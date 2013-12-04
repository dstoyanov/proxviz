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

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <utility>

#include <QGraphicsScene>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>

#include "qvertex.h"


class QVertex;

struct Vertex{
    std::string name;

    double x;
    double y;

    bool is_visible;

    double size;

    int age;

    // needed for the ForceAtlas
    double dx;
    double dy;
    double old_dx;
    double old_dy;
    double mass;

    QVertex *qvertex;
};

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,  Vertex > graph_t;

typedef boost::graph_traits<graph_t>::vertex_iterator VertexIterator;

typedef boost::graph_traits<graph_t>::edge_iterator EdgeIterator;

typedef boost::graph_traits<graph_t>::adjacency_iterator AdjacencyIterator;

typedef boost::graph_traits<graph_t>::vertex_descriptor VertexDescriptor;

typedef std::map<std::string, VertexDescriptor> NameToVertex;

enum graph_state_t {NOT_SHOWN, SHOWN, VERTICES_REMOVED};

class Graph{

public:
    Graph();

    Vertex *addVertex(const std::string &name);
    Vertex *addVertex(Vertex &v);

    void addEdge(const std::string id_v1, const std::string id_v2,
                 bool insert_vertices=true);

    void printGraph();

    time_t *getTime();
    void setTime(time_t t);

    std::pair<VertexIterator, VertexIterator> getVertexIterators();

    std::pair<EdgeIterator, EdgeIterator> getEdgeIterators();

    std::pair<AdjacencyIterator, AdjacencyIterator>
        getAdjacentIterators(VertexIterator vi);

    Vertex *getVertex(VertexIterator vi);

    Vertex *getVertex(const std::string &name);

    Vertex *getVertex(AdjacencyIterator ai);

    Vertex *getEdgeTarget(EdgeIterator ei);
    Vertex *getEdgeSource(EdgeIterator ei);

    bool checkEdgeExists(std::string v1_name, std::string v2_name);

    void removeVertex(VertexIterator vi);

    unsigned int getNumberVertices();

    unsigned int getNumberEdges();

    int getDegree(VertexIterator vi);

//    void replaceGraph(Graph *g);

    void recomputeGraphEdges(double radius);

    void prepareNewGraph(Graph *g, QGraphicsScene *scene);
    void prepareNewGraph(Graph *g);

    void printEdges();


//    bool first_display;
    graph_state_t graph_state;

private:
    graph_t graph;
    NameToVertex names;

    time_t time;

    int max_age;
};

#endif // GRAPH_H
