#include "data_parsing/file_read.hpp"
#include "presentation/custom_print.hpp"
#include "math/custom_math.hpp"

#include <iostream>
#include <cassert>
#include <chrono>
#include <iomanip>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

static int part_one(const std::string file_name);
static int part_two(const std::string file_name);
static position get_guard_location(world_map &map);
static void patrol_map(world_map &map, position current_position); 
static position get_next_position(position old_position, char direction);
static bool creates_loop(world_map &map, position initial_position, position new_obstacle);
static bool move(world_map &map, position &old_position, char &direction);
static char rotate(char old_direction);

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

    assert(part_one_solution == 4883);
    assert(part_two_solution == 1655);

    std::cout << std::fixed << std::setprecision(6);

    if (mode == RUN) {
        std::cout << "[" << part_one_exec_time << " s] " 
                  << "Part One solution is " << part_one_solution << "\n";
        std::cout << "[" << part_two_exec_time << " s] "
                  << "Part Two solution is " << part_two_solution << "\n";
    } else if (mode == TEST) {
        std::cout << "Solutions for 2024 Day 06 are correct "
                  << "[P1 " << part_one_exec_time << " s | P2 " << part_two_exec_time << " s]\n";
    } else {
        std::cout << "Error: Wrong mode selected " << mode << "\n";
        return 1;
    }

    return 0;
}

static int part_one(const std::string file_name)
{
    // Read file
    world_map map;
    read_file_into_string_vector(file_name, map);
    
    // Locate guard
    position starting_position = get_guard_location(map);

    // Simulate guard's patrol
    patrol_map(map, starting_position);

    // Calculate solution
    int result = 0;

    for (std::string line : map) {
        for (char sign : line) {
            if (sign == 'X') {
                ++result;
            }
        }
    }

    return result;
}

static int part_two(const std::string file_name)
{
    // Read file
    world_map map;
    read_file_into_string_vector(file_name, map);
    
    // Locate guard
    position starting_position = get_guard_location(map);

    // Locate positions where placing obstacle makes sense
    patrol_map(map, starting_position);

    // Calculate solution
    int result = 0;

    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            position current = std::make_pair<int, int>(i, j);
            if (map[current.first][current.second] == 'X' &&
                current != starting_position &&
                creates_loop(map, starting_position, current)
            ) {
                ++result;
            }
        }
    }

    return result;
}

static position get_guard_location(world_map &map)
{
    position result = std::make_pair<int, int>(-1, -1);

    for (size_t i = 0; i < map.size(); ++i) {
        int j = map[i].find('^');
        if (j > -1) {
            result.first = i;
            result.second = j;
            return result;
        }
    }

    return result;
}

static void patrol_map(world_map &map, position current_position)
{
    char direction = '^';

    while (move(map, current_position, direction)) {
        map[current_position.first][current_position.second] = 'X';
    }
}

static bool creates_loop(world_map &map, position initial_position, position new_obstacle)
{
    char slow_direction = '^';
    char fast_direction = '^';

    position slow_guard = initial_position;
    position fast_guard = initial_position;

    map[new_obstacle.first][new_obstacle.second] = '#';

    do {
        move(map, slow_guard, slow_direction);

        for (int cnt = 0; cnt < 2; ++cnt) {
            if (!move(map, fast_guard, fast_direction)) {
                map[new_obstacle.first][new_obstacle.second] = '.';
                return false;
            }
        }
    } while (is_on_map(map, fast_guard) && (slow_guard != fast_guard || slow_direction != fast_direction));

    map[new_obstacle.first][new_obstacle.second] = '.';

    if (is_out_of_map(map, fast_guard)) {
        return false;
    }

    if (slow_guard == fast_guard && slow_direction == fast_direction) {
        return true;
    }

    // Should never reach here, I put return here to disable
    // „control reaches end of function” warnings
    return false;
}

static position get_next_position(position old_position, char direction)
{
    position offset = std::make_pair<int, int>(0, 0);

    switch (direction) {
        case '^':
            offset.first = -1;
            offset.second = 0;
            break;
        case '>':
            offset.first = 0;
            offset.second = 1;
            break;
        case 'v':
            offset.first = 1;
            offset.second = 0;
            break;
        case '<':
            offset.first = 0;
            offset.second = -1;
            break;
        default:
            std::cerr << "Wrong direction passed (" << direction << ")\n";
            return old_position;
    }

    return std::make_pair<int, int>(
        old_position.first + offset.first,
        old_position.second + offset.second
    );
}

static bool move(world_map &map, position &old_position, char &direction)
{
    position new_position = get_next_position(old_position, direction);

    if (is_out_of_map(map, new_position)) {
        return false;
    }

    if (map[new_position.first][new_position.second] == '#') {
        direction = rotate(direction);
    } else {
        old_position = new_position;
    }

    return true;
}

static char rotate(char old_direction)
{
    switch (old_direction) {
        case '^': return '>';
        case '>': return 'v';
        case 'v': return '<';
        case '<': return '^';
        default: 
            std::cerr << "Wrong direction passed (" << old_direction << ")\n";
            return old_direction;
    }
}
