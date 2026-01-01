#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"
#include "math/custom_math.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <chrono>
#include <iomanip>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

static int part_one(const std::string file_name);
static int part_two(const std::string file_name);
static int xmas_count(std::vector<std::string> &data, int i, int j);
static bool x_mas_present(std::vector<std::string> &data, int i, int j);

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

    assert(part_one_solution == 2434);
    assert(part_two_solution == 1835);

    std::cout << std::fixed << std::setprecision(6);

    if (mode == RUN) {
        std::cout << "[" << part_one_exec_time << " s] " 
                  << "Part One solution is " << part_one_solution << "\n";
        std::cout << "[" << part_two_exec_time << " s] "
                  << "Part Two solution is " << part_two_solution << "\n";
    } else if (mode == TEST) {
        std::cout << "Solutions for 2024 Day 04 are correct "
                  << "[P1 " << part_one_exec_time << " s | P2 " << part_two_exec_time << " s]\n";
    } else {
        std::cout << "Error: Wrong mode selected " << mode << "\n";
        return 1;
    }

    return 0;
}

static int part_one(const std::string file_name)
{
    // Read file content
    std::vector<std::string> data;
    read_file_into_string_vector(file_name, data);

    // Count XMAS
    int result = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            if (data[i][j] == 'X') {
                result += xmas_count(data, i, j);
            }
        }
    }

    return result;
}

static int part_two(const std::string file_name)
{
    // Read file content
    std::vector<std::string> data;
    read_file_into_string_vector(file_name, data);

    // Count XMAS
    int result = 0;

    for (size_t i = 1; i < data.size() - 1; ++i) {
        for (size_t j = 1; j < data[i].size() - 1; ++j) {
            if (data[i][j] == 'A' && x_mas_present(data, i, j)) {
                ++result;
            }
        }
    }

    return result;
}

static int xmas_count(std::vector<std::string> &data, int i, int j)
{
    std::string mas = "MAS";
    std::vector<std::pair<int, int>> moves = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
        {1, 1}, {1, 0}, {1, -1}, {0, -1}
    };
    int result = 0;

    for (auto &move : moves) {
        int i_offset = i + move.first;
        int j_offset = j + move.second;

        int lines = data.size();
        int columns = data[i].size();

        bool abort = false;

        for (char sign : mas) {
            if (!(-1 < i_offset && i_offset < lines &&
                -1 < j_offset && j_offset < columns &&
                data[i_offset][j_offset] == sign
            )) {
                abort = true;
                break;
            }

            i_offset += move.first;
            j_offset += move.second;
        }

        if (abort) {
            continue;
        }

        ++result;
    }

    return result;
}

static bool x_mas_present(std::vector<std::string> &data, int i, int j)
{
    std::string shape = "";
    shape += data[i - 1][j - 1];
    shape += data[i - 1][j + 1];
    shape += data[i + 1][j + 1];
    shape += data[i + 1][j - 1];

    return (
        shape == "MSSM" ||
        shape == "MMSS" ||
        shape == "SSMM" ||
        shape == "SMMS"
    );
}
