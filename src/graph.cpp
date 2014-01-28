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

#include "graph.h"

#include <iostream>

Graph::Graph(){
//    first_display = false;

    graph_state = NOT_SHOWN;

    max_age = 3;
}


Vertex* Graph::addVertex(const std::string &name){
    NameToVertex::iterator i = names.find(name);

    if(i == names.end()){
        VertexDescriptor v = boost::add_vertex(graph);

        graph[v].name = name;

        graph[v].x = 0;
        graph[v].y = 0;

        graph[v].dx = 0;
        graph[v].dy = 0;
        graph[v].old_dx = 0;
        graph[v].old_dy = 0;
        graph[v].mass = 1.0;
        graph[v].size = 10.0;

        graph[v].age = 0;

        graph[v].qvertex = NULL;

        i = names.insert(std::make_pair(name, v)).first;
    }
        return &graph[i->second];
}

Vertex* Graph::addVertex(Vertex &v){
    NameToVertex::iterator i = names.find(v.name);

    if(i == names.end()){
        VertexDescriptor vd = boost::add_vertex(graph);

        graph[vd].name = v.name;

        graph[vd].x = v.x;
        graph[vd].y = v.y;

        graph[vd].dx = v.dx;
        graph[vd].dy = v.dy;
        graph[vd].old_dx = v.old_dx;
        graph[vd].old_dy = v.old_dy;
        graph[vd].size = v.size;

        graph[vd].age = v.age;

        graph[vd].qvertex = v.qvertex;
        v.qvertex = NULL;

        i = names.insert(std::make_pair(v.name, vd)).first;
    }

    return &graph[i->second];
}

/**
 * If insert_vertices == true insert the vertices if they do not exist
 * in the graph
 */
void Graph::addEdge(const std::string id_v1, const std::string id_v2,
                    bool insert_vertices){

    NameToVertex::iterator i1 = names.find(id_v1);
    NameToVertex::iterator i2 = names.find(id_v2);

    VertexDescriptor v1;
    VertexDescriptor v2;

    if(insert_vertices){
        if(i1 == names.end()){
            v1 = boost::add_vertex(graph);

            graph[v1].name = id_v1;

            graph[v1].x = 0;
            graph[v1].y = 0;

            graph[v1].dx = 0;
            graph[v1].dy = 0;
            graph[v1].old_dx = 0;
            graph[v1].old_dy = 0;
            graph[v1].mass = 1.0;
            graph[v1].size = 10.0;

            graph[v1].age = 0;

            graph[v1].qvertex = NULL;

            names.insert(std::make_pair(id_v1, v1));
        }else{
            v1 = i1->second;
        }

        if(i2 == names.end()){
            v2 = boost::add_vertex(graph);

            graph[v2].name = id_v2;

            graph[v2].x = 0;
            graph[v2].y = 0;

            graph[v2].dx = 0;
            graph[v2].dy = 0;
            graph[v2].old_dx = 0;
            graph[v2].old_dy = 0;
            graph[v2].mass = 1.0;
            graph[v2].size = 10.0;

            graph[v2].age = 0;

            graph[v2].qvertex = NULL;

            names.insert(std::make_pair(id_v2, v2));

        }else{
            v2 = i2->second;
        }

        boost::add_edge(v1, v2, graph);

    }else{
        if(i1 != names.end() && i2 != names.end()){
            boost::add_edge(i1->second, i2->second, graph);
        }
    }
}

void Graph::printGraph(){
    VertexIterator vi, vi_end;

    for(boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi){
        std::cout << "Vertex " <<   graph[*vi].name << " x " << graph[*vi].x << " y " <<
                     graph[*vi].y << "  " << graph[*vi].mass << "  " << graph[*vi].age << "  " <<
                     graph[*vi].dx << " " << graph[*vi].dy << std::endl;
    }
}

time_t *Graph::getTime(){
    return &this->time;
}

void Graph::setTime(time_t t){
    time = t;
}

std::pair<VertexIterator, VertexIterator> Graph::getVertexIterators(){
    VertexIterator vi, vi_end;

    boost::tie(vi, vi_end) = vertices(graph);

    return std::make_pair(vi, vi_end);
}

