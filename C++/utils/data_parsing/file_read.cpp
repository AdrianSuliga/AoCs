#include "file_read.hpp"

#include <iostream>
#include <fstream>
#include <string>

void read_file_with_2_columns(const std::string file_name, 
                              const std::string separator, 
                              std::vector<int> &left_vector, 
                              std::vector<int> &right_vector)
{
    std::ifstream file(file_name);
    std::string buffer;

    while (getline(file, buffer)) {
        int idx = buffer.find("  ");

        std::string left_num_str = buffer.substr(0, idx);
        std::string right_num_str = buffer.substr(idx + 2);

        left_vector.push_back(std::stoi(left_num_str));
        right_vector.push_back(std::stoi(right_num_str));
    }

    file.close();
}
