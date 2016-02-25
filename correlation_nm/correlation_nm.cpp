//
//  correlation.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-06.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

/* this executable is used to generate the data for an nxn correlation matrix

Params:
  input.hdf5: an hdf5 file containing all the zscores
  filenames.txt: input file which contains n uncorrelated filenames, one per row
  output.results: output file path
  bin_size: an int which represents the bin of the hdf5

Output:
  a file where every line is "name1vsname2 chrX,0.12313 chrY,0.12313"

note: "filename" is really just the name of the groups as written in the hdf5 file,
they are not nessessarily actual files
*/

#if defined(_OPENMP)
  #include <omp.h>
#endif
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include "utils/genomic_dataset.h"
#include "utils/genomic_file_reader_factory.h"
#include "utils/hdf5_dataset_factory.h"
#include "utils/hdf5_reader.h"
#include "utils/input_list.h"

void write_entry(std::ofstream& output_file,
                 std::string& name,
                 std::map<std::string, float>& result) {
  std::string output_line = name;
  for (const auto& chrom : result) {
    output_line += "\t" + chrom.first + "," +  std::to_string(chrom.second);
  }
  #pragma omp critical (output) 
  {
    output_file << output_line + "\n";
  }
}

int main(int argc, const char * argv[]) {
  std::string hdf5_path, hdf5_path2, chrom_path, output_path, list_path, list_path2;
  // TODO(jl): remove requirement for bin_size
  int bin;

  if (argc < 8) {
    printf("Usage: correlation {input_list1} "
                              "{input_list2} "
                              "{chrom_sizes} "
                              "{input1.hdf5} "
                              "{input2.hdf5}"
                              "{output.results} "
                              "{bin_size}\n");
    return 1;
  }

  list_path = argv[1];
  list_path2 = argv[2];
  chrom_path = argv[3];
  hdf5_path = argv[4];
  hdf5_path2 = argv[5];
  output_path = argv[6];
  bin = std::stoi(argv[7], NULL, 10);

  Hdf5Reader hdf5_reader(hdf5_path);
  Hdf5Reader hdf5_reader2(hdf5_path2);
  InputList input_list(list_path);
  InputList input_list2(list_path2);
  ChromSize chrom_size = ChromSize(chrom_path);

  Hdf5Dataset* hdf5_dataset;

  std::vector<std::string> chroms = chrom_size.get_chrom_list();

  // read hdf5
  std::map<std::string, GenomicDataset> data;
  for (uint64_t i = 0; i < input_list.size(); ++i) {
    data.emplace(input_list[i].second, GenomicDataset(input_list[i].second));
    for (const std::string& chrom : chroms) {
      std::string name = input_list[i].second + "/" + chrom;
      if (hdf5_reader.IsValid(name)) {
        hdf5_dataset = hdf5_reader.GetDataset(name, bin);
        data[input_list[i].second].add_chromosome(chrom, *hdf5_dataset);
      }
    }
  }

  // read hdf5 2
  for (uint64_t i = 0; i < input_list2.size(); ++i) {
    data.emplace(input_list2[i].second, GenomicDataset(input_list2[i].second));
    for (const std::string& chrom : chroms) {
      std::string name = input_list2[i].second + "/" + chrom;
      if (hdf5_reader2.IsValid(name)) {
        hdf5_dataset = hdf5_reader2.GetDataset(name, bin);
        data[input_list2[i].second].add_chromosome(chrom, *hdf5_dataset);
      }
    }
  }

  // generate all file pairs to correlate
  std::vector<std::pair<std::string, std::string>> pairs;
  // nxn
  for (uint64_t i = 0; i < input_list.size(); ++i) {
    for (uint64_t j = 0; j <= i; ++j) {
      pairs.push_back(std::make_pair(input_list[i].second,
                                     input_list[j].second));
    }
  }
  // nxm
  for (uint64_t i = 0; i < input_list.size(); ++i) {
    for (uint64_t j = 0; j < input_list2.size(); ++j) {
      pairs.push_back(std::make_pair(input_list[i].second,
                                     input_list2[j].second));
    }
  }

  // compute correlation for every pair
  std::ofstream output_file;
  output_file.open(output_path);

  std::string first, second;
  std::map<std::string, float> result;

  #pragma omp parallel for private(first, second, result)
  for (uint64_t i = 0; i < pairs.size(); ++i) {
    first = pairs[i].first;
    second = pairs[i].second;
    result = data[first].Correlate(data[second],
                                                                  chroms);
    std::string name = first + ":" + second;
    write_entry(output_file, name, result);
  }

  output_file.close();

  return 0;
}
