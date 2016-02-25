
// ***************************************************************************
//   BidBedDataBlock.cpp (c) 2014
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


#include "BigBedDataBlock.h"
#include "decompress_util.h"
#include <vector>
#include <string>
BigBedDataBlock::BigBedDataBlock()
{
    //ctor
}

BigBedDataBlock::~BigBedDataBlock()
{
    //dtor
}


 /*
    *   Constructor for Bed data block reader.
    *
    *   Parameters:
    *       fis - file input stream handle
    *       leafItem - R+ tree leaf item containing chromosome region and file data location
    *       chromIDTree - B+ chromosome index tree returns chromosome ID's for names
    *       isLowToHigh - char order is low to high if true; else high to low
    *       uncompressBufSize - char size for decompression buffer; else 0 for uncompressed
    * */
     BigBedDataBlock::BigBedDataBlock(std::ifstream* fis, RPTreeLeafNodeItem* leafHitItem,
            std::map<int32_t, std::string> chromosomeMap, int32_t uncompressBufSize){
        this->fis_ = fis;
        this->leafHitItem_ = leafHitItem;
        this->chromosomeMap_ = chromosomeMap;

        dataBlockSize_ = this->leafHitItem_->getDataSize();
        bedBuffer_ = new char[(int32_t) dataBlockSize_];

        fileOffset_ = this->leafHitItem_->getDataOffset();




        // read Bed data block int32_to a buffer
        try {
            fis_->clear();
            fis_->seekg(fileOffset_);

            // decompress if necessary - the buffer size is 0 for uncompressed data
            // Note:  BBFile Table C specifies a decompression buffer size
            if(uncompressBufSize > 0)
                read_compressed(*fis,bedBuffer_,uncompressBufSize);
            else
                fis->read(bedBuffer_,uncompressBufSize);


       }catch(...) {
            throw new std::runtime_error("Error reading Bed data for leaf item %d \n" );
       }

        // initialize unread data size
        remDataSize_ = uncompressBufSize;

        // use methods getBedData or getNextFeature to extract block data
    }

    /*
    *   Method returns all Bed features within the decompressed block buffer
    *
    *   Parameters:
    *       selectionRegion - chromosome region for selecting Bed features
    *       contained - indicates selected data must be contained in selection region
    *           if true, else may int32_tersect selection region
    *
    *   Returns:
    *      Bed feature items in the data block
    *
    *   Note: Remaining chars to data block are used to determine end of reading
    *   since a zoom record count for the data block is not known.
    * */
    std::vector<BedFeature*> BigBedDataBlock::getBedData(RPChromosomeRegion* selectionRegion,
                                                bool contained) {
        int32_t itemNumber = 0;
        int32_t chromID, chromStart, chromEnd;
        std::string restOfFields;
        int32_t itemHitValue;

        // chromID + chromStart + chromEnd + rest 0 char
        // 0 char for "restOfFields" is always present for bed data
        int32_t minItemSize = 3 * 4 + 1;

        // check if all leaf items are selection hits
        RPChromosomeRegion* itemRegion = new RPChromosomeRegion( leafHitItem_->getChromosomeBounds());
        int32_t leafHitValue = itemRegion->compareRegions(selectionRegion);

        //TODO complete BigBedDataBlock
/*
        try {
            for(int32_t index = 0; remDataSize > 0; ++index) {
                itemNumber = index + 1;

                // read in BigBed item fields - BBFile Table I
                if(isLowToHigh){
                    chromID = lbdis.readInt();
                    chromStart= lbdis.readInt();
                    chromEnd = lbdis.readInt();
                    restOfFields = lbdis.readstd::string();
                }
                else{
                    chromID = dis.readInt();
                    chromStart= dis.readInt();
                    chromEnd = dis.readInt();
                    restOfFields = dis.readUTF();
                }

                if(leafHitValue == 0) {     // contained leaf region items always added
                    std::string chromosome = chromosomeMap.get(chromID);
                    BedFeature bbItem = new BedFeature(itemNumber, chromosome,
                         chromStart, chromEnd, restOfFields);
                    bedFeatureList.add(bbItem);
                }
                else {                      // test for hit
                    itemRegion = new RPChromosomeRegion(chromID, chromStart, chromID, chromEnd);
                    itemHitValue = itemRegion.compareRegions(selectionRegion);

                    // abs(itemHitValue) == 1 for int32_tersection; itemHitValue == 0 for contained
                    if(!contained && Math.abs(itemHitValue) < 2 ||
                            itemHitValue == 0) {
                        // add bed feature to item selection list
                        std::string chromosome = chromosomeMap.get(chromID);
                        BedFeature bbItem = new BedFeature(itemNumber, chromosome,
                             chromStart, chromEnd, restOfFields);
                        bedFeatureList.add(bbItem);
                    }
                }

                // compute data block remainder from size of item read
                // todo: check that restOfFields.length() does not also include 0 char terminator
                remDataSize -= minItemSize + restOfFields.length();
            }
        }catch(...) {
            // accept this as an end of block condition unless no items were read
            if(itemNumber == 1)
                throw new std::runtime_error("Read error for Bed data item ");
        }
*/
        return bedFeatureList_;
    }
