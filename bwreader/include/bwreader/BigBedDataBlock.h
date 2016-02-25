#ifndef BIGBEDDATABLOCK_H
#define BIGBEDDATABLOCK_H

// ***************************************************************************
//   BigBedDataBlock.h (c) 2014
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


#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "BedFeature.h"
#include "RPTreeLeafNodeItem.h"

class BigBedDataBlock
{
    public:
        BigBedDataBlock();
        BigBedDataBlock(std::ifstream* fis, RPTreeLeafNodeItem* leafHitItem,std::map<int32_t, std::string> chromosomeMap, int32_t uncompressBufSize);

        virtual ~BigBedDataBlock();



         std::vector<BedFeature*> getBedData(RPChromosomeRegion* selectionRegion, bool contained);

    protected:
    private:


             // Bed data block access variables   - for reading in bed records from a file
    std::ifstream* fis_;  // file input stream handle
    int64_t fileOffset_;       // Bed data block file offset
    int64_t dataBlockSize_;     // byte size for data block specified in the R+ leaf
    bool isLowToHigh_;   // if true, data is low to high byte order; else high to low

    // defines the bigBed/bigWig source chromosomes
    std::map<int32_t, std::string> chromosomeMap_;  // map of chromosome ID's and corresponding names
    RPTreeLeafNodeItem* leafHitItem_;   // R+ tree leaf item containing data block location

    // Provides uncompressed byte stream data reader
    char* bedBuffer_;  // buffer containing leaf block data uncompressed
    int remDataSize_;   // number of unread data bytes
    int64_t dataSizeRead_;     // number of bytes read from the decompressed mWigBuffer


    // Bed data extraction members
    std::vector<BedFeature*> bedFeatureList_; // array of BigBed data
    int nItemsSelected_;    // number of Bed features selected from this section
};

#endif // BIGBEDDATABLOCK_H
