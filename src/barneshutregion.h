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

#ifndef BARNESHUTREGION_H
#define BARNESHUTREGION_H

#include "graph.h"
#include "forceatlas2.h"

#include<boost/thread.hpp>


/**
 *  @file barneshutregion.h
 *  @author Dimo Stoyanov
 *  @brief Used for optimization of the Force Atlas 2 algorithm.
 *  Divides the space into squares and creates a quadtree.
 */

class BarnesHutRegion
{
public:
    BarnesHutRegion(std::vector<Vertex *>);

    void updateMassAndGeometry();

    void buildSubRegions();

    double getMass();
    double getMassCenterX();
    double getMassCenterY();
    double getSize();
    int getNumerNodes();
    Vertex* getNodeAt(int i);

    int getNumberSubregions();
    BarnesHutRegion *getSubregionAt(int i);

private:
    std::vector<Vertex *> nodes;
    std::vector<BarnesHutRegion *> subregions;

    double mass;
    double massCenterX;
    double massCenterY;
    double size;

    boost::mutex *mtx;

    void linRepulsion(Vertex *v);
};

#endif // BARNESHUTREGION_H
