/*
 * Queue.h
 *
 *  Created on: Apr 17, 2022
 *      Author: Hao
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <omnetpp.h>
#include "Job_m.h"

using namespace omnetpp;

namespace queueingsystem {
class Queue  : public cSimpleModule
{
    private:
        std::list<Job*> jobs;
        simsignal_t qLenSignal;
        simsignal_t qWaitSignal;
        simtime_t time_to_remove_one_job;

    public:
        Queue();
        virtual ~Queue();
        int getQueueLength();
        const bool getServerStatus();
        bool tryToFetchJob();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        //virtual void refreshDisplay() const override;
        virtual void finish() override;
};
};

#endif /* QUEUE_H_ */
