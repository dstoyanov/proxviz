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


#ifndef BADGEDATAREADER_H
#define BADGEDATAREADER_H

#include "datareader.h"

class BadgeDataReader : public DataReader
{
public:
//    BadgeDataReader() : DataReader(){};

    BadgeDataReader(string folder_path);

//    BadgeDataReader(const BadgeDataReader& bdr) {(void)bdr;};

    void readGraph();

private:
//    time_t next_snapshot_time;
    string filename2id(const char *str);

    vector<string> getAdjacentNodes(const string line, time_t &frame);

};

#endif // BADGEDATAREADER_H
