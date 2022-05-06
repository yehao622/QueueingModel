//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Source.h"

namespace queueingsystem {

Define_Module(Source);

Source::Source(){}

Source::~Source(){}

void Source::initialize()
{
//    createdSignal = registerSignal("created");
//    cResultFilter *removeRepeatsFilter = cResultFilterType::get("removeRepeats")->create();
//    cResultRecorder *vectorRecorder = cResultRecorderType::get("vector")->create();
//    opp_string_map *attrs = new opp_string_map;
//    (*attrs)["title"] = "Title";
//    (*attrs)["unit"] = "seconds";
//    vectorRecorder->init(this, "uniquecreated", "vector", nullptr, attrs);
//    removeRepeatsFilter->addDelegate(vectorRecorder);

    id = 0;
    if(strcmp(getName(), "source") == 0){
        Job *timerMessage = new Job();
        scheduleAt(simTime(), timerMessage);
    }
}

void Source::handleMessage(cMessage *msg)
{
//    emit(createdSignal, simTime());
    if(id == UINT_MAX)  endSimulation();

    Job *job = check_and_cast<Job*>(msg);
    job->setCached(false);
    job->setBack_from_ost(false);
    job->setAssigned_oss_id(-1);
    job->setJob_id(id);
    cPacket pkg = cPacket(job->getPkg());
    double data_size = par("avgPkgSize5");
    pkg.setByteLength((long long)data_size*1024*1024);
    job->setPkg(pkg);
    job->setInit_data_size(data_size*1024*1024);
    if(uniform(0.0, 1.0, 0)<2.0)
        job->setWork_type('r');
    else
        job->setWork_type('w');
    job->setArrive_time_queue(simTime());
    job->setLeave_time_queue(simTime());
    job->setArrive_time_server(simTime());
    job->setLeave_time_server(simTime());
    send(job, "out"); // source module has only one output gate

    Job *timerMessage = new Job();
    timerMessage->setArrive_time_queue(simTime());
    timerMessage->setLeave_time_queue(simTime());
    timerMessage->setArrive_time_server(simTime());
    timerMessage->setLeave_time_server(simTime());
    scheduleAt(simTime()+par("sendInterval5").doubleValue(), timerMessage);
    id++;
}

void Source::finish(){}

}; // namespace
