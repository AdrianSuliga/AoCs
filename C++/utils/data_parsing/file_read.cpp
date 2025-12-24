#include "file_read.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

static void __scan_file_with_2_columns(std::ifstream &file, 
                                       const std::string separator, 
                                       std::vector<int> &left_vector, 
                                       std::vector<int> &right_vector);

static void __scan_file_with_n_numbers_per_line(std::ifstream &file,
                                                const char separator,
                                                std::vector<std::vector<int>> &output);

std::string read_file(const std::string file_name)
{
    std::ifstream file(file_name);
    std::string result = (std::stringstream() << file.rdbuf()).str();
    file.close();
    return result;
}

void read_file_with_2_columns(const std::string file_name, 
                              const std::string separator, 
                              std::vector<int> &left_vector, 
                              std::vector<int> &right_vector)
{
    std::ifstream file(file_name);
    
    __scan_file_with_2_columns(file, separator, left_vector, right_vector);

    file.close();
}

void read_file_with_n_numbers_per_line(const std::string file_name,
                                       const char separator,
                                       std::vector<std::vector<int>> &output)
{
    std::ifstream file(file_name);
    
    __scan_file_with_n_numbers_per_line(file, separator, output);

    file.close();
}

void read_file_with_2_columns_n_numbers_per_line(const std::string file_name,
                                                 std::vector<int> &left_column,
                                                 std::vector<int> &right_column,
                                                 const std::string column_separator,
                                                 std::vector<std::vector<int>> &readings,
                                                 const char lines_separator)
{
    std::ifstream file(file_name);

    __scan_file_with_2_columns(file, column_separator, left_column, right_column);

    __scan_file_with_n_numbers_per_line(file, lines_separator, readings);

    file.close();
}

void read_file_into_string_vector(const std::string file_name,
                                  std::vector<std::string> &output)
{
    std::ifstream file(file_name);
    std::string buffer;

    while (getline(file, buffer)) {
        output.push_back(buffer);
    }

    file.close();
}

void scan_file_for_regex(const std::string file_name,
                         const std::regex &regex,
                         std::vector<std::string> &output)
{
    std::string file_content = read_file(file_name);
    std::smatch found;
    
    while (std::regex_search(file_content, found, regex)) {
        output.push_back(found[0]);
        file_content = found.suffix();
    }
}

static void __scan_file_with_2_columns(std::ifstream &file, 
                                       const std::string separator, 
                                       std::vector<int> &left_vector, 
                                       std::vector<int> &right_vector)
{
    std::string buffer;

    while (getline(file, buffer) && buffer != "") {
        int idx = buffer.find(separator);

        std::string left_num_str = buffer.substr(0, idx);
        std::string right_num_str = buffer.substr(idx + separator.size());

        left_vector.push_back(std::stoi(left_num_str));
        right_vector.push_back(std::stoi(right_num_str));
    }
}

static void __scan_file_with_n_numbers_per_line(std::ifstream &file,
                                                const char separator,
                                                std::vector<std::vector<int>> &output)
{
    std::string buffer;

    while (getline(file, buffer)) {
        std::vector<int> nums_in_line;
        std::string number_str = "";

        for (char sign : buffer) {
            if (sign == separator) {
                nums_in_line.push_back(std::stoi(number_str));
                number_str = "";
                continue;
            }

            number_str += sign;
        }

        nums_in_line.push_back(std::stoi(number_str));

        output.push_back(nums_in_line);
    }
}
