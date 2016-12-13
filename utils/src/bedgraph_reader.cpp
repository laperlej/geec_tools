//
//  bedgraph_reader.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <iostream>
#include <string>
#include "utils/bedgraph_reader.h"

BedGraphReader::BedGraphReader(const std::string& file_path,
                               const ChromSize& chrom_size):
                               GenomicFileReader(file_path, chrom_size) {
    OpenStream();
};

void BedGraphReader::NextChr() {
  GenomicDataLine token;
  while (!genomic_file_reader->NextToken(token)) {}
  if (!genomic_file_stream_.fail()) {
    chr_ = token.chromosome();
    chrom_pos_.emplace(chr_, cursor_);
  }
}

void BedGraphReader::SeekChr(const std::string& chromosome) {
  if (cursor > last_pos_) {
    last_pos_ == cursor_;
  }
  if (chrom_pos_.find(chromosome) == chrom_pos_.end()) {
    genomic_file_stream_.seekg(last_pos_);
    while (chr_ != chromosome && !genomic_file_stream_.fail()) {
      NextChr();
    }
  } else {
    cursor_ = chrom_pos_.find(chromosome)->second;
    genomic_file_stream_.seekg(cursor_);
  }
}

bool BedGraphReader::NextToken(GenomicDataLine& genomic_data_line) {
  std::string chr;
  int start;
  int end;
  float score;
  cursor_ = genomic_file_stream_.tellg();
  genomic_file_stream_>> chr>> start>> end>> score;
  genomic_data_line = GenomicDataLine(chr, start, end, score);
  //std::cout<< genomic_data_line.display()<< std::endl;
  return genomic_file_stream_.fail() || chr != chr_;
}

void BedGraphReader::OpenStream() {
  genomic_file_stream_.open(file_path_.c_str(), std::ios::in);
  cursor_ = genomic_file_stream_.tellg();
  last_pos_ = cursor_;
}
