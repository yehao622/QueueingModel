/*
 * method.cc
 *
 *  Created on: May 3, 2022
 *      Author: Hao
 */

#include "method.h"

std::tuple<Job*, int, int> segmentMsg(Job* j, int block_size=BLOCK_SIZE){
    if(!j)
        throw cRuntimeError("Job is a nullptr!\n");
    if(block_size <= 0)
        throw cRuntimeError("Wrong Block Size setting!\n");
    if(j->getPkg().getByteLength() <= 0)
        throw cRuntimeError("Wrong package size to segment!\n");

    Job* child = j->dup();
    uint64_t data_size = j->getPkg().getByteLength();
    int left_over = data_size % block_size;
    int block_count = data_size/block_size + (left_over>0);
    if(block_count < 0)
        throw cRuntimeError("Block Size is too small, so the block count overflows!\n");

    if(block_count > 1)
        child->getPkg().setByteLength(block_size);
    else
        child->getPkg().setByteLength(left_over);

    return std::make_tuple(child, block_count, left_over);
}
