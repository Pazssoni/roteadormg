#include <algorithm>
#include <sstream>
#include <queue>
#include <tuple>
#include <cctype>
#include <iomanip>
#include <cmath>

#include <omnetpp.h>
#include "RouterNode.h"

using namespace omnetpp;

namespace roteadormg {

class Monitor : public cSimpleModule, public cListener {
  private:
    int numNodes = 0;
    std::string edgesStr;

    struct Edge { int u; int v; simtime_t delay; };
    std::vector<Edge> edges;

    std::vector<std::vector<double>> adj; // adjacency matrix with weights (double seconds)

    long long totalRoutingMessages = 0;
    simtime_t lastTableUpdateTime = SIMTIME_ZERO;

    simsignal_t sigRoutingMsgSent;
    simsignal_t sigTableUpdated;

  protected:
    virtual int numInitStages() const override { return 2; }
    virtual void initialize(int stage) override;
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details) override;
    virtual void finish() override;

    void parseEdges();
    void buildConnections();

    std::vector<double> dijkstraFrom(int src);
    std::vector<std::vector<double>> computeAllPairs();

    static std::string simtimeToString(simtime_t t);
    static std::string formatMatrix(const std::vector<std::vector<double>>& m, const std::string &title);
  public:
    Monitor() {}
    virtual ~Monitor() {}
};

Define_Module(Monitor);

void Monitor::initialize(int stage) {
    if (stage == 0) {
        numNodes = par("numNodes");
        edgesStr = par("edges").stdstringValue();

        sigRoutingMsgSent = registerSignal("routingMsgSent");
        sigTableUpdated = registerSignal("tableUpdated");

        parseEdges();
        buildConnections();
    } else if (stage == 1) {
        // Subscribe to signals on each node
        cModule *net = getParentModule();
        for (int i = 0; i < numNodes; ++i) {
            cModule *node = net->getSubmodule("node", i);
            node->subscribe(sigRoutingMsgSent, this);
            node->subscribe(sigTableUpdated, this);
        }

        // Prepare adjacency for central computation
        adj.assign(numNodes, std::vector<double>(numNodes, 1e15));
        for (int i = 0; i < numNodes; ++i) adj[i][i] = 0.0;
        for (const auto &e : edges) {
            adj[e.u][e.v] = std::min(adj[e.u][e.v], e.delay.dbl());
            adj[e.v][e.u] = std::min(adj[e.v][e.u], e.delay.dbl());
        }
    }
}

void Monitor::receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details) {
    if (signalID == sigRoutingMsgSent) {
        totalRoutingMessages += 1;
    } else if (signalID == sigTableUpdated) {
        lastTableUpdateTime = simTime();
    }
}

void Monitor::parseEdges() {
    edges.clear();
    // edges format: "u-v:delay,u-v:delay,..." delay like 10ms or 0.01s
    std::string s = edgesStr;
    auto trim = [](std::string &x){
        size_t a = x.find_first_not_of(" \t\n\r");
        size_t b = x.find_last_not_of(" \t\n\r");
        if (a == std::string::npos) { x.clear(); return; }
        x = x.substr(a, b - a + 1);
    };

    std::stringstream ss(s);
    std::string tok;
    while (std::getline(ss, tok, ',')) {
        trim(tok);
        if (tok.empty()) continue;
        // split by ':'
        auto posColon = tok.find(':');
        if (posColon == std::string::npos) continue;
        std::string uv = tok.substr(0, posColon);
        std::string delayStr = tok.substr(posColon + 1);
        trim(uv); trim(delayStr);
        // split uv by '-'
        auto posDash = uv.find('-');
        if (posDash == std::string::npos) continue;
        int u = std::stoi(uv.substr(0, posDash));
        int v = std::stoi(uv.substr(posDash + 1));
        simtime_t d = SimTime(delayStr.c_str());
        if (u < 0 || v < 0 || u >= numNodes || v >= numNodes || u == v) continue;
        edges.push_back({u, v, d});
    }
}

