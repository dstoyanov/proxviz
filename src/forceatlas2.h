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


/**
 *  @file forceatlas2.h
 *  @author Dimo Stoyanov
 *  @brief Computes the positioning of the nodes.
 */
#ifndef FORCEATLAS2_H
#define FORCEATLAS2_H

#include "graph.h"
#include "barneshutregion.h"

class BarnesHutRegion;

class ForceAtlas2
{
public:
    ForceAtlas2(int width, int height, bool barnes_hut_enabled = true);

    /**
     * The main loop of the algorithm. All the forces are computed in it.
     */
    void runAlgorithm(Graph *g);

    /**
     * The initialization of the layout. All nodes of graph g are
     * placed randomly
     */
    void randomize_layout(Graph *g);


    void initializeAlgorithm(Graph *g);

    /**
     * Sets the default values for the variables needed for the algorithm.
     * They are computed dynamically based on the properties of the
     * graph (e.g. density, number of nodes, etc.)
     */
    void setDefaultCoefficients(Graph *g);

    double jitter_tollerance;

    double scaling_ratio;

    double gravity_coefficient;

    void print_execution_times(char *filename);


private:

    long execution_time[100];
    int num_updates;

    double speed;

    int num_threads;

    int canvas_width;
    int canvas_height;

    BarnesHutRegion *root_region;

    int num_executions;
    //    long long execution_time;

    bool barnes_hut_enabled;
    double barnes_hut_theta;

    void linRepulsionAnticollision(Vertex *v1, Vertex *v2, double coefficient);
    void linRepulstionAnticollision(Vertex *v1, double coefficient, double g);


    void linRepulsion(Vertex *v1, Vertex *v2, double coefficient);
    void linRepulsion(Vertex *v, double coefficient, double gravity);
    void linRepulsion(Vertex *v, BarnesHutRegion *region, double coefficient, double theta);
    void linRepulsion(Vertex *v, BarnesHutRegion *region, double coefficient);

    void logAttractionAnticollision(Vertex *v1, Vertex *v2, double coefficient, double e);
    void linAttraction(Vertex *v1, Vertex *v2, double coefficient, double e);


    void repulsionGravityThread(Graph *g, int from, int to);
};

#endif // FORCEATLAS2_H
