//
//  chrom_size.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <string>
#include <fstream>
#include <vector>
#include "utils/chrom_size.h"

ChromSize::ChromSize() {
  //hg19 is default
  chrom_sizes_ = {
    {"chr1",   249250621},
    {"chr2",   243199373},
    {"chr3",   198022430},
    {"chr4",   191154276},
    {"chr5",   180915260},
    {"chr6",   171115067},
    {"chr7",   159138663},
    {"chrX",   155270560},
    {"chr8",   146364022},
    {"chr9",   141213431},
    {"chr10",  135534747},
    {"chr11",  135006516},
    {"chr12",  133851895},
    {"chr13",  115169878},
    {"chr14",  107349540},
    {"chr15",  102531392},
    {"chr16",  90354753},
    {"chr17",  81195210},
    {"chr18",  78077248},
    {"chr20",  63025520},
    {"chrY",   59373566},
    {"chr19",  59128983},
    {"chr22",  51304566},
    {"chr21",  48129895},
  };

  chrom_list_= {
            "chr1", "chr2", "chr3", "chr4", "chr5",
            "chr6", "chr7", "chr8", "chr9", "chr10",
            "chr11", "chr12", "chr13", "chr14", "chr15",
            "chr16", "chr17", "chr18", "chr19", "chr20",
            "chr21", "chr22", "chrX"
  };
}

ChromSize::ChromSize(const std::string& file_name) {
  std::ifstream flot(file_name);
  std::string chromosome;
  int size;
  while (flot>> chromosome>> size) {
    chrom_sizes_.emplace(chromosome, size);
    chrom_list_.push_back(chromosome);
  }
}

int ChromSize::operator[](const std::string& chromosome) {
  return chrom_sizes_[chromosome];
}

size_t ChromSize::count(const std::string& k) const {
  return chrom_sizes_.count(k);
}

std::vector<std::string> ChromSize::get_chrom_list() const {
  return chrom_list_;
}
