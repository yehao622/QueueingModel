/*
 * Router.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Hao
 */

#ifndef ROUTER_H_
#define ROUTER_H_

#include <omnetpp.h>
#include "Job_m.h"
#include "Queue.h"
#include "method.h"

using namespace omnetpp;

namespace queueingsystem {
class Router  : public cSimpleModule
{
    private:
        std::unordered_map<std::string, int> gates_map;
    public:
        Router();
        virtual ~Router();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};
};


#endif /* ROUTER_H_ */
