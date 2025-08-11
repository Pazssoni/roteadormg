//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

import ned.DelayChannel;

network Topologia1
{
    parameters:
        int totalNodes = 7; // Essencial para o Monitor
    submodules:
        node[totalNodes]: Node {}
        monitor: Monitor {}
    connections:
        // Suas conexões aqui
        node[0].g++ <--> DelayChannel { delay = 10ms; } <--> node[1].g++;
        node[0].g++ <--> DelayChannel { delay = 2ms; } <--> node[2].g++;
        node[1].g++ <--> DelayChannel { delay = 4ms; } <--> node[2].g++;
        node[1].g++ <--> DelayChannel { delay = 8ms; } <--> node[3].g++;
        node[2].g++ <--> DelayChannel { delay = 3ms; } <--> node[4].g++;
        node[3].g++ <--> DelayChannel { delay = 5ms; } <--> node[5].g++;
        node[4].g++ <--> DelayChannel { delay = 1ms; } <--> node[5].g++;
        node[5].g++ <--> DelayChannel { delay = 12ms; } <--> node[6].g++;
}