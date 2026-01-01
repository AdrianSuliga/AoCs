#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"
#include "math/custom_math.hpp"

#include <iostream>
#include <vector>
#include <regex>
#include <cassert>
#include <chrono>
#include <iomanip>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

static int part_one(const std::string file_name);
static int part_two(const std::string file_name);
static int extract_from_mul(std::string expression);

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

    assert(part_one_solution == 196826776);
    assert(part_two_solution == 106780429);

    std::cout << std::fixed << std::setprecision(6);

    if (mode == RUN) {
        std::cout << "[" << part_one_exec_time << " s] " 
                  << "Part One solution is " << part_one_solution << "\n";
        std::cout << "[" << part_two_exec_time << " s] "
                  << "Part Two solution is " << part_two_solution << "\n";
    } else if (mode == TEST) {
        std::cout << "Solutions for 2024 Day 03 are correct "
                  << "[P1 " << part_one_exec_time << " s | P2 " << part_two_exec_time << " s]\n";
    } else {
        std::cout << "Error: Wrong mode selected " << mode << "\n";
        return 1;
    }

    return 0;
}

static int part_one(const std::string file_name)
{
    // Prepare regex and output
    std::regex regex = std::regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
    std::vector<std::string> found_regexes;

    // Extract regexes from file
    scan_file_for_regex(file_name, regex, found_regexes);

    // Calculate result
    int result = 0;

    for (std::string found : found_regexes) {
        result += extract_from_mul(found);
    }

    return result;
}

static int part_two(const std::string file_name)
{
    // Prepare regex and output
    std::regex regex = std::regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\)");
    std::vector<std::string> found_regexes;

    // Extract regexes from file
    scan_file_for_regex(file_name, regex, found_regexes);

    // Calculate result
    bool extract = true;
    int result = 0;

    for (std::string found : found_regexes) {
        if (found.substr(0, 3) == "mul") {
            if (extract) {
                result += extract_from_mul(found);
            }
        } else if (found.substr(0, 5) == "do()") {
            extract = true;
        } else if (found.substr(0, 7) == "don't()") {
            extract = false;
        }
    }

    return result;
}

static int extract_from_mul(std::string expression)
{
    size_t fst_idx = expression.find('(');
    size_t mid_idx = expression.find(',');
    size_t lst_idx = expression.find(')');

    std::string first_num = expression.substr(fst_idx + 1, mid_idx - fst_idx - 1);
    std::string second_num = expression.substr(mid_idx + 1, lst_idx - mid_idx - 1);

    return std::stoi(first_num) * std::stoi(second_num); 
}
