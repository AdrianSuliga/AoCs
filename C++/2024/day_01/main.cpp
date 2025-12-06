#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"

#include <iostream>
#include <algorithm>
#include <unordered_map>

static int part_one(const std::string filename);
static int part_two(const std::string filename);

int main(int argc, char **argv)
{
    std::string filename = "input.txt";

    std::cout << "Part One solution is " << part_one(filename) << "\n";
    std::cout << "Part Two solution is " << part_two(filename) << "\n";

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
