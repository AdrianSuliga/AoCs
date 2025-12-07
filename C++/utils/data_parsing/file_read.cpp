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

void read_file_with_n_numbers_per_line(const std::string file_name,
                                       const std::string separator,
                                       std::vector<std::vector<int>> &output)
{
    std::ifstream file(file_name);
    std::string buffer;

    while (getline(file, buffer)) {
        std::vector<int> nums_in_line;
        std::string number_str = "";

        for (char sign : buffer) {
            if (sign == ' ') {
                nums_in_line.push_back(std::stoi(number_str));
                number_str = "";
                continue;
            }

            number_str += sign;
        }

        nums_in_line.push_back(std::stoi(number_str));

        output.push_back(nums_in_line);
    }

    file.close();
}
