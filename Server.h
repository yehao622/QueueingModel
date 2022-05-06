/*
 * Server.h
 *
 *  Created on: Apr 16, 2022
 *      Author: Hao
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <omnetpp.h>
#include "Job_m.h"
#include "method.h"

#define STRIPE_SIZE 65536
#define STRIPE_COUNT 2
#define CACHE_HIT_RATIO 0.3

using namespace omnetpp;

namespace queueingsystem {
class Server : public cSimpleModule
{
    private:
        int job_count;
        bool free_status;
        simsignal_t avgThroughput;
        simsignal_t sWaitSignal;
        simtime_t end_time;
        simtime_t last_visit_time;
        double bandwidth;
        void updateTimeStamp();
        void updateTimeStamp(Job* j);
        void mdsSendMessage(Job* j);
        void ossSendMessage(Job* j);
        void ostSendMessage(Job* j);

    public:
        Server();
        virtual ~Server();
        virtual bool isIdle();
        simtime_t getEndTimeStamp();
        simtime_t genRandomDelay();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
//        virtual void refreshDisplay() const override;
        virtual void finish() override;
};

}; //namespace



#endif /* SERVER_H_ */
