cplusplus {
#include <vector>
}

namespace roteadormg;

message RoutingUpdate {
    int senderId;
    int vectorSize;
    double distances[];
}