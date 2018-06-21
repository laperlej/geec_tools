#ifndef RPTREECHILDNODEITEM_H
#define RPTREECHILDNODEITEM_H



// ***************************************************************************
//   RPTreeChildNodeItem.h (c) 2014
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



#include "RPTreeNodeItem.h"
#include "RPTreeNode.h"

class RPTreeChildNodeItem : public RPTreeNodeItem
{
    public:
        RPTreeChildNodeItem();

        RPTreeChildNodeItem(uint32_t startChromID, uint32_t startBase, uint32_t endChromID, uint32_t endBase, RPTreeNode* childNode);
        RPTreeChildNodeItem(uint32_t startChromID, uint32_t startBase, uint32_t endChromID, uint32_t endBase, uint64_t childDataOffset);
        RPChromosomeRegion* getChromosomeBounds();
        RPTreeNode* getChildNode();
        uint32_t compareRegions(RPChromosomeRegion* chromosomeRegion);


        virtual ~RPTreeChildNodeItem();


    protected:
    private:

        RPChromosomeRegion* chromosomeBounds_;
        RPTreeNode* childNode_;
};

#endif // RPTREECHILDNODEITEM_H