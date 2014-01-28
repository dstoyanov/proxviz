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

#include "graphvizdatareader.h"

#include <boost/regex.hpp>

GraphVizDataReader::GraphVizDataReader(std::string filename)
{
    mtx = new boost::mutex();

    filename = filename;

    file_streams.push_back(new ifstream(filename.c_str(), ifstream::in));

    if(!file_streams[0]->is_open())
        cerr << "Unable to read from " << filename << endl;

    readGraph();
}

void GraphVizDataReader::readGraph(){

    boost::regex node_regex("j\\d*");
    boost::smatch match;

    string node1_id;
    string node2_id;

    Graph *g = new Graph();

    int line_size = 256;
    char line[line_size];


    while(!file_streams[0]->eof()){

        file_streams[0]->getline(line, line_size);

        string s = string(line);

        string::const_iterator begin = s.begin();
        string::const_iterator end = s.end();

        if(boost::regex_search(begin, end, match, node_regex)){
            node1_id = string(match[0].first, match[0].second);
            begin = match[0].second;

            if(boost::regex_search(begin, end, match, node_regex)){
                node2_id = string(match[0].first, match[0].second);

//                cout << "ADDING EDGE " << node1_id << "  " << node2_id << endl;

                g->addEdge(node1_id, node2_id);
            }
        }
    }

    snapshots.push_back(g);
}