void Monitor::buildConnections() {
    // compute degrees
    std::vector<int> degree(numNodes, 0);
    for (const auto &e : edges) { degree[e.u]++; degree[e.v]++; }

    // set gate sizes
    cModule *net = getParentModule();
    for (int i = 0; i < numNodes; ++i) {
        cModule *node = net->getSubmodule("node", i);
        node->setGateSize("gate", degree[i]);
    }

    // assign next free index per node
    std::vector<int> nextIdx(numNodes, 0);

    for (const auto &e : edges) {
        cModule *nu = net->getSubmodule("node", e.u);
        cModule *nv = net->getSubmodule("node", e.v);

        int iu = nextIdx[e.u]++;
        int iv = nextIdx[e.v]++;

        // u -> v
        cGate *uOut = nu->gateHalf("gate", iu, cGate::OUTPUT);
        cGate *vIn  = nv->gateHalf("gate", iv, cGate::INPUT);
        auto chUV = cDelayChannel::create("chan_uv");
        chUV->setDelay(e.delay);
        uOut->connectTo(vIn, chUV);

        // v -> u
        cGate *vOut = nv->gateHalf("gate", iv, cGate::OUTPUT);
        cGate *uIn  = nu->gateHalf("gate", iu, cGate::INPUT);
        auto chVU = cDelayChannel::create("chan_vu");
        chVU->setDelay(e.delay);
        vOut->connectTo(uIn, chVU);
    }
}

std::vector<double> Monitor::dijkstraFrom(int src) {
    const double INF = 1e15;
    std::vector<double> dist(numNodes, INF);
    std::vector<char> vis(numNodes, false);
    using P = std::pair<double,int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    dist[src] = 0.0;
    pq.emplace(0.0, src);
    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        double d = top.first; int u = top.second;
        if (vis[u]) continue; vis[u] = true;
        for (int v = 0; v < numNodes; ++v) {
            if (adj[u][v] >= INF/2) continue;
            double nd = d + adj[u][v];
            if (nd + 1e-12 < dist[v]) { dist[v] = nd; pq.emplace(nd, v);}    
        }
    }
    return dist;
}

std::vector<std::vector<double>> Monitor::computeAllPairs() {
    std::vector<std::vector<double>> res(numNodes);
    for (int s = 0; s < numNodes; ++s) res[s] = dijkstraFrom(s);
    return res;
}

std::string Monitor::simtimeToString(simtime_t t) {
    std::ostringstream os;
    os.setf(std::ios::fixed); os.precision(6);
    os << t.dbl() << " s";
    return os.str();
}

static std::string cell(double v) {
    std::ostringstream os; os.setf(std::ios::fixed); os.precision(3);
    if (v > 1e14) os << "INF"; else os << v;
    return os.str();
}

std::string Monitor::formatMatrix(const std::vector<std::vector<double>>& m, const std::string &title) {
    std::ostringstream os;
    os << "================================================================\n";
    os << "||        MATRIZ DE CUSTOS MÍNIMOS CORRETOS (" << title << ")      ||\n";
    os << "================================================================\n";
    os << "  De\\Para |";
    for (int j = 0; j < (int)m.size(); ++j) { os << std::setw(8) << j << " |"; }
    os << "\n----------------------------------------------------------------\n";
    for (int i = 0; i < (int)m.size(); ++i) {
        os << std::setw(8) << i << " |";
        for (int j = 0; j < (int)m.size(); ++j) os << std::setw(8) << cell(m[i][j]) << " |";
        os << "\n";
    }
    os << "================================================================\n\n";
    return os.str();
}

void Monitor::finish() {
    // Gather final tables from nodes
    std::vector<std::vector<double>> nodeTables(numNodes);
    cModule *net = getParentModule();
    for (int i = 0; i < numNodes; ++i) {
        RouterNode *rn = check_and_cast<RouterNode*>(net->getSubmodule("node", i));
        nodeTables[i] = rn->getDistanceVector();
    }

    auto optimal = computeAllPairs();

    // Config title
    std::string cfg = getEnvir()->getConfig()->getActiveConfigName();

    // Print optimal matrix
    EV << "\n" << formatMatrix(optimal, cfg);

    // Verify consistency
    bool ok = true;
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            double a = nodeTables[i][j];
            double b = optimal[i][j];
            if ((a > 1e14 && b <= 1e14) || (b > 1e14 && a <= 1e14) || fabs(a - b) > 1e-6) {
                ok = false; break;
            }
        }
        if (!ok) break;
    }

    EV << "================================================================\n";
    EV << "||                   RESUMO FINAL DA AVALIAÇÃO                ||\n";
    EV << "================================================================\n";
    EV << "--> Número total de mensagens trocadas: " << totalRoutingMessages << "\n";
    EV << "--> Tempo de convergência da rede: " << simtimeToString(lastTableUpdateTime) << "\n";
    EV << "--> Consistência da tabela de roteamento: " << (ok ? "Verificada. As tabelas dos nós CONVERGIRAM para o resultado correto." : "Falhou. As tabelas dos nós NÃO convergiram para o resultado correto.") << "\n";
    EV << "================================================================\n";
}

} // namespace roteadormg