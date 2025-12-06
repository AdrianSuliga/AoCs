#pragma once

#include <string>
#include <vector>

// Read numbers from file containing two columns of 
// integers separated by separator string
void read_file_with_2_columns(const std::string file_name, 
                              const std::string separator, 
                              std::vector<int> &left_vector,
                              std::vector<int> &right_vector);
