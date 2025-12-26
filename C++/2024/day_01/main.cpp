#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"
#include "math/custom_math.hpp"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cassert>

static int part_one(const std::string filename);
static int part_two(const std::string filename);

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "Error: Wrong number of arguments. Expected 3, got " << argc << "\n";
        std::cout << "How to use: ./main <path_to_input> <mode>\n";
        return 1;
    }

    std::string filename = argv[1];
    CMD mode = static_cast<CMD>(std::stoi(argv[2]));

    int part_one_solution = part_one(filename);
    int part_two_solution = part_two(filename);

    assert(part_one_solution == 1970720);
    assert(part_two_solution == 17191599);

    if (mode == RUN) {
        std::cout << "Part One solution is " << part_one_solution << "\n";
        std::cout << "Part Two solution is " << part_two_solution << "\n";
    } else if (mode == TEST) {
        std::cout << "Solutions for 2024 Day 01 are correct\n";
    } else {
        std::cout << "Error: Wrong mode selected " << mode << "\n";
        return 1;
    }

    return 0;
}

static int part_one(const std::string filename)
{
    // Read data from file
    std::vector<int> left_numbers;
    std::vector<int> right_numbers;

    read_file_with_2_columns(filename, "  ", left_numbers, right_numbers);

    // Sort both vectors
    std::sort(left_numbers.begin(), left_numbers.end());
    std::sort(right_numbers.begin(), right_numbers.end());

    // Calculate solution
    int result = 0;

    for (size_t i = 0; i < left_numbers.size(); ++i) {
        result += std::abs(left_numbers[i] - right_numbers[i]);
    }

    return result;
}

static int part_two(const std::string filename)
{
    // Read data from file
    std::vector<int> left_numbers;
    std::vector<int> right_numbers;

    read_file_with_2_columns(filename, "  ", left_numbers, right_numbers);

    // Calculate solution using hash map
    std::unordered_map<int, int> occurences;

    for (auto number : right_numbers) {
        ++occurences[number];
    }

    int result = 0;

    for (auto number : left_numbers) {
        result += number * occurences[number];
    }

    return result;
}
