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

#include "ubidatareader.h"

#include "graph.h"

#include <boost/regex.hpp>
#include <boost/date_time.hpp>

UbiDataReader::UbiDataReader(string trace_path, double range){
    mtx = new boost::mutex();

    this->range = range;

    file_streams.push_back(new ifstream(trace_path.c_str(), ifstream::in));


    if(file_streams[0]->good() && !file_streams[0]->is_open())
        cerr << "Unable to read from " << trace_path << endl;

    char line[256];
    file_streams[0]->getline(line, 256);
    file_streams[0]->seekg(0);

    current_time = extractTime(line);


    readGraph();
}

void UbiDataReader::setRange(double range){
    this->range = range;
}

void UbiDataReader::recomputeAllSnapshotVertices(double range){
    this->range = range;
    deque<Graph *>::iterator it;

    for(it = snapshots.begin(); it != snapshots.end(); ++it)
        (*it)->recomputeGraphEdges(range);
}

time_t UbiDataReader::extractTime(string line){
    boost::regex time_regex("\\d{2}\\/\\d{2}\\/\\d{2} \\d{2}:\\d{2}:\\d{2}");
    boost::smatch match;
    time_t result = -1;

    if(boost::regex_search(string(line), match, time_regex)){

        string s = string(match[0].first, match[0].second);
        istringstream  is(s);
        const locale format = locale(locale::classic(),
                                     new bt::time_input_facet("%m/%d/%y %H:%M:%S"));

        bt::ptime pt;
        is.imbue(format);
        is >> pt;

        result = pt_to_time_t(pt);
    }

    return result;
}

string UbiDataReader::extractId(string line){
    boost::regex id_regex("\\d{3}\\-\\d{3}\\-\\d{3}\\-\\d{3}");
    boost::smatch match;
    string id = "";


    if(boost::regex_search(string(line), match, id_regex)){
        id = string(match[0].first, match[0].second);
    }

    return id;
}

bool UbiDataReader::extractCoordinates(string line, float &x, float &y){
    boost::regex coordinate_regex("\\[\\-?\\d*\\.\\d*,\\-?\\d*\\.\\d*,\\-?\\d*\\.\\d*\\]");
    boost::regex float_regex("\\-?\\d*\\.\\d*");
    boost::smatch match;

    if(boost::regex_search(string(line), match, coordinate_regex)){
        string s =  string(match[0].first, match[0].second);

        string::const_iterator begin = s.begin();
        string::const_iterator end = s.end();

        boost::regex_search(begin, end, match, float_regex);
        x = atof(string(match[0].first, match[0].second).c_str());
        begin = match[0].second;

        boost::regex_search(begin, end, match, float_regex);
        y = atof(string(match[0].first, match[0].second).c_str());
        return true;
    }

    return false;
}

void UbiDataReader::readGraph(){

    Graph *g = new Graph();

    std::pair<VertexIterator, VertexIterator> vi;
    std::pair<VertexIterator, VertexIterator> vj;

    int line_size = 256;
    char line[line_size];

    string id;
    time_t time = current_time;
    float x, y;

    while(time == current_time){
        file_streams[0]->getline(line, line_size);


        if(strlen(line) == 0)
            break;
        bool b = stringToVertex(line, id, time, x,  y);
//        std::cout << line << std::endl;
//        std::cout << id << "  " << time << "  " << x << "  " << y << std::endl;
        if(b && time == current_time){
            Vertex *v = g->addVertex(id);
            v->x =  x;
            v->y =  y;
        }
   }


    if(g->getNumberVertices() > 0){
        g->setTime(current_time);
        current_time++;

        vi = g->getVertexIterators();

        for(; vi.first != vi.second; ++vi.first){

            vj = g->getVertexIterators();
            for(; vj.first != vj.second; ++vj.first){
                Vertex *v1 = g->getVertex(vi.first);
                Vertex *v2 = g->getVertex(vj.first);

                float d = sqrt((v1->x - v2->x) * (v1->x - v2->x) + (v1->y - v2->y) * (v1->y - v2->y));
                if(d < range && v1->name != v2->name){
                    g->addEdge(v1->name, v2->name, false);
                }
            }
        }

    }else{
        delete(g);
        return;
    }

    mtx->lock();
    snapshots.push_back(g);
    mtx->unlock();
}

bool UbiDataReader::stringToVertex(const char* line, string &id, time_t &time,
                                            float &x, float &y){

    id = extractId(line);
    time = extractTime(line);
    bool c = extractCoordinates(line, x, y);

    if(!c || time == -1 || id.empty()){
        return false;
    }

    return true;
}

std::time_t UbiDataReader::pt_to_time_t(const bt::ptime& pt)
{
    bt::ptime timet_start(boost::gregorian::date(1970,1,1));
    bt::time_duration diff = pt - timet_start;
    return diff.ticks()/bt::time_duration::rep_type::ticks_per_second;
}