std::pair<EdgeIterator, EdgeIterator> Graph::getEdgeIterators(){
    EdgeIterator ei, ei_end;

    boost::tie(ei, ei_end) = edges(graph);

    return std::make_pair(ei, ei_end);
}

std::pair<AdjacencyIterator, AdjacencyIterator>
Graph::getAdjacentIterators(VertexIterator vi){
    AdjacencyIterator ai, ai_end;

    boost::tie(ai, ai_end) = adjacent_vertices(*vi, graph);

    return std::make_pair(ai, ai_end);
}

Vertex *Graph::getVertex(VertexIterator vi){
    return &graph[*vi];
}

Vertex *Graph::getVertex(AdjacencyIterator ai){
    return &graph[*ai];
}

Vertex *Graph::getVertex(const std::string &name){
    NameToVertex::iterator i = names.find(name);

    if(i == names.end())
        return NULL;

    return &(graph[i->second]);
}

Vertex *Graph::getEdgeSource(EdgeIterator ei){
    VertexDescriptor vd = source(*ei, graph);

    return &graph[vd];
}

Vertex *Graph::getEdgeTarget(EdgeIterator ei){
    VertexDescriptor vd = target(*ei, graph);

    return &graph[vd];

}

unsigned int Graph::getNumberVertices(){
    return num_vertices(graph);
}

unsigned int Graph::getNumberEdges(){
    return num_edges(graph);
}

int Graph::getDegree(VertexIterator vi){
    return degree(*vi, graph);
}

void Graph::removeVertex(VertexIterator vi){

    delete(graph[*vi].qvertex);
    remove_vertex(*vi, graph);
}

//void Graph::replaceGraph(Graph *g){
//    VertexIterator vi, vi_end;

//    //increase age or remove the vertices which are not in the new graph
//    boost::tie(vi, vi_end) = vertices(graph);
//    for(; vi != vi_end; ++vi){
//        if(g->getVertex(graph[*vi].name) == NULL){

//            if(g[*vi].age >= max_age){
//                delete(graph[*vi].qvertex);
//                remove_vertex(*vi, graph);
//            }else{
//                g[*vi].age++;
//            }
//        }
//    }


//    //add the new vertices
//    std::pair<VertexIterator, VertexIterator> vis;

//    vis = g->getVertexIterators();
//    for(; vis.first != vis.second; ++vis.first){
//        Vertex *v_new = g->getVertex(vis.first);

//        if(this->getVertex(v_new->name) == NULL){
//            VertexDescriptor vd = add_vertex(graph);

//            graph[vd].name = v_new->name;

//            graph[vd].x = 0;
//            graph[vd].y = 0;

//            graph[vd].dx = 0;
//            graph[vd].dy = 0;
//            graph[vd].old_dx = 0;
//            graph[vd].old_dy = 0;
//            graph[vd].mass = 1.0;
//            graph[vd].size = 10.0;

//            graph[vd].age = 0;

//            graph[vd].qvertex = NULL;

//            names.insert(std::make_pair(v_new->name, vd));
//        }
//    }

//    //
//}

void Graph::prepareNewGraph(Graph *g){
    VertexIterator vi, vi_end;
    boost::tie(vi, vi_end) = vertices(graph);

    std::vector<VertexDescriptor> old_vertices;
    std::vector<VertexDescriptor>::iterator i;
    std::pair<AdjacencyIterator, AdjacencyIterator> ais;

    for(; vi != vi_end; ++vi){
        Vertex *v = g->getVertex(graph[*vi].name);

        if(v == NULL){
            if(graph[*vi].age < 3){
                graph[*vi].age++;
                old_vertices.push_back(*vi);

                g->addVertex(graph[*vi]);
            }
        }else{
            v->x = graph[*vi].x;
            v->y = graph[*vi].y;

            v->qvertex = graph[*vi].qvertex;
            graph[*vi].qvertex = NULL;
        }
    }

    for(i = old_vertices.begin(); i != old_vertices.end(); ++i){
        ais = boost::adjacent_vertices(*i, graph);

        for(; ais.first != ais.second; ++ais.first){
            g->addEdge(graph[*i].name, graph[*(ais.first)].name, false);
        }
    }
}

