/*
 * method.h
 *
 *  Created on: May 3, 2022
 *      Author: Hao
 */

#ifndef METHOD_H_
#define METHOD_H_

#include "Job_m.h"
#include <tuple>
#include <unordered_map>

#define BLOCK_SIZE 8192
#define OSS_NUM 4

using namespace omnetpp;

std::tuple<Job*, int, int> segmentMsg(Job*, int); // return a job; its repetition number; the data size of last job

#endif /* METHOD_H_ */
