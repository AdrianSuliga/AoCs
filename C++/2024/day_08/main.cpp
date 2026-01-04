#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"
#include "math/custom_math.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <set>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

using position = std::pair<int, int>;
using world_map = std::vector<std::string>;

static int part_one(const std::string file_name);
static int part_two(const std::string file_name);
static int find_antinodes(const std::string file_name, 
                          void (*mark_function)(world_map &map, position &p1, position &p2, std::set<position> &antinodes));
static void mark_antinodes(world_map &map, position &p1, position &p2, std::set<position> &antinodes);
static void mark_antinodes_resonant(world_map &map, position &p1, position &p2, std::set<position> &antinodes);
static bool is_on_map(world_map &map, position &pos);
static bool is_antenna(char sign);

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

    assert(part_one_solution == 376);
    assert(part_two_solution == 1352);

    std::cout << std::fixed << std::setprecision(6);

    if (mode == RUN) {
        std::cout << "[" << part_one_exec_time << " s] " 
                  << "Part One solution is " << part_one_solution << "\n";
        std::cout << "[" << part_two_exec_time << " s] "
                  << "Part Two solution is " << part_two_solution << "\n";
    } else if (mode == TEST) {
        std::cout << "Solutions for 2024 Day 08 are correct "
                  << "[P1 " << part_one_exec_time << " s | P2 " << part_two_exec_time << " s]\n";
    } else {
        std::cout << "Error: Wrong mode selected " << mode << "\n";
        return 1;
    }

    return 0;
}

static int part_one(const std::string file_name)
{
    return find_antinodes(file_name, &mark_antinodes);
}

static int part_two(const std::string file_name)
{
    return find_antinodes(file_name, &mark_antinodes_resonant);
}

static int find_antinodes(const std::string file_name, 
                          void (*mark_function)(world_map &map, position &p1, position &p2, std::set<position> &antinodes))
{
    std::set<position> antinodes;
    world_map map;

    read_file_into_string_vector(file_name, map);

    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            if (is_antenna(map[i][j])) {
                position antenna1 = std::make_pair<int, int>(i, j);

                for (size_t p = j + 1; p < map[i].size(); ++p) {
                    if (map[i][j] == map[i][p]) {
                        position antenna2 = std::make_pair<int, int>(i, p);
                        mark_function(map, antenna1, antenna2, antinodes);
                    }
                }

                for (size_t k = i + 1; k < map.size(); ++k) {
                    for (size_t l = 0; l < map[k].size(); ++l) {
                        if (map[i][j] == map[k][l]) {
                            position antenna2 = std::make_pair<int, int>(k, l);
                            mark_function(map, antenna1, antenna2, antinodes);
                        }
                    }
                }
            }
        }
    }

    return antinodes.size();
}

static void mark_antinodes(world_map &map, position &p1, position &p2, std::set<position> &antinodes)
{
    int x_distance = p2.first - p1.first;
    int y_distance = p2.second - p1.second;

    position antinode1 = std::make_pair(p2.first + x_distance, p2.second + y_distance);
    position antinode2 = std::make_pair(p1.first - x_distance, p1.second - y_distance);

    if (is_on_map(map, antinode1)) {
        antinodes.insert(antinode1);
    }

    if (is_on_map(map, antinode2)) {
        antinodes.insert(antinode2);
    }
}

static void mark_antinodes_resonant(world_map &map, position &p1, position &p2, std::set<position> &antinodes)
{
    int x_distance = p2.first - p1.first;
    int y_distance = p2.second - p1.second;

    position antinode1 = std::make_pair(p2.first, p2.second);

    while (is_on_map(map, antinode1)) {
        antinodes.insert(antinode1);

        antinode1 = std::make_pair(antinode1.first + x_distance, antinode1.second + y_distance);
    }

    position antinode2 = std::make_pair(p1.first, p1.second);

    while (is_on_map(map, antinode2)) {
        antinodes.insert(antinode2);

        antinode2 = std::make_pair(antinode2.first - x_distance, antinode2.second - y_distance);
    }
}

static bool is_on_map(world_map &map, position &pos)
{
    int height = map.size();
    int width = map[0].size();

    return (
        -1 < pos.first && pos.first < height &&
        -1 < pos.second && pos.second < width
    );
}

static bool is_antenna(char sign)
{
    return (
        ('0' <= sign && sign <= '9') ||
        ('a' <= sign && sign <= 'z') ||
        ('A' <= sign && sign <= 'Z')
    );
}
