#pragma once

#include <string>
#include <vector>

// print vector of ints ending each character with end string
void print_int_vector(const std::vector<int> &vector, const std::string end);

// print vector of longs ending each character with end string
void print_long_vector(const std::vector<long> &vector, const std::string end);

// print vector of strings ending each element with end string
void print_string_vector(const std::vector<std::string> &vector, 
                         const std::string end);

// print 2 vectors of ints ending each pair of characters with end string
void print_2_int_vectors(const std::vector<int> &left_vector, 
                         const std::vector<int> &right_vector, 
                         const std::string end);

// print vector of vectors of int ending each line with end string
void print_2d_vector(const std::vector<std::vector<int>> &data,
                     const std::string end);
