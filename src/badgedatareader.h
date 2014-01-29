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
 *  @file badgedatareader.h
 *  @author Dimo Stoyanov
 *  @brief The class used to parse badge data files.
 */

#ifndef BADGEDATAREADER_H
#define BADGEDATAREADER_H

#include "datareader.h"

class BadgeDataReader : public DataReader
{
public:

    /**
     * @param folder_path the path were the nodelogs are stored.
     */
    BadgeDataReader(string folder_path);

    void readGraph();

private:
    /**
     * Extracts the node id from str which is the file name for the
     * coresponding nodelog.
     */
    string filename2id(const char *str);

    /**
     * Extracts the adjacent nodes from a line in the nodelog
     */
    vector<string> getAdjacentNodes(const string line, time_t &frame);

};

#endif // BADGEDATAREADER_H
