#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"
#include "math/custom_math.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <chrono>
#include <iomanip>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

static int part_one(const std::string file_name);
static int part_two(const std::string file_name);
static bool is_correctly_ordered(std::vector<int> &reading, 
                                 std::vector<int> &left_column,
                                 std::vector<int> &right_column);
static void order_correctly(std::vector<int> &reading,
                            std::vector<int> &left_column,
                            std::vector<int> &right_column);
static void swap(std::vector<int> &vec, int i, int j);

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "Error: Wrong number of arguments. Expected 3, got " << argc << "\n";
        std::cout << "How to use: ./main <path_to_input> <mode>\n";
        return 1;
    }

    std::string filename = argv[1];
    CMD mode = static_cast<CMD>(std::stoi(argv[2]));

    steady_clock::time_point part_one_begin = steady_clock::now();
    int part_one_solution = part_one(filename);
    steady_clock::time_point part_one_end = steady_clock::now();
    double part_one_exec_time = static_cast<double>(
                                    duration_cast<microseconds>(
                                        part_one_end - part_one_begin
                                    ).count()
                                ) / 1000000.0;

    steady_clock::time_point part_two_begin = steady_clock::now();
    int part_two_solution = part_two(filename);
    steady_clock::time_point part_two_end = steady_clock::now();
    double part_two_exec_time = static_cast<double>(
                                    duration_cast<microseconds>(
                                        part_two_end - part_two_begin
                                    ).count()
                                ) / 1000000.0;

    assert(part_one_solution == 4959);
    assert(part_two_solution == 4655);

    std::cout << std::fixed << std::setprecision(6);

    if (mode == RUN) {
        std::cout << "[" << part_one_exec_time << " s] " 
                  << "Part One solution is " << part_one_solution << "\n";
        std::cout << "[" << part_two_exec_time << " s] "
                  << "Part Two solution is " << part_two_solution << "\n";
    } else if (mode == TEST) {
        std::cout << "Solutions for 2024 Day 05 are correct "
                  << "[P1 " << part_one_exec_time << " s | P2 " << part_two_exec_time << " s]\n";
    } else {
        std::cout << "Error: Wrong mode selected " << mode << "\n";
        return 1;
    }

    return 0;
}

static int part_one(const std::string file_name)
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

static int part_two(const std::string file_name)
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
