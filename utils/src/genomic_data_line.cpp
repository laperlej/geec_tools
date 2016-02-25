//
//  genomic_data_line.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <sstream>
#include <string>
#include "utils/genomic_data_line.h"

std::string GenomicDataLine::display() {
    std::stringstream display_stream;
    display_stream<< chromosome_
                  << "\t"
                  << start_position_
                  << "\t"
                  << end_position_
                  << "\t"
                  << score_;
    return display_stream.str();
}
