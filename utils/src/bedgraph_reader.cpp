//
//  bedgraph_reader.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <string>
#include "utils/bedgraph_reader.h"

BedGraphReader::BedGraphReader(const std::string& file_path,
                               const ChromSize& chrom_size):
                               GenomicFileReader(file_path, chrom_size) {
    OpenStream();
};

void BedGraphReader::SeekChr(const std::string& chromosome) {
  std::streampos cursor;
  chr_ = chromosome;
  GenomicDataLine genomic_data_line;
  do {
    cursor = genomic_file_stream_.tellg();
    NextToken(genomic_data_line);
  } while (genomic_data_line.chromosome() != chromosome);
  genomic_file_stream_.seekg(cursor);
}

bool BedGraphReader::NextToken(GenomicDataLine& genomic_data_line) {
  std::string chr;
  int start;
  int end;
  float score;
  genomic_file_stream_>> chr>> start>> end>> score;
  genomic_data_line = GenomicDataLine(chr, start, end, score);
  return genomic_file_stream_.fail() || chr != chr_;
}

void BedGraphReader::OpenStream() {
  genomic_file_stream_.open(file_path_.c_str(), std::ios::in);
}
