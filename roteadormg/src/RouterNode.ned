package roteadormg;

simple RouterNode
{
    parameters:
        int nodeId;
        int numNodes;
        @display("i=block/router");
    gates:
        inout gate[]; // neighbor links will be assigned by Monitor
}