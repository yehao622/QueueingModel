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

#include "Sink.h"

namespace queueingsystem {

Define_Module(Sink);

void Sink::initialize()
{
    total_data_size = 0.0;
    lastArrival = simTime();
    iaTimeHistogram.setName("IO Throughput");
//    arrivalsVector.setName("arrivals");
//    arrivalsVector.setInterpolationMode(cOutVector::NONE);
}

void Sink::handleMessage(cMessage *msg)
{
    Job* j = check_and_cast<Job*>(msg);
    total_data_size += (double)j->getPkg().getByteLength()/(1024.0*1024.0);
    simtime_t d = simTime() - lastArrival;
    delete msg;

    double thrput = total_data_size / simTime().dbl();
    iaTimeHistogram.collect(thrput);
    //arrivalsVector.record(1);

    lastArrival = simTime();
}

void Sink::finish()
{
    recordStatistic(&iaTimeHistogram);
}

}; // namespace
