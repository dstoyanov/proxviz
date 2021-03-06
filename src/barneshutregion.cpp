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

#include "barneshutregion.h"

BarnesHutRegion::BarnesHutRegion(std::vector<Vertex *> vertices){
    nodes = vertices;
    mtx = new boost::mutex();
    updateMassAndGeometry();
}


void BarnesHutRegion::updateMassAndGeometry(){
    double massSumX;
    double massSumY;
    double distance;
    std::vector<Vertex *>::iterator nit;
    std::vector<BarnesHutRegion *>::iterator rit;

    if(nodes.size() > 1){
        mass = 0;

        massSumX = 0;
        massSumY = 0;

        for(nit = nodes.begin(); nit != nodes.end(); ++nit){
            mass += (*nit)->mass;
            massSumX += (*nit)->x * (*nit)->mass;
            massSumY += (*nit)->y * (*nit)->mass;
        }

        massCenterX = massSumX / mass;
        massCenterY = massSumY / mass;

        size = -DBL_MAX;

        for(nit = nodes.begin(); nit != nodes.end(); ++nit){
            distance = sqrt(((*nit)->x - massCenterX) * ((*nit)->x - massCenterX) +
                            ((*nit)->y - massCenterY) * ((*nit)->y - massCenterY));

            size = std::max(size, 2 * distance);
        }
    }
}

void BarnesHutRegion::buildSubRegions(){
    if(nodes.size() > 1){
        std::vector<Vertex *> leftNodes;
        std::vector<Vertex *> rightNodes;
        std::vector<Vertex *> topLeftNodes;
        std::vector<Vertex *> bottomLeftNodes;
        std::vector<Vertex *> topRightNodes;
        std::vector<Vertex *> bottomRightNodes;

        std::vector<Vertex *> subRegions[4];

        std::vector<Vertex *>::iterator nit;
        std::vector<BarnesHutRegion *>::iterator rit;

        mtx->lock();

        for(nit = nodes.begin(); nit != nodes.end(); ++nit){
            (*nit)->x < massCenterX ? leftNodes.push_back(*nit) :
                                      rightNodes.push_back(*nit);
        }

        for(nit = leftNodes.begin(); nit != leftNodes.end(); ++nit){
            (*nit)->y < massCenterY ? topLeftNodes.push_back(*nit) :
                                      bottomLeftNodes.push_back(*nit);
        }


        for(nit = rightNodes.begin(); nit != rightNodes.end(); ++nit){
            (*nit)->y < massCenterY ? topRightNodes.push_back(*nit) :
                                      bottomRightNodes.push_back(*nit);
        }

        subRegions[0] = topLeftNodes;
        subRegions[1] = bottomLeftNodes;
        subRegions[2] = bottomRightNodes;
        subRegions[3] = topRightNodes;

        for(int i = 0; i < 4; i++){
            if(subRegions[i].size() > 0){
                if(subRegions[i].size() < nodes.size()){
                    subregions.push_back(new BarnesHutRegion(subRegions[i]));
                }
            }else{
                for(nit = subRegions[i].begin(); nit != subRegions[i].end(); ++nit){
                    std::vector<Vertex *> tmp;
                    tmp.push_back(*nit);
                    subregions.push_back(new BarnesHutRegion(tmp));
                }
            }
        }


        for(rit = subregions.begin(); rit != subregions.end(); ++rit){
            (*rit)->buildSubRegions();
        }

        mtx->unlock();

    }
}



double BarnesHutRegion::getMass(){
    return mass;
}


double BarnesHutRegion::getMassCenterX(){
    return massCenterX;
}

double BarnesHutRegion::getMassCenterY(){
    return massCenterY;
}

int BarnesHutRegion::getNumerNodes(){
    return nodes.size();
}

Vertex* BarnesHutRegion::getNodeAt(int i){
    return nodes[i];
}

int BarnesHutRegion::getNumberSubregions(){
    return subregions.size();
}

BarnesHutRegion* BarnesHutRegion::getSubregionAt(int i){
    return subregions[i];
}

double BarnesHutRegion::getSize(){
    return size;
}
