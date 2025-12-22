#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"

#include <iostream>
#include <cassert>

static int part_one(const std::string filename);
static int part_two(const std::string filename);
static bool is_safe(std::vector<int> &data);

int main(int argc, char **argv)
{
    std::string filename = "input.txt";

    int part_one_solution = part_one(filename);
    int part_two_solution = part_two(filename);

    std::cout << "Part One solution is " << part_one_solution << "\n";
    std::cout << "Part Two solution is " << part_two_solution << "\n";

    assert(part_one_solution == 246);
    assert(part_two_solution == 318);

    std::cout << "Solutions are correct\n";

    return 0;
}

static int part_one(const std::string filename)
{
    std::vector<std::vector<int>> data;

    read_file_with_n_numbers_per_line(filename, " ", data);

    int result = 0;

    for (std::vector<int> &line : data) {
        if (is_safe(line)) {
            ++result;
        }
    }

    return result;
}

static int part_two(const std::string filename)
{
    std::vector<std::vector<int>> data;

    read_file_with_n_numbers_per_line(filename, " ", data);

    int result = 0;

    for (std::vector<int> &line : data) {
        for (size_t i = 0; i < line.size(); ++i) {
            std::vector<int> copy = std::vector<int>(line.begin(), line.begin() + i);
            copy.insert(copy.end(), line.begin() + i + 1, line.end());

            if (is_safe(copy)) {
                ++result;
                break;
            }
        }
    }

    return result;
}

static bool is_safe(std::vector<int> &data)
{
    if (data.size() <= 1) {
        return true;
    }

    bool increasing = data[1] > data[0];

    for (size_t i = 0; i < data.size() - 1; ++i) {
        
        if (increasing) {
            if (data[i + 1] <= data[i]) {
                return false;
            }
        } else {
            if (data[i + 1] >= data[i]) {
                return false;
            }
        }

        int difference = abs(data[i + 1] - data[i]); 
        if (difference < 1 || difference > 3) {
            return false;
        }
    }

    return true;
}
