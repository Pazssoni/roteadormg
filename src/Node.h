#ifndef __PROJETOROTEAMENTO_NODE_H_
#define __PROJETOROTEAMENTO_NODE_H_

#include <omnetpp.h>
#include <vector>
#include "DVMessage_m.h"

using namespace omnetpp;

struct Route {
    double cost = INFINITY;
    int nextHopGateIndex = -1;
};

class Node : public cSimpleModule
{
  private:
    int totalNodes;
    std::vector<Route> routingTable;
    simsignal_t sentMessagesSignal;
    simsignal_t routingTableUpdatesSignal;
    cOutVector convergenceTimeVector;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    void broadcastDistanceVector();
};
#endif
