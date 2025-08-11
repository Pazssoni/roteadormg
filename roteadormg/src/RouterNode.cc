#include <algorithm>
#include <sstream>
#include <cmath>
#include "RouterNode.h"
#include "Routing_m.h"

using namespace omnetpp;

namespace roteadormg {

Define_Module(RouterNode);

void RouterNode::initialize(int stage) {
    if (stage == 0) {
        nodeId = par("nodeId");
        numNodes = par("numNodes");

        sigRoutingMsgSent = registerSignal("routingMsgSent");
        sigTableUpdated = registerSignal("tableUpdated");

        distanceToDestination.assign(numNodes, INF);
        nextHopForDestination.assign(numNodes, -1);
        distanceToDestination[nodeId] = 0.0;

        // neighbor gates will be discovered in stage 1 when connections exist
    } else if (stage == 1) {
        // Discover neighbors via gates and channel delays
        int deg = gateSize("gate");
        neighborIdForGateIndex.assign(deg, -1);
        for (int gi = 0; gi < deg; ++gi) {
            cGate *outg = gateHalf("gate", gi, cGate::OUTPUT);
            if (!outg->isConnected()) continue;
            cGate *next = outg->getNextGate();
            cModule *peer = next->getOwnerModule();
            int peerId = (int)peer->par("nodeId");
            neighborIdForGateIndex[gi] = peerId;

            cChannel *ch = outg->getTransmissionChannel();
            cDelayChannel *dch = dynamic_cast<cDelayChannel*>(ch);
            double delayCost = dch ? dch->getDelay().dbl() : 0.0;
            costToNeighbor[peerId] = delayCost;
            if (peerId >= 0 && peerId < numNodes) {
                distanceToDestination[peerId] = std::min(distanceToDestination[peerId], delayCost);
                if (distanceToDestination[peerId] == delayCost) {
                    nextHopForDestination[peerId] = peerId;
                }
            }
        }

        // Send initial vector to neighbors
        sendDistanceVectorToNeighbors();
    }
}

void RouterNode::handleMessage(cMessage *msg) {
    RoutingUpdate *upd = dynamic_cast<RoutingUpdate*>(msg);
    if (!upd) {
        delete msg;
        return;
    }

    int sender = upd->getSenderId();
    // Ignore if sender not a known neighbor
    auto itCost = costToNeighbor.find(sender);
    if (itCost == costToNeighbor.end()) {
        delete upd;
        return;
    }

    double costToSender = itCost->second;
    bool changed = false;

    int vecSize = upd->getVectorSize();
    for (int d = 0; d < vecSize && d < numNodes; ++d) {
        double senderToD = upd->getDistances(d);
        if (senderToD < 0) continue; // unknown
        double candidate = costToSender + senderToD;
        if (candidate + 1e-12 < distanceToDestination[d]) {
            distanceToDestination[d] = candidate;
            nextHopForDestination[d] = sender;
            changed = true;
        }
    }

    if (changed) {
        emit(sigTableUpdated, (long)1);
        sendDistanceVectorToNeighbors();
    }

    delete upd;
}

void RouterNode::sendDistanceVectorToNeighbors() {
    int deg = gateSize("gate");
    // build a single vector once
    RoutingUpdate *templateMsg = new RoutingUpdate();
    templateMsg->setSenderId(nodeId);
    templateMsg->setVectorSize(numNodes);
    templateMsg->setDistancesArraySize(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        double v = distanceToDestination[i];
        templateMsg->setDistances(i, std::isfinite(v) && v < INF/2 ? v : -1.0);
    }

    for (int gi = 0; gi < deg; ++gi) {
        if (!gateHalf("gate", gi, cGate::OUTPUT)->isConnected()) continue;
        RoutingUpdate *msg = templateMsg->dup();
        send(msg, "gate$o", gi);
        emit(sigRoutingMsgSent, (long)1);
    }

    delete templateMsg;
}

} // namespace roteadormg