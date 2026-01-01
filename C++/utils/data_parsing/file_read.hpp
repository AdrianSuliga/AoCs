#pragma once

#include <string>
#include <vector>
#include <regex>

// Return entire content from file as string
std::string read_file(const std::string file_name);

// Read numbers from file containing two columns of 
// integers separated by separator string
void read_file_with_2_columns(const std::string file_name, 
                              const std::string separator, 
                              std::vector<int> &left_vector,
                              std::vector<int> &right_vector);

// Read numbers from file where each line has unknown number of
// integers separated by separator char. Ignore given indexes.
// Output is vector of vectors of integers
void read_file_with_n_numbers_per_line(const std::string file_name,
                                       const char separator,
                                       std::vector<std::vector<int>> &output);
                                       
void read_file_with_n_numbers_per_line(const std::string file_name,
                                       const char separator,
                                       std::vector<std::vector<int>> &output,
                                       std::vector<size_t> &to_ignore);

// Read file that starts with two columns of integers seperated by column_separator
// string and ends with lines of integers separated by line_separator string, 
void read_file_with_2_columns_n_numbers_per_line(const std::string file_name,
                                                 std::vector<int> &left_column,
                                                 std::vector<int> &right_column,
                                                 const std::string column_separator,
                                                 std::vector<std::vector<int>> &readings,
                                                 const char lines_separator);

// Read file that starts with column of longs, column end with separator string
void read_file_with_column_of_longs(const std::string file_name,
                                    std::vector<long> &output,
                                    const std::string separator);

// Save each line of file's content as separate string in vector
void read_file_into_string_vector(const std::string file_name,
                                  std::vector<std::string> &output);

// Scan file for given regex, save found regexes to output
void scan_file_for_regex(const std::string file_name,
                         const std::regex &regex,
                         std::vector<std::string> &output);
