/*
 * Copyright 2013 Dimo Stoyanov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "forceatlas2.h"

#include <utility>
#include <algorithm>

#include <sys/time.h>
#include <ctime>

#include <boost/thread.hpp>

#include <iostream>
#include <fstream>

#include "barneshutregion.h"

ForceAtlas2::ForceAtlas2(int width, int height, bool bhe){
    canvas_width = width;
    canvas_height = height;

    speed = 1.;

    num_threads = 16;

    num_executions = 0;

    barnes_hut_enabled = bhe;

    barnes_hut_theta = 1.2;

    root_region = 0;
}

void ForceAtlas2::randomize_layout(Graph *g){
    std::pair<VertexIterator, VertexIterator> iterators = g->getVertexIterators();
    for(; iterators.first != iterators.second; ++iterators.first){
        Vertex *v = g->getVertex(iterators.first);

        v->x = 2/3. * ((double) this->canvas_width / 2. -
                (double) this->canvas_width * rand() / (double) RAND_MAX);

        v->y = 2/3. * ((double) this->canvas_height / 2. -
                (double) this->canvas_height * rand() / (double) RAND_MAX);
    }
    num_updates++;
}

void ForceAtlas2::setDefaultCoefficients(Graph *g){
    int n_vertices = g->getNumberVertices();

    if(n_vertices >= 100){
        scaling_ratio = 2.0;
    }else{
        scaling_ratio= 10.0;
    }

    gravity_coefficient = 1.0;

    if(n_vertices >= 50000){

        jitter_tollerance = 10;

    }else if (n_vertices >= 5000){

        jitter_tollerance = 1;

    }else{
        jitter_tollerance = 0.1;
    }

}

void ForceAtlas2::initializeAlgorithm(Graph *g){
    speed = 1.;

    std::pair<VertexIterator, VertexIterator> it;
    it = g->getVertexIterators();

    for(; it.first != it.second; ++it.first){
        Vertex *v = g->getVertex(it.first);

        v->mass = 1 + g->getDegree(it.first);

        v->old_dx = 0;
        v->old_dy = 0;

        v->dx = 0;
        v->dy = 0;
    }
}

void ForceAtlas2::runAlgorithm(Graph *g){

//    timespec begin, end;

//    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);

    std::pair<VertexIterator, VertexIterator> vi;
    std::pair<VertexIterator, VertexIterator> vj;

    std::pair<EdgeIterator, EdgeIterator> ei;

    vi = g->getVertexIterators();
    for(; vi.first != vi.second; ++vi.first){
        Vertex *v = g->getVertex(vi.first);

        v->mass = 1 + g->getDegree(vi.first);

        v->old_dx = v->dx;
        v->old_dy = v->dy;

        v->dx = 0;
        v->dy = 0;
    }

    // Barnes Hut optimization
    if(barnes_hut_enabled){
        std::vector<Vertex *> tmp_vertices;

        vi = g->getVertexIterators();
        for(; vi.first != vi.second; ++vi.first){
            tmp_vertices.push_back(g->getVertex(vi.first));
        }

        root_region = new BarnesHutRegion(tmp_vertices);
        root_region->buildSubRegions();
    }

    //Repulsin and Gravity thread
    int num_vertices = g->getNumberVertices();
    vi = g->getVertexIterators();
    boost::thread_group tgroup;

    for(int t = num_threads; t > 0; t--){
        int from = floor(num_vertices * (t-1)  / num_threads);
        int to = floor(num_vertices * t / num_threads);

        tgroup.create_thread(boost::bind(
               &ForceAtlas2::repulsionGravityThread, this, g, from, to));
    }

    tgroup.join_all();



    //Attraction
    ei = g->getEdgeIterators();
    for(; ei.first != ei.second; ++ei.first){
        linAttraction(g->getEdgeSource(ei.first), g->getEdgeTarget(ei.first), 1, 1);
    }

    double total_swinging = 0;
    double total_effective_traction = 0;

    vi = g->getVertexIterators();
    for(; vi.first != vi.second; ++vi.first){
        Vertex *v = g->getVertex(vi.first);

        double swinging = sqrt((v->old_dx - v->dx) * (v->old_dx - v->dx) +
                               (v->old_dy - v->dy) * (v->old_dy - v->dy));

        total_swinging += v->mass * swinging;

        total_effective_traction += v->mass * 0.5 *
                sqrt((v->old_dx + v->dx) * (v->old_dx + v->dx) +
                     (v->old_dy + v->dy) * (v->old_dy + v->dy));
    }

    double target_speed = jitter_tollerance * jitter_tollerance *
            total_effective_traction / total_swinging;

    speed += std::min(target_speed - speed, 0.5 * speed);

    vi = g->getVertexIterators();
    for(; vi.first != vi.second; ++vi.first){
        Vertex *v = g->getVertex(vi.first);

        double swinging = sqrt((v->old_dx - v->dx) * (v->old_dx - v->dx) +
                               (v->old_dy - v->dy) * (v->old_dy - v->dy));

        double factor = speed / (1. + speed * sqrt(swinging));

        v->x += v->dx * factor;
        v->y += v->dy * factor;
    }


//    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    //    std::cout << "EXECUTION TIME: " << end.tv_nsec - begin.tv_nsec << " nsec" << std::endl;
//        if(execution_time < 0 || end.tv_nsec < begin.tv_nsec){
//            std::cout << "ET: " << execution_time << "  " << begin.tv_nsec << "  " << end.tv_nsec << std::endl;
//        }


//    execution_time += pow(10, 9) * (end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

//    execution_time[num_updates] += pow(10, 9) * (end.tv_sec - begin.tv_sec) + end.tv_nsec - begin.tv_nsec;

//    num_executions++;

//    if(num_executions == 100){
////        std::cout << "Total execution time " << execution_time << std::endl;
////        execution_time = 0;
//        num_executions = 1;

//        std::cout << "NUMMBER UPDATES " << num_updates << std::endl;
//        //            exit(1);
//    }
//    if(root_region != 0){
//        delete(root_region);
//        root_region = 0;
//    }
}

void ForceAtlas2::linRepulsionAnticollision(Vertex *v1, Vertex *v2,
                                            double coefficient){
    double xdist = v1->x - v2->x;
    double ydist = v1->y - v2->y;
    double distance = sqrt(xdist * xdist + ydist * ydist) - v1->size - v2->size;

    if(distance > 0 ){
        double factor = coefficient * v1->mass * v2->mass / distance / distance;

        v1->dx += xdist * factor;
        v1->dy += ydist * factor;

        v2->dx -= xdist * factor;
        v2->dy -= ydist * factor;

    } else{
        double factor = 100 * coefficient * v1->mass * v2->mass;

        v1->dx += xdist * factor;
        v1->dy += ydist * factor;

        v2->dx -= xdist * factor;
        v2->dy -= ydist * factor;
    }
}

void ForceAtlas2::linRepulstionAnticollision(Vertex *v, double coefficient,
                                             double g){

    double distance = sqrt(v->x * v->x + v->y * v->y);

    if(distance > 0){
        double factor = coefficient * v->mass * g / distance;

        v->dx -= v->x * factor;
        v->dy -= v->y * factor;
    }
}

void ForceAtlas2::linRepulsion(Vertex *v1, Vertex *v2, double coefficient){
    double xdist = v1->x - v2->x;
    double ydist = v1->y - v2->y;
    double distance = sqrt(xdist * xdist + ydist * ydist) - v1->size - v2->size;

    if(distance > 0){
        double factor = coefficient * v1->mass * v2->mass / distance / distance;

        v1->dx += xdist * factor;
        v1->dy += ydist * factor;

        v2->dx -= xdist * factor;
        v2->dy -= ydist * factor;
    }
}

void ForceAtlas2::linRepulsion(Vertex *v, double coefficient, double gravity){
    double distance = sqrt(v->x * v->x + v->y * v->y);
    if(distance > 0){
        double factor = coefficient * v->mass * gravity / distance;

        v->dx -= v->x * factor;
        v->dy -= v->y * factor;
    }
}

void ForceAtlas2::logAttractionAnticollision(Vertex *v1, Vertex *v2,
                                             double coefficient, double e){
    double xdist = v1->x - v2->x;
    double ydist = v1->y - v2->y;
    double distance = sqrt(xdist * xdist + ydist * ydist) - v1->size - v2->size;

    if(distance > 0){
        double factor = -coefficient * e * std::log( 1 + distance) / distance  / v1->mass;

        v1->dx += xdist * factor;
        v1->dy += ydist * factor;

        v2->dx -= xdist * factor;
        v2->dy -= ydist * factor;
    }
}

void ForceAtlas2::linAttraction(Vertex *v1, Vertex *v2, double coefficient, double e){
    double xdist = v1->x - v2->x;
    double ydist = v1->y - v2->y;

    double distance = sqrt(xdist * xdist + ydist * ydist) - v1->size - v2->size;

    if(distance > 0){
        double factor = -coefficient / e;

        v1->dx += xdist * factor;
        v1->dy += ydist * factor;

        v2->dx -= xdist * factor;
        v2->dy -= ydist * factor;

    }
}

void ForceAtlas2::repulsionGravityThread(Graph *g, int from, int to){


    VertexIterator vi = g->getVertexIterators().first;
    VertexIterator vj;
    VertexIterator tmp = vi + to;

    if(barnes_hut_enabled){
        for(vi += from; vi < tmp; ++vi){
            //            root_region->applyRepulsionForce(g->getVertex(vi), barnes_hut_theta);
            linRepulsion(g->getVertex(vi), root_region, scaling_ratio, barnes_hut_theta);
        }
    }else{
        for(vi += from; vi < tmp; ++vi){
            vj = g->getVertexIterators().first;

            for(;vj < vi; ++vj){
                linRepulsion(g->getVertex(vi), g->getVertex(vj), scaling_ratio);
            }
        }
    }


    vi = g->getVertexIterators().first;
    for(vi += from; vi < tmp; ++vi){
        linRepulsion(g->getVertex(vi),  scaling_ratio,
                     gravity_coefficient / (double) scaling_ratio);
    }
}


void ForceAtlas2::linRepulsion(Vertex *v, BarnesHutRegion *region, double coefficient,
                               double theta){
    if(region->getNumerNodes() < 2){
        linRepulsion(v, region->getNodeAt(0), coefficient);
    }else{
        double distance = sqrt((v->x - region->getMassCenterX()) *
                               (v->x - region->getMassCenterX()) +
                               (v->y - region->getMassCenterY()) *
                               (v->y - region->getMassCenterY()));

        if(distance * theta > region->getSize()){
            linRepulsion(v, region, coefficient);   //TODO replace with the code from the function below
        } else{
            for(int i = 0; i < region->getNumberSubregions(); i++){
                linRepulsion(v, region->getSubregionAt(i), coefficient, theta);
            }
        }
    }
}

void ForceAtlas2::linRepulsion(Vertex *v, BarnesHutRegion *region, double coefficient){
    double xdist = v->x - region->getMassCenterX();
    double ydist = v->y - region->getMassCenterY();
    double distance = sqrt(xdist * xdist + ydist * ydist);

    if(distance > 0){
        double factor = coefficient * v->mass * region->getMass() / distance / distance;

        v->dx += xdist * factor;
        v->dy += ydist * factor;
    }
}


void ForceAtlas2::print_execution_times(char *filename){
    std::ofstream f(filename, std::ios::app);
    long total_execution_time = 0;

    for(int i = 0; i < 100; i++)
        total_execution_time += execution_time[i];

    f << std::fixed << total_execution_time / 2000. << std::endl;
    f.close();
}

