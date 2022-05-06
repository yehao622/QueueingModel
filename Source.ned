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

//
// Generates messages with a configurable interarrival time.
//
simple Source
{
    parameters:
//        @signal[created](type="simtime_t");
//        @statistic[created](title="the number of jobs created";record=histogram);
//        @statistic[uniquecreated](source=sum(created);record=vector(removeRepeats););
        volatile double sendInterval @unit(s) = default(exponential(2e-5s));
        
        volatile double avgPkgSize1 = default(poisson(1.0));
        volatile double sendInterval1 @unit(s) = default(exponential(2e-5s));
        volatile double avgPkgSize2 = default(poisson(10.0));
        volatile double sendInterval2 @unit(s) = default(exponential(2e-4s));
        volatile double avgPkgSize3 = default(poisson(1e+2));
        volatile double sendInterval3 @unit(s) = default(exponential(2e-3s));
        volatile double avgPkgSize4 = default(poisson(1e+3));
        volatile double sendInterval4 @unit(s) = default(exponential(2e-2s));
        volatile double avgPkgSize5 = default(poisson(1e+4));
        volatile double sendInterval5 @unit(s) = default(exponential(2e-1s));
        volatile double avgPkgSize6 = default(poisson(1e+6));
        volatile double sendInterval6 @unit(s) = default(exponential(20.0s));
        @display("i=block/source");
    gates:
        output out;
}
