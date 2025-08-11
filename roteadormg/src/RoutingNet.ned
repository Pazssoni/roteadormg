package roteadormg;

network RoutingNet
{
    parameters:
        int numNodes;
        string edges; // comma-separated "u-v:delay" list, e.g. "0-1:10ms,0-2:2ms"
    submodules:
        monitor: Monitor {
            parameters:
                numNodes = numNodes;
                edges = default(edges);
                @display("p=100,50");
            gates:
                gate[numNodes];
        }
        node[numNodes]: RouterNode {
            parameters:
                nodeId = index;
                numNodes = numNodes;
                @display("i=block/router");
            gates:
                gate[];
        }
}