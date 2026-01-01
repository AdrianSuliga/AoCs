#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"
#include "math/custom_math.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cassert>

using state = std::pair<long, size_t>;
struct StateHash {
    std::size_t operator()(const state &p) const noexcept {
        size_t h1 = std::hash<long>{}(p.first);
        size_t h2 = std::hash<size_t>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

using dictionary = std::unordered_map<state, bool, StateHash>;

static long part_one(const std::string file_name);
static long part_two(const std::string file_name);
static bool is_possible(std::vector<int> &data, long target);
static bool is_possible_concat(std::vector<int> &data, long target);
static bool search_recursive(std::vector<int> &data, long target, long result, 
                             size_t idx, dictionary &memo);
static bool search_recursive_concat(std::vector<int> &data, long target, long result,
                                    size_t idx, dictionary &memo);

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "Error: Wrong number of arguments. Expected 3, got " << argc << "\n";
        std::cout << "How to use: ./main <path_to_input> <mode>\n";
        return 1;
    }

    std::string filename = argv[1];
    CMD mode = static_cast<CMD>(std::stoi(argv[2]));

    long part_one_solution = part_one(filename);
    long part_two_solution = part_two(filename);

    assert(part_one_solution == 2941973819040);
    assert(part_two_solution == 249943041417600);

    if (mode == RUN) {
        std::cout << "Part One solution is " << part_one_solution << "\n";
        std::cout << "Part Two solution is " << part_two_solution << "\n";
    } else if (mode == TEST) {
        std::cout << "Solutions for 2024 Day 07 are correct\n";
    } else {
        std::cout << "Error: Wrong mode selected " << mode << "\n";
        return 1;
    }

    return 0;
}

static long part_one(const std::string file_name)
{
    std::vector<std::vector<int>> data;
    std::vector<long> targets;
    // Do not try to read target as int
    std::vector<size_t> ignored_idxs = {0};

    read_file_with_n_numbers_per_line(file_name, ' ', data, ignored_idxs);
    read_file_with_column_of_longs(file_name, targets, ":");

    // Calculate result
    long result = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        if (is_possible(data[i], targets[i])) {
            result += targets[i];
        }
    }

    return result;
}

static long part_two(const std::string file_name)
{
    std::vector<std::vector<int>> data;
    std::vector<long> targets;
    // Do not try to read target as int
    std::vector<size_t> ignored_idxs = {0};

    read_file_with_n_numbers_per_line(file_name, ' ', data, ignored_idxs);
    read_file_with_column_of_longs(file_name, targets, ":");

    // Calculate result
    long result = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        if (is_possible_concat(data[i], targets[i])) {
            result += targets[i];
        }
    }

    return result;
}

static bool is_possible(std::vector<int> &data, long target)
{
    std::unordered_map<state, bool, StateHash> memo;
    return search_recursive(data, target, data[0], 1, memo);
}

static bool search_recursive(std::vector<int> &data, long target, long result,
                             size_t idx, dictionary &memo)
{
    state current_state = std::make_pair(result, idx);

    if (memo.count(current_state) > 0) {
        return memo[current_state];
    }

    if (idx == data.size()) {
        memo[current_state] = target == result;
        return target == result;
    }

    if (result > target) {
        memo[current_state] = false;
        return false;
    }

    memo[current_state] = search_recursive(data, target, result + data[idx], idx + 1, memo) ||
                          search_recursive(data, target, result * data[idx], idx + 1, memo);

    return memo[current_state];
}

static bool is_possible_concat(std::vector<int> &data, long target)
{
    std::unordered_map<state, bool, StateHash> memo;
    return search_recursive_concat(data, target, data[0], 1, memo);
}

static bool search_recursive_concat(std::vector<int> &data, long target, long result,
                                    size_t idx, dictionary &memo)
{
    state current_state = std::make_pair(result, idx);

    if (memo.count(current_state) > 0) {
        return memo.at(current_state);
    }

    if (idx == data.size()) {
        memo.insert({current_state, result == target});
        return result == target;
    }

    if (result > target) {
        memo.insert({current_state, false});
        return false;
    }

    long concat_result = result;
    int to_concat = data[idx];

    while (to_concat > 0) {
        concat_result *= 10;
        to_concat /= 10;
    }

    concat_result += data[idx];

    bool return_value = search_recursive_concat(data, target, result + data[idx], idx + 1, memo) ||
                        search_recursive_concat(data, target, result * data[idx], idx + 1, memo) ||
                        search_recursive_concat(data, target, concat_result, idx + 1, memo);

    memo.insert({current_state, return_value});
    return return_value;
}
