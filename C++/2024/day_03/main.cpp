#include <data_parsing/file_read.hpp>
#include <presentation/custom_print.hpp>

#include <iostream>
#include <vector>
#include <regex>
#include <cassert>

static int part_one(std::string file_name);
static int part_two(std::string file_name);
static int extract_from_mul(std::string expression);

int main()
{
    std::string filename = "input.txt";

    int part_one_solution = part_one(filename);
    int part_two_solution = part_two(filename);

    std::cout << "Part One solution is " << part_one_solution << "\n";
    std::cout << "Part Two solution is " << part_two_solution << "\n";

    assert(part_one_solution == 196826776);
    assert(part_two_solution == 106780429);

    std::cout << "Solutions are correct\n";

    return 0;
}

static int part_one(std::string file_name)
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

static int part_two(std::string file_name)
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
