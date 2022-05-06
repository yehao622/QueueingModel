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

package queueingsystem;

module OST
{
    parameters:
        int count = default(10);
        @display("bgb=413,280;i=device/disk;is=n");
    gates:
        input in;
        output out;
    submodules:
        ostEntry: Router {
            @display("p=179,200");
        }
        ostQueue[count]: Queue {
            @display("p=179,108");
        }
        ostCore[count]: Server {
            @display("p=298,108");
        }
        ostExit: Router {
            @display("p=298,200");
        }
    connections:
        in --> ostEntry.in++;
        for i=0..count-1 {
            ostEntry.out++ --> ostQueue[i].in++;
            ostQueue[i].out --> ostCore[i].in++;
            ostCore[i].out --> ostExit.in++;
        }
        ostExit.out++ --> out;
}
