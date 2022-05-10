//
//  genomic_file_reader.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-06.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <string>
#include "utils/genomic_file_reader.h"

GenomicFileReader::GenomicFileReader(const std::string& file_path,
                                     const ChromSize& chrom_size) {
  file_path_ = file_path;
  chrom_size_ = chrom_size;
}
