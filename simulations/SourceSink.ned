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

package queueingsystem.simulations;

import queueingsystem.OSS;
import queueingsystem.OST;
import queueingsystem.Router;
import queueingsystem.Source;
import queueingsystem.Sink;
import queueingsystem.MDS;

//
// Sample network, consisting of a source and a sink.
//

network SourceSink
{
    parameters:
        int oss_num = 4;
        @display("bgb=656,272");
    submodules:
        source: Source {
            @display("p=29,113");
        }
        sink: Sink {
            @display("p=477,39");
        }
        mds: MDS {
            @display("p=98,113");
        }
        mds_oss: Router {
            @display("p=173,194");
        }
        oss[oss_num]: OSS {
            @display("p=249,113");
        }
        ost_sink: Router {
            @display("p=477,187");
        }
        ost[oss_num]: OST {
            @display("p=410,113");
        }
        oss_ost: Router {
            @display("p=322,113");
        }
    connections:
        source.out --> mds.in;
        mds.out --> mds_oss.in++;
        for i=0..oss_num-1 {
            mds_oss.out++ --> oss[i].in;
            oss[i].out --> oss_ost.in++;
            oss_ost.out++ --> ost[i].in;
            ost[i].out --> ost_sink.in++;
        }
        ost_sink.out++ --> sink.in++;
        oss_ost.out++ --> sink.in++;
        ost_sink.out++ --> mds_oss.in++;
}
