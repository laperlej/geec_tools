#ifndef RPTREELEAFNODE_H
#define RPTREELEAFNODE_H



// ***************************************************************************
//   RPTreeLeafNode.h (c) 2014
//   Copyright @ Alexei Nordell-Markovits : Sherbrooke University
//
//    This file is part of the BWReader library.
//
//    The BWReader library is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU  General Public License
//    along with this program (gpl-3.0.txt).  If not, see <http://www.gnu.org/licenses/>.
// ***************************************************************************


#include "RPTreeNode.h"
#include "RPChromosomeRegion.h"
#include "RPTreeLeafNodeItem.h"

#include <vector>


class RPTreeLeafNode : public RPTreeNode
{
    public:
         bool isLeaf();
        RPChromosomeRegion* getChromosomeBounds();
        int32_t compareRegions(RPChromosomeRegion* chromosomeRegion);
        int32_t getItemCount();
        RPTreeNodeItem* getItem(int32_t index);
        bool insertItem(RPTreeNodeItem* item);
        bool deleteItem(int32_t index);

        RPTreeLeafNode();
        virtual ~RPTreeLeafNode();
    protected:
    private:

    RPChromosomeRegion* chromosomeBounds_;    //  bounds for entire node
    std::vector<RPTreeLeafNodeItem*> leafItems_;   // array for leaf items
};

#endif // RPTREELEAFNODE_H
