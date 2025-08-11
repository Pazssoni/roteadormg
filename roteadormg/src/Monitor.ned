package roteadormg;

simple Monitor
{
    parameters:
        int numNodes;
        string edges;
        @display("i=block/process");
    gates:
        inout gate[];
}