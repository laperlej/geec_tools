//
//  bigwig_reader.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <string>
#include "utils/bigwig_reader.h"

BigWigReader::BigWigReader(const std::string& file_path,
                           const ChromSize& chrom_size):
                           GenomicFileReader(file_path, chrom_size) {
    OpenStream();
    bigwig_ = new BBFileReader(file_path_, genomic_file_stream_);
};

void BigWigReader::SeekChr(const std::string& chromosome) {
  bigwig_it_ = bigwig_->getBigWigIterator(chromosome,
                                          0,
                                          chromosome,
                                          chrom_size_[chromosome],
                                          false);
}

bool BigWigReader::NextToken(GenomicDataLine& genomic_data_line) {
  if (bigwig_it_.isEnd()) {return true;}
  std::string chr;
  int start;
  int end;
  float score;
  chr = (*bigwig_it_).getChromosome().c_str();
  start = (*bigwig_it_).getStartBase();
  end = (*bigwig_it_).getEndBase();
  score = (*bigwig_it_).getWigValue();
  genomic_data_line = GenomicDataLine(chr, start, end, score);
  ++bigwig_it_;
  return false;
}

void BigWigReader::OpenStream() {
    genomic_file_stream_.open(file_path_.c_str(),
                              std::ios::in | std::ios::binary);
}
