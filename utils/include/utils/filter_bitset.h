//
//  filter_bitset.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_FILTER_BITSET_H_
#define UTILS_INCLUDE_UTILS_FILTER_BITSET_H_

#include <math.h>

class FilterBitset {
 public:
    FilterBitset(ChromSize& chrom_size, int bin, GenomicFileReader& genomic_file_reader) {
        std::vector<std::string> chrom_list = chrom_size.getChromList();

        for (std::string& chrom : chrom_list) {
            int size = ceil(chrom_size[chrom] / bin);
            vector<bool> filter(size);

            GenomicDataLine token;
            genomic_file_reader->SeekChr(chrom);
            while (!genomic_file_reader->NextToken(token)) {
              feed_data_line(filter, token);
            }

            content_.emplace(chrom, filter);
        }
    };
    ~FilterBitset() {};
    vector<bool>& operator[](const std::string& chrom){
      return content_[chrom];
    }
 private:
    std::map<std::string, vector<bool>> content_;
};

void feed_data_line(vector<bool>& filter, const GenomicDataLine& token, int bin) {
  int start_bin, end_bin;
  start_bin = token.start_position() / bin_;
  end_bin = token.end_position() / bin_;
  for (int i = start_bin; i <= end_bin; ++i) {
    content_[i] = 1;
  }
}

#endif  // UTILS_INCLUDE_UTILS_FILTER_BITSET_H_
