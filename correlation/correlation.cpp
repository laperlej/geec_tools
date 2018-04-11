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
#include <string>
#include <map>
#include <vector>
#include <utility>
#include "utils/genomic_dataset.h"
#include "utils/genomic_file_reader_factory.h"
#include "utils/hdf5_dataset_factory.h"
#include "utils/hdf5_reader.h"
#include "utils/input_list.h"

void write_matrix(std::ofstream& output_file,
                 InputList& input_list,
                 std::vector<std::vector<float>>& matrix) {
  //write header
  std::string first_line = "";
  for (uint64_t i = 0; i < input_list.size(); ++i) {
    first_line += "\t" + input_list[i].second;
  }
  output_file << first_line + "\n";
  //write matrix
  for (uint64_t i = 0; i < input_list.size(); ++i) {
    std::string output_line = input_list[i].second;
    for (uint64_t j = 0; j < input_list.size(); ++j) {
      output_line += "\t" +  std::to_string(matrix[i][j]);
    }
    output_file << output_line + "\n";
  }
}

int main(int argc, const char * argv[]) {
  std::string chrom_path, output_path, list_path;
  // TODO(jl): remove requirement for bin_size
  int bin;

  if (argc < 5) {
    printf("Usage: correlation {input_list} "
                         "{chrom_sizes} "
                         "{output.results} "
                         "{bin_size}\n");
    return 1;
  }

  list_path = argv[1];
  chrom_path = argv[2];
  output_path = argv[3];
  bin = std::stoi(argv[4], NULL, 10);

  InputList input_list(list_path);
  ChromSize chrom_size = ChromSize(chrom_path);

  Hdf5Dataset* hdf5_dataset;

  std::vector<std::string> chroms = chrom_size.get_chrom_list();

  // read hdf5
  std::map<std::string, GenomicDataset> data;
  for (uint64_t i = 0; i < input_list.size(); ++i) {
    try {
      Hdf5Reader hdf5_reader = Hdf5Reader(input_list[i].first);
      data.emplace(input_list[i].second, GenomicDataset(input_list[i].second));
      for (const std::string& chrom : chroms) {
        std::string name = input_list[i].second + "/" + chrom;
        if (hdf5_reader.IsValid(name)) {
          hdf5_dataset = hdf5_reader.GetDataset(name, bin);
          data[input_list[i].second].add_chromosome(chrom, *hdf5_dataset);
        }
      }
    } catch (...) { std::cout<< "Could not open file: "<< input_list[i].first<< std::endl; }
  }

  // generate all file pairs to correlate
  std::vector<std::pair<std::string, std::string>> pairs;
  for (uint64_t i = 0; i < input_list.size(); ++i) {
    for (uint64_t j = 0; j <= i; ++j) {
      pairs.push_back(std::make_pair(input_list[i].second,
                                     input_list[j].second));
    }
  }
  
  // compute correlation for every pair
  std::string first, second;
  float result;
  std::vector<std::vector<float>> matrix;
  matrix.resize(input_list.size(), std::vector<float>(input_list.size()));

  #pragma omp parallel for private(first, second, result)
  for (uint64_t i = 0; i < pairs.size(); ++i) {
    first = pairs[i].first;
    second = pairs[i].second;
    result = data[first].CorrelateAll(data[second], chroms);
    matrix[input_list.get_index(first)][input_list.get_index(second)] = result;
    matrix[input_list.get_index(second)][input_list.get_index(first)] = result;
  }
  std::ofstream output_file;
  write_matrix(output_file, input_list, matrix);
  output_file.close();

  return 0;
}
