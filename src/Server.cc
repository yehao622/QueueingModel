/*
 * Server.cc
 *
 *  Created on: Apr 16, 2022
 *      Author: Hao
 */

#include "Server.h"
#include <thread>
#include "Queue.h"

namespace queueingsystem {

Define_Module(Server);

Server::Server(){}

Server::~Server(){}

void Server::initialize(){
    job_count = 0;
    free_status = true;
    avgThroughput = registerSignal("averageDataRate");
    sWaitSignal = registerSignal("waitInStation");
    end_time = simTime();
    last_visit_time = simTime();
    bandwidth = 1024.0; // 1G per second

    int num_in = gateSize("in");
//    int num_out = gateSize("out");

    for(int i=0; i<num_in; i++){
        cGate* gin = gate("in", i);
        std::string prev_module_class_name = gin->getPreviousGate()->getOwnerModule()->getNedTypeName();
        if(strcmp(prev_module_class_name.c_str(), "queueingsystem.Queue")){
            EV_ERROR << "Server module should follow a Queue class module!\n";
        }
    }

//    for(int i=0; i<num_out; i++){
//        cGate* gout = gate("out", i);
        cGate* gout = gate("out");
        std::string next_module_class_name = gout->getNextGate()->getOwnerModule()->getNedTypeName();
        if(strcmp(next_module_class_name.c_str(), "queueingsystem.Server") == 0){
            EV_ERROR << "Two Server modules shall not connect directly!\n";
        }
//    }
}

simtime_t Server::genRandomDelay(){
    double delay_time(-1.0);

    if(strcmp(getName(), "mdsCore") == 0){
        delay_time = par("mds_rate").doubleValue();
    }else if(strcmp(getName(), "ossCore") == 0){
        delay_time = par("oss_rate").doubleValue();
    }else if(strcmp(getName(), "ostCore") == 0){
        delay_time = par("ost_rate").doubleValue();
    }else
        throw cRuntimeError("Server has no corresponding rule at %s!\n", getName());

    return delay_time;
}

simtime_t Server::getEndTimeStamp(){
    return end_time;
}

void Server::updateTimeStamp(){
    end_time = simTime() + genRandomDelay();
}

void Server::updateTimeStamp(Job* j){
    if(strcmp(getName(), "ossCore")==0 || strcmp(getName(), "ostCore")==0)
        end_time = simTime() + (double)j->getPkg().getByteLength()/(1024.0*1024.0) * genRandomDelay();
    else if(strcmp(getName(), "mdsCore") == 0)
        updateTimeStamp();
    else
        throw cRuntimeError("Server has no corresponding rule at %s!\n", getName());
}

void Server::mdsSendMessage(Job* j){
    updateTimeStamp(j);
    j->setLeave_time_server(end_time);
    emit(sWaitSignal, (j->getLeave_time_server() - j->getArrive_time_queue()).dbl());
    int out_to_oss_index = intuniform(0, OSS_NUM-1);
    j->setAssigned_oss_id(out_to_oss_index);
//    if(j->getWork_type() == 'r'){
        sendDelayed(j, end_time-simTime(), "out");
//    }else{
        std::tuple<Job*, int, int> res = segmentMsg(j, BLOCK_SIZE);
//    EV <<j->getPkg().getByteLength() << " :: " << std::get<0>(res)->getPkg().getByteLength() << " ==> "
//         << std::get<1>(res) << " ==> " << std::get<2>(res) << " !!!\n";
//    }
}

void Server::ossSendMessage(Job* j){
    if(j->getPkg().getByteLength() <= 0)
            throw cRuntimeError("Wrong package date size at %s\n", getName());

    simtime_t latest = end_time;
    long long left_size, cache_size;
    if(j->getWork_type() == 'r'){
        left_size = j->getPkg().getByteLength() * (1.0-CACHE_HIT_RATIO);
        cache_size = j->getPkg().getByteLength() - left_size;
    }else{
        left_size = j->getPkg().getByteLength();
        cache_size = 0;
    }


    // deal with cache-missed data
    int split = left_size/STRIPE_SIZE + (left_size%STRIPE_SIZE>0);
    split = std::min(split, STRIPE_COUNT);
    long long split_size(left_size / split);

    while(split > 0){
        Job* sub_job = new Job();
        sub_job = j->dup();
        if(split == 1)
            sub_job->getPkg().setByteLength(left_size);
        else
            sub_job->getPkg().setByteLength(split_size);
        left_size -= split_size;
        split--;
        if(sub_job->getWork_type()=='r' && !sub_job->getBack_from_ost()) // if read request from mds(not carry the data)
            updateTimeStamp();
        else
            updateTimeStamp(sub_job);
        latest = std::max(latest, end_time);
        sub_job->setLeave_time_server(end_time);
        emit(sWaitSignal, (sub_job->getLeave_time_server() - sub_job->getArrive_time_queue()).dbl());
        sendDelayed(sub_job, end_time-simTime(), "out");
    }

     //for cached data
    if(cache_size > 0){
        Job* cached_job = new Job();
        cached_job = j->dup();
        cached_job->setCached(true);
        cached_job->getPkg().setByteLength(cache_size);
        updateTimeStamp(cached_job);
        latest = std::max(latest, end_time);
        cached_job->setLeave_time_server(end_time);
        emit(sWaitSignal, (cached_job->getLeave_time_server() - cached_job->getArrive_time_queue()).dbl());
        sendDelayed(cached_job, end_time-simTime(), "out");
    }

    delete j;
    end_time = latest;
}

void Server::ostSendMessage(Job* j){
    updateTimeStamp(j);
    j->setLeave_time_server(end_time);
    j->setBack_from_ost(true);
    emit(sWaitSignal, (j->getLeave_time_server() - j->getArrive_time_queue()).dbl());
    sendDelayed(j, end_time-simTime(), "out");
}

void Server::handleMessage(cMessage *msg){
    Job *job = check_and_cast<Job*>(msg);

    if(!job->isSelfMessage()){
        job_count++;
        free_status = false;
        job->setArrive_time_server(simTime());

        if(strcmp(getName(), "mdsCore") == 0){
            mdsSendMessage(job);
        }else if(strcmp(getName(), "ossCore") == 0){
            ossSendMessage(job);
        }else if(strcmp(getName(), "ostCore") == 0){
            ostSendMessage(job);
        }else{
            cRuntimeError("Need to implement new module!");
        }

        scheduleAt(end_time, new Job());

        if((simTime()-last_visit_time).dbl() >= 0.01){
            double instant_rate = (double)job_count / (simTime()-last_visit_time).dbl();
            last_visit_time = simTime();
            emit(avgThroughput, instant_rate);
            job_count = 0;
        }
    }else{
        delete job;
        free_status = true;

//        int num_in = gateSize("in");
//        for(int i=0; i<num_in; i++){
//            cGate* gin = gate("in", i);
//            Queue* q = check_and_cast<Queue*>(gin->getPreviousGate()->getOwnerModule());
//            if(q->tryToFetchJob()){
//                break;
//            }
//        }
    }
}

/*void Server::refreshDisplay() const {
    getDisplayString().setTagArg("i2", 0, jobServiced ? "status/execute" : "");
}*/

void Server::finish(){}

bool Server::isIdle(){
    return (simTime()>=end_time) && free_status;
}

};
