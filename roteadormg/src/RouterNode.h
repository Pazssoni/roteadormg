#ifndef __ROTEADORMG_ROUTERNODE_H_
#define __ROTEADORMG_ROUTERNODE_H_

#include <omnetpp.h>
#include <vector>
#include <unordered_map>

using namespace omnetpp;

namespace roteadormg {

class RouterNode : public cSimpleModule {
  private:
    int nodeId = -1;
    int numNodes = 0;

    std::vector<double> distanceToDestination;
    std::vector<int> nextHopForDestination;

    std::vector<int> neighborIdForGateIndex; // index -> neighborId
    std::unordered_map<int, double> costToNeighbor; // neighborId -> cost

    simsignal_t sigRoutingMsgSent;
    simsignal_t sigTableUpdated;

    static constexpr double INF = 1e15;

  protected:
    virtual int numInitStages() const override { return 2; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    void sendDistanceVectorToNeighbors();

  public:
    const std::vector<double>& getDistanceVector() const { return distanceToDestination; }
};

} // namespace roteadormg

#endif