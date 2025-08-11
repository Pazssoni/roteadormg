#include "Node.h"

Define_Module(Node);

void Node::initialize()
{
    totalNodes = par("totalNodes");
    routingTable.resize(totalNodes);
    routingTable[getIndex()] = {0.0, -1};

    for (int i = 0; i < gateSize("g"); i++) {
        if (gate("g$o", i)->isConnected()) {
            cChannel *channel = gate("g$o", i)->getChannel();
            if (channel) {
                int neighborIndex = gate("g$o", i)->getPathEndGate()->getOwnerModule()->getIndex();
                double linkCost = channel->par("delay").doubleValue() * 1000;
                if (linkCost < routingTable[neighborIndex].cost) {
                    routingTable[neighborIndex] = {linkCost, i};
                }
            }
        }
    }

    routingTableUpdatesSignal = registerSignal("routingTableUpdate");
    sentMessagesSignal = registerSignal("sentMessage");
    convergenceTimeVector.setName("Convergence Time");
    scheduleAt(simTime() + uniform(0.01, 0.05), new cMessage("broadcastTimer"));
}

void Node::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        broadcastDistanceVector();
        delete msg;
        return;
    }

    DVMessage *dvMsg = check_and_cast<DVMessage *>(msg);
    cGate *arrivalGate = dvMsg->getArrivalGate();
    if (!arrivalGate || !arrivalGate->getPathEndGate() || !arrivalGate->getChannel()) {
        delete dvMsg;
        return;
    }

    double costToNeighbor = arrivalGate->getChannel()->par("delay").doubleValue() * 1000;
    bool tableUpdated = false;

    for (unsigned int i = 0; i < dvMsg->getDistanceVectorArraySize(); i++) {
        const RoutingEntry& entry = dvMsg->getDistanceVector(i);
        int destination = entry.destinationNode;
        double costFromNeighbor = entry.cost;
        if (costFromNeighbor >= INFINITY) continue;

        double newCost = costToNeighbor + costFromNeighbor;
        if (newCost < routingTable[destination].cost) {
            routingTable[destination] = {newCost, arrivalGate->getIndex()};
            tableUpdated = true;
        }
    }

    if (tableUpdated) {
        emit(routingTableUpdatesSignal, 1);
        convergenceTimeVector.record(simTime().dbl());
        scheduleAt(simTime() + 0.001, new cMessage("broadcastTimer"));
    }

    delete dvMsg;
}

void Node::broadcastDistanceVector()
{
    DVMessage *msg = new DVMessage("distanceVector");
    msg->setDistanceVectorArraySize(totalNodes);
    for (int i = 0; i < totalNodes; i++) {
        RoutingEntry entry;
        entry.destinationNode = i;
        entry.cost = routingTable[i].cost;
        msg->setDistanceVector(i, entry);
    }
    for (int i = 0; i < gateSize("g"); i++) {
        if (gate("g$o", i)->isConnected()) {
            send(msg->dup(), "g$o", i);
            emit(sentMessagesSignal, 1);
        }
    }
    delete msg;
}

void Node::finish()
{
    // A saída dos nós individuais pode ser usada como um log de depuração.
    // O resultado final validado virá do Monitor.
}
