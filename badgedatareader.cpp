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

#include "badgedatareader.h"

#include <boost/regex.hpp>
#include <dirent.h>

BadgeDataReader::BadgeDataReader(string folder_path){
    mtx = new boost::mutex();

    DIR *dir;
    struct dirent *ent;

    boost::regex name_pattern(".*\\.nodedat");
    boost::regex id_pattern("([1-9]\\d*)");

    ifstream *stream;
    string file_path;


    if((dir = opendir(folder_path.c_str())) != NULL){
        while((ent = readdir(dir)) != NULL){

            if(boost::regex_match(ent->d_name, name_pattern)){

                this->node_ids.push_back(filename2id(ent->d_name));

                file_path = folder_path + "/" + ent->d_name;
                stream = new ifstream(file_path.c_str(), ifstream::in);
                if(!stream->is_open()){
                    std::cerr << "Unable to read data from " << file_path << endl;
                    exit(1);
                }

                file_streams.push_back(stream);
            }
        }
        int tmp;
        *file_streams[0] >> tmp;
        current_time = tmp;

        closedir(dir);
    }else{
        cerr << "Unable to read data from "  << folder_path << endl;
    }
}


string BadgeDataReader::filename2id(const char *str){
    boost::regex id_pattern("([1-9]\\d*)");
    boost::smatch match;

    if(boost::regex_search(string(str), match, id_pattern)){
        return string(match[1].first, match[1].second);
    }

    return NULL;
}


void BadgeDataReader::readGraph(){

    int count = 0;
    vector<ifstream *>::iterator file_iterator;
    string node_id;

    int linesize = 256;
    char node_line[linesize];

    time_t time_frame = 0;

    vector<string> adjacent_nodes;
    vector<string>::iterator itan;

    Graph *g = new Graph();
    bool snapshot_created = false;


    for(file_iterator = this->file_streams.begin();
        file_iterator != this->file_streams.end(); ++file_iterator){

        node_id = this->node_ids[count];

        g->addVertex(node_id);

        (*file_iterator)->getline(node_line, linesize);

        if(strlen(node_line) == 0)
            continue;


        adjacent_nodes = this->getAdjacentNodes(string(node_line), time_frame);

        if(time_frame == this->current_time){

            for(itan = adjacent_nodes.begin(); itan != adjacent_nodes.end(); ++itan){

                g->addEdge(node_id, *itan, false);

                if(!snapshot_created){
                    snapshot_created = true;
                    g->setTime(current_time);
                }
            }

        }else if(time_frame > this->current_time){
            //rewind the stream to the beginning of the line we just read

            (*file_iterator)->seekg(-strlen(node_line)- 1, (*file_iterator)->cur);
            exit(1);
        }

        count++;
    }

    if(snapshot_created){
        //        snapshots.push(Snapshot(g, this->new_snapshot_frame, node_ids_to_vertex));

//        cout << "SNAPSHOT CREATED" << endl;

        mtx->lock();

        snapshots.push_back(g);
        mtx->unlock();
    }
    else
        delete(g);

    this->current_time++;

}

/*
vector<string> BadgeDataReader::getAdjacentNodes(const string line, time_t &frame_number){
    boost::regex regex("\\d+");

    boost::sregex_iterator it(line.begin(), line.end(), regex);
    boost::sregex_iterator end;

    vector<string> result;

    it++;
    it++;
    it++;

    frame_number = atoi( it->str().c_str());

    it++;
    it++;

    for(; it != end; ++it){
        result.push_back(it->str());
    }


    return result;
}
*/

vector<string> BadgeDataReader::getAdjacentNodes(const string line, time_t &frame_number){
    boost::regex regex("\\d+");

    boost::sregex_iterator it(line.begin(), line.end(), regex);
    boost::sregex_iterator end;

    vector<string> result;

//    it++;
//    it++;
//    it++;
    frame_number = atoi( it->str().c_str());
//    cout << "FN: " << frame_number << "   " << line << endl;

    if(it != end)
        it++;

    for(; it != end; ++it){
        result.push_back(it->str());
    }

//    cout << "ADCACENT NODES READ" << endl;
    return result;
}
