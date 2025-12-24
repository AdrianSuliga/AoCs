#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

static int part_one(std::string file_name);
static int part_two(std::string file_name);
static bool is_correctly_ordered(std::vector<int> &reading, 
                                 std::vector<int> &left_column,
                                 std::vector<int> &right_column);
static void order_correctly(std::vector<int> &reading,
                            std::vector<int> &left_column,
                            std::vector<int> &right_column);
static void swap(std::vector<int> &vec, int i, int j);

int main()
{
    std::string filename = "input.txt";

    int part_one_solution = part_one(filename);
    int part_two_solution = part_two(filename);

    std::cout << "Part One solution is " << part_one_solution << "\n";
    std::cout << "Part Two solution is " << part_two_solution << "\n";

    assert(part_one_solution == 4959);
    assert(part_two_solution == 4655);

    std::cout << "Solutions are correct\n";

    return 0;
}

static int part_one(std::string file_name)
{
    // Read data from file
    std::vector<int> left_column;
    std::vector<int> right_column;
    std::vector<std::vector<int>> readings;

    read_file_with_2_columns_n_numbers_per_line(file_name, left_column, right_column,
                                                "|", readings, ',');

    // Calculate solution
    int result = 0;

    for (std::vector<int> &reading : readings) {
        if (is_correctly_ordered(reading, left_column, right_column)) {
            result += reading[reading.size() / 2];
        }
    }

    return result;
}

static int part_two(std::string file_name)
{
    // Read data from file
    std::vector<int> left_column;
    std::vector<int> right_column;
    std::vector<std::vector<int>> readings;

    read_file_with_2_columns_n_numbers_per_line(file_name, left_column, right_column,
                                                "|", readings, ',');

    // Calculate solution
    int result = 0;

    for (std::vector<int> &reading : readings) {
        if (!is_correctly_ordered(reading, left_column, right_column)) {
            order_correctly(reading, left_column, right_column);
            result += reading[reading.size() / 2];
        }
    }

    return result;
}

static bool is_correctly_ordered(std::vector<int> &reading, 
                                 std::vector<int> &left_column,
                                 std::vector<int> &right_column)
{
    for (size_t i = 0; i < reading.size() - 1; ++i) {
        for (size_t j = i + 1; j < reading.size(); ++j) {
            for (size_t k = 0; k < left_column.size(); ++k) {
                if (reading[i] == right_column[k] && reading[j] == left_column[k]) {
                    return false;
                }
            }
        }
    }

    return true;
}

static void order_correctly(std::vector<int> &reading,
                            std::vector<int> &left_column,
                            std::vector<int> &right_column)
{
    for (size_t i = 0; i < reading.size() - 1; ++i) {
        for (size_t j = i + 1; j < reading.size(); ++j) {
            for (size_t k = 0; k < left_column.size(); ++k) {
                if (reading[i] == right_column[k] && reading[j] == left_column[k]) {
                    swap(reading, i, j);
                }
            }
        }
    }
}

static void swap(std::vector<int> &vec, int i, int j)
{
    int buffer = vec[i];
    vec[i] = vec[j];
    vec[j] = buffer;
}
