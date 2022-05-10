#ifndef BIGBEDITERATOR_H
#define BIGBEDITERATOR_H

// ***************************************************************************
//   BigBedIterator.h (c) 2014
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



#include <iterator>
#include "BPTree.h"
#include "RPTreeLeafNodeItem.h"
#include "RPTree.h"
#include "BigBedDataBlock.h"


class BigBedIterator : public std::iterator<std::input_iterator_tag, BedFeature>
{
    public:
        BigBedIterator();
        virtual ~BigBedIterator();
        RPTreeLeafNodeItem* leafHitItem;


    protected:
    private:

    //specification of chromosome selection region
    RPChromosomeRegion* selectionRegion;  // selection region for iterator
    bool contained; // if true, features must be fully contained by extraction region
    RPChromosomeRegion* hitRegion;  // hit selection region for iterator

    // File access variables for reading Bed data block
    std::ifstream* fis;  // file input stream handle
    BPTree* chromIDTree;    // B+ chromosome index tree
    RPTree* chromDataTree;  // R+ chromosome data location tree

    // chromosome region extraction items
    std::vector<RPTreeLeafNodeItem*> leafHitList; // array of leaf hits for selection region items
    std::map<uint32_t, std::string>* chromosomeMap;  // map of chromosome ID's and corresponding names
    int32_t leafItemIndex;  // index of current leaf item being processed from leaf hit list
    // leaf item being processed by next

    // current data block processing members
    BigBedDataBlock* bedDataBlock; // Bed data block with Bed records decompressed
    bool dataBlockRead;  // flag indicates successful read of data block
    std::vector<BedFeature*> bedFeatureList; // array of selected  Bed features
    int32_t bedFeatureIndex;       // index of next Bed feature from the list

    bool empty;


};

#endif // BIGBEDITERATOR_H