/*
void Graph::prepareNewGraph(Graph *g, QGraphicsScene *scene){

    VertexIterator vi, vi_end;
    boost::tie(vi, vi_end) = vertices(graph);

    std::vector<VertexDescriptor> old_vertices;
    std::vector<VertexDescriptor>::iterator i;
    std::pair<AdjacencyIterator, AdjacencyIterator> ais;

    for(; vi != vi_end; ++vi){
        Vertex *v = g->getVertex(graph[*vi].name);

        if(v == NULL){

            if(graph[*vi].age < 3){
                graph[*vi].age++;

//                std::cout << "ADDING VERTEX " << graph[*vi].name << std::endl;

                old_vertices.push_back(*vi);

                g->addVertex(graph[*vi]);
            }else{
                scene->removeItem(graph[*vi].qvertex);
                delete(graph[*vi].qvertex);
            }
        }else{
            v->x = graph[*vi].x;
            v->y = graph[*vi].y;

            v->qvertex = graph[*vi].qvertex;

            graph[*vi].qvertex = NULL;

        }
    }

    for(i = old_vertices.begin(); i != old_vertices.end(); ++i){
        ais = boost::adjacent_vertices(*i, graph);

        for(; ais.first != ais.second; ++ais.first){
            g->addEdge(graph[*i].name, graph[*(ais.first)].name, false);
        }
    }

//    g->first_display = false;
    g->graph_state = SHOWN;


//    QList<QGraphicsItem *> items = scene->items();
//    QList<QGraphicsItem *>::Iterator it;

//    for(it = items.begin(); it != items.end(); ++it){
//        if((*it)->type() == QEdge::Type)
//    }

//    boost::tie(vi, vi_end) = vertices(graph);
//    for(; vi != vi_end; ++vi){
//        if(graph[*vi].qvertex != NULL)
//            delete(graph[*vi].qvertex);
//    }

//    std::cout << "Graph Transformed" << std::endl;
}
*/

void Graph::printEdges(){
    std::pair<EdgeIterator, EdgeIterator> ei = getEdgeIterators();
    for(; ei.first != ei.second; ++ei.first){
        std::cout << "Edge: " << " " << getEdgeSource(ei.first)->name << "  " <<  getEdgeSource(ei.first)->x << "  " <<  getEdgeSource(ei.first)->y;
        std::cout << getEdgeTarget(ei.first)->name << " " << getEdgeTarget(ei.first)->x << " " << getEdgeTarget(ei.first)->y << std::endl;
    }

}

bool Graph::checkEdgeExists(std::string v1_name, std::string v2_name){

    NameToVertex::iterator i1 = names.find(v1_name);
    NameToVertex::iterator i2 = names.find(v2_name);

    VertexDescriptor v1;
    VertexDescriptor v2;

    if(i1 != names.end() && i2 != names.end()){
        v1 = i1->second;
        v2 = i2->second;

        return edge(v1, v2, graph).second;
    }

    return false;
}

void Graph::recomputeGraphEdges(double radius){
    std::pair<VertexIterator, VertexIterator> vi1;
    std::pair<VertexIterator, VertexIterator> vi2;

//    NameToVertex::iterator name_it1;
//    NameToVertex::iterator name_it2;

    VertexDescriptor vd1, vd2;
    Vertex *v1;
    Vertex *v2;

    std::cout << "RADIUS " << radius << std::endl;

    double distance;

    vi1 = getVertexIterators();
    for(; vi1.first != vi1.second; ++vi1.first){

        v1 = getVertex(vi1.first);
        vd1 = names.find(v1->name)->second;

        vi2 = getVertexIterators();
        for(; vi2.first != vi2.second; ++vi2.first){
            v2 = getVertex(vi2.first);
            vd2 = names.find(v2->name)->second;

            distance = sqrt((v1->x - v2->x) * (v1->x - v2->x) +
                            (v1->y - v2->y) * (v1->y - v2->y));

            if(distance > radius && edge(vd1, vd2, graph).second){
                remove_edge(vd1, vd2, graph);

            }else if(distance <= radius && !edge(vd1, vd2, graph).second){
                std::cout << "ADDING EDGE: " << v1->name << "  " << v2->name << std::endl;
                add_edge(vd1, vd2, graph);
            }
        }
    }
}
