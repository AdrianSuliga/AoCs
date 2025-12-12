#pragma once

#include <string>
#include <vector>
#include <regex>

// Return entire content from file as string
std::string read_file(std::string file_name);

// Read numbers from file containing two columns of 
// integers separated by separator string
void read_file_with_2_columns(const std::string file_name, 
                              const std::string separator, 
                              std::vector<int> &left_vector,
                              std::vector<int> &right_vector);

// Read numbers from file where each line has unknown number of
// integers separated by separator string. Output is vector
// of vectors of integers
void read_file_with_n_numbers_per_line(const std::string file_name,
                                       const std::string separator,
                                       std::vector<std::vector<int>> &output);

// Scan file for given regex, save found regexes to output
void scan_file_for_regex(const std::string file_name,
                         const std::regex &regex,
                         std::vector<std::string> &output);
