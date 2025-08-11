#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include "Monitor.h"

Define_Module(Monitor);

void Monitor::finish()
{
    cModule *network = getParentModule();
    int n = network->par("totalNodes");

    // 1. Construir o grafo a partir da topologia
    std::vector<std::vector<std::pair<int, double>>> adj(n);
    for (int i = 0; i < n; i++) {
        cModule *node = network->getSubmodule("node", i);
        for (int j = 0; j < node->gateSize("g"); j++) {
            if (node->gate("g$o", j)->isConnected()) {
                cChannel *channel = node->gate("g$o", j)->getChannel();
                if (channel) {
                    int neighborId = node->gate("g$o", j)->getPathEndGate()->getOwnerModule()->getIndex();
                    double cost = channel->par("delay").doubleValue() * 1000;
                    adj[i].push_back({neighborId, cost});
                }
            }
        }
    }

    // 2. Rodar Dijkstra para cada nó para encontrar os caminhos mais curtos
    std::vector<std::vector<double>> shortestPaths(n, std::vector<double>(n, INFINITY));
    for (int startNode = 0; startNode < n; startNode++) {
        std::vector<double>& dist = shortestPaths[startNode];
        dist[startNode] = 0;
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
        pq.push({0.0, startNode});
        while (!pq.empty()) {
            double d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (d > dist[u]) continue;
            for (auto& edge : adj[u]) {
                int v = edge.first;
                double weight = edge.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // 3. Imprimir a matriz de custos correta e final
    EV << "\n\n================================================================================\n";
    EV << "||        MATRIZ DE CUSTOS MÍNIMOS CORRETOS (Calculada pelo Monitor)        ||\n";
    EV << "================================================================================\n";
    EV << "  De\\Para |";
    for (int j = 0; j < n; j++) { EV << std::setw(8) << std::right << j << " |"; }
    EV << "\n--------------------------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        EV << "   " << std::setw(4) << std::left << i << " |";
        for (int j = 0; j < n; j++) {
            double cost = shortestPaths[i][j];
            if (cost >= INFINITY) { EV << std::setw(8) << std::right << "inf" << " |"; }
            else { EV << std::setw(8) << std::right << cost << " |"; }
        }
        EV << "\n";
    }
    EV << "================================================================================\n";
}
