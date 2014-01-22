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

#ifndef DATAREADER_H
#define DATAREADER_H

#include <vector>
#include <queue>
#include <fstream>

#include<boost/thread.hpp>

#include "graph.h"

using namespace std;

//class BadgeDataReader;

class DataReader
{
public:
    DataReader();

    ~DataReader();

    Graph* getSnapshot();

    Graph* getSnapshot(int i);

    void fillGraphBuffer();

    int getStreamSize(){return file_streams.size();}

    void setMaxNumSnapshots(int mns);

    int getNumberSnapshots();

protected:
    string folder_path;

    deque<Graph *> snapshots;

    time_t current_time;

    vector<string> node_ids;
    vector<ifstream *> file_streams;

    string filename2id(const char *str);

    boost::mutex *mtx;

private:
    virtual void readGraph() = 0;

    int max_num_snapshots;

};

#endif // DATAREADER_H
