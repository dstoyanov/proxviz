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

#include "datareader.h"
#include <fstream>

DataReader::DataReader(){
//    this->mtx = new boost::mutex();

    this->mtx = NULL;

    max_num_snapshots = -1;
}

DataReader::~DataReader(){
    std::vector<ifstream *>::iterator si;

//    cout << "SIZE " << file_streams.size() << "  " << snapshots.size() << endl;

    for(si = file_streams.begin(); si != file_streams.end(); ++si){
        (*si)->close();
        delete(*si);
    }

    while(!snapshots.empty()){
        delete(snapshots.front());
        snapshots.pop_front();
    }

    delete(mtx);
}

Graph* DataReader::getSnapshot(){
    Graph *g;

    g = NULL;

    mtx->lock();
    if(snapshots.size() > 0){
        g = snapshots.front();
        snapshots.pop_front();
    }
    mtx->unlock();

    return g;
}

Graph* DataReader::getSnapshot(int i){
    return snapshots[i];
}

void DataReader::fillGraphBuffer(){
    int size;

    while(true){

        mtx->lock();
        size = snapshots.size();
        mtx->unlock();

        if(size < max_num_snapshots || max_num_snapshots == -1){
            readGraph();
        }
    }
}

void DataReader::setMaxNumSnapshots(int mns){
    max_num_snapshots = mns;
}

int DataReader::getNumberSnapshots(){
    return snapshots.size();
}
