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
 *  @file ubidatareader.h
 *  @author Dimo Stoyanov
 *  @brief The class used to parse ubisense data files.
 */
#ifndef UBIDATAREADER_H
#define UBIDATAREADER_H

#include "datareader.h"

#include <ctime>

namespace bt = boost::posix_time;

class UbiDataReader : public DataReader
{
public:
//    UbiDataReader() : DataReader(){};

    UbiDataReader(string folder_path, double range=1.5);

    void readGraph();

    void setRange(double range);
    void recomputeAllSnapshotVertices(double range);

private:
    double range;

    bool stringToVertex(const char* line, string &id, time_t &time,
                        float &x, float &y);

    time_t extractTime(string line);
    string extractId(string line);
    bool extractCoordinates(string line, float &x, float &y);

    std::time_t pt_to_time_t(const bt::ptime &pt);

};

#endif // UBIDATAREADER_H
