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

simple Server
{
    parameters:
        @display("i=block/server");
        @signal[averageDataRate](type="double");
        @signal[waitInStation](type="double");
        @statistic[averageDataRate](title="Average IO throughput";record=histogram);
        @statistic[waitInStation](title="Average waiting time in station";record=histogram);
//        @statistic[busy](title="server busy state";record=vector?,timeavg;interpolationmode=sample-hold);

        //string fetchingAlgorithm @enum("priority","random","roundRobin","longestQueue") = default("priority");
             // how the next job will be choosen from the attached queues
        volatile double mds_rate @unit(s) = default(exponential(1e-4s));
        volatile double oss_rate @unit(s) = default(exponential(1.25e-4s));
        volatile double ost_rate @unit(s) = default(exponential(1.25e-2s));
    gates:
        input in[];
        output out;
}
