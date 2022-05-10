//
//  genomic_file_reader_factory.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <string>
#include "utils/genomic_file_reader_factory.h"
#include "utils/bedgraph_reader.h"
#include "utils/bigwig_reader.h"
#include "utils/bed_reader.h"

enum FileTypeId {
  bw,
  bg,
  bd,
  none
};

FileTypeId file_type_to_id(const std::string& file_type) {
    if (file_type == ".bw" || file_type == ".bigWig" || file_type == ".bigwig") return bw;
    if (file_type == ".bg" || file_type == ".bedGraph" || file_type == ".bedgraph") return bg;
    if (file_type == ".bd" || file_type == ".bed") return bd;
    return bw;
}

GenomicFileReader* GenomicFileReaderFactory::createGenomicFileReader(
    const std::string& file_path,
    const std::string& file_type,
    const ChromSize& chrom_size) {
  GenomicFileReader* file_reader = NULL;
  switch (file_type_to_id(file_type)) {
    case bg:
      file_reader = new BedGraphReader(file_path, chrom_size);
        break;
    case bw:
      file_reader = new BigWigReader(file_path, chrom_size);
        break;
    case bd:
      file_reader = new BedReader(file_path, chrom_size);
        break;
    default:
      std::cout<< "Unknown file type: "<< file_type<< std::endl;
  }
  return file_reader;
}
