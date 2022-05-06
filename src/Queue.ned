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

simple Queue
{
    parameters:
        @signal[queueLength](type="int");
        @signal[queueWaiting](type="double");
//        @statistic[queueLength](title="Length of the queue";record=stats,histogram);
        @statistic[queueLength](title="Length of the queue";record=stats);
        @statistic[queueWaiting](title="Waiting time within queue";record=stats);
        @display("i=block/passiveq");
    gates:
        input in[];
        output out;
}