/*
 * Router.cc
 *
 *  Created on: Apr 18, 2022
 *      Author: Hao
 */

#include "Router.h"

namespace queueingsystem {

Define_Module(Router);

Router::Router(){}

Router::~Router(){}

void Router::initialize(){
    int num_out = gateSize("out");

    if(strcmp(getFullName(), "mds_oss") == 0){
        if(num_out != OSS_NUM)
            throw cRuntimeError("%d of OSSes has been configured, but not equal to OSS_NUM in 'method.h'", num_out);
    }

    for(int i=0 ;i<num_out; i++){
        cGate* g = gate("out", i);
        gates_map[g->getNextGate()->getOwnerModule()->getFullName()] = i;
    }
}

void Router::handleMessage(cMessage *msg){
    Job *job = check_and_cast<Job*>(msg);
    int num_out = gateSize("out");
    int out_to_gate = intuniform(0, num_out-1);

    if(strcmp(getFullName(), "mds_oss") == 0){
//        if(job->getAssigned_oss_id() == -1){ // work from mds
//            job->setAssigned_oss_id(out_to_gate);
//            bubble("mds send to oss!");
//        }else{ // work from osts
        out_to_gate = job->getAssigned_oss_id();
//            bubble("oss send to client!");
//        }
        send(job, "out", out_to_gate);
    }else if(strcmp(getFullName(), "oss_ost") == 0){
        if((job->getCached()||job->getBack_from_ost()) && job->getWork_type()=='r'){ // read data if cached or returned from osts, send to client(sink)
            send(job, "out", gates_map["sink"]);
//            bubble("cached data on oss send to client!");
        }else{ // randomly select one ost set(here assume each oss connects with all osts, and the workload is uniformly distributed)
            while(out_to_gate == gates_map["sink"])  // Avoid send back to client
                out_to_gate = intuniform(0, num_out-1);
            send(job, "out", out_to_gate);
//            bubble("send to ost!");
        }
    }else if(strcmp(getFullName(), "ost_sink") == 0){
        if(job->getWork_type() == 'r'){
            send(job, "out", gates_map["mds_oss"]);
//            bubble("ost send to oss!");
        }else{
            send(job, "out", gates_map["sink"]);
//            bubble("write finished!");
        }
    }else
        send(job, "out", out_to_gate);

//    cGate* g = gate("out", out_to_gate);
//    std::string next_module_class_name = g->getNextGate()->getOwnerModule()->getNedTypeName();
//    if(strcmp(next_module_class_name.c_str(), "queueingsystem.Queue") == 0){ // Choose least queue length
//        int qlen(INT_MAX);
//        for(int i=0; i<num_out; i++){
//            g = gate("out", i);
//            Queue* q = check_and_cast<Queue*>(g->getNextGate()->getOwnerModule());
//            if(q->getServerStatus()){
//                out_to_gate = i;
//                break;
//            }else if(qlen > q->getQueueLength()){
//                qlen = q->getQueueLength();
//                out_to_gate = i;
//            }
//        }
//    }

}

};



