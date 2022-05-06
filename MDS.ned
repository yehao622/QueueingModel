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

module MDS
{
    parameters:
        int core_count = default(16);
        @display("bgb=415,282;i=device/server;is=n");
    gates:
        input in;
        output out;
    submodules:
        mdsEntry: Router {
            @display("p=140,200");
        }
        mdsQueue[core_count]: Queue {
            @display("p=140,108");
        }
        mdsCore[core_count]: Server {
            @display("p=298,108");
        }
        mdsExit: Router {
            @display("p=298,200");
        }
    connections:
        in --> mdsEntry.in++;
        for i=0..core_count-1 {
            mdsEntry.out++ --> mdsQueue[i].in++;
            mdsQueue[i].out --> mdsCore[i].in++;
            mdsCore[i].out --> mdsExit.in++;
        }
        mdsExit.out++ --> out;
}
