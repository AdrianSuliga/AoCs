#include "data_parsing/file_read.h"
#include "memory/custom_allocation.h"
#include "presentation/custom_print.h"
#include "math/custom_math.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

static int part_one(char *input);
static int part_two(char *input);
static struct position_t locate_guard(char **map, int lines, int columns);
static void patrol_map(char **map, int lines, int columns, struct position_t position);
static char rotate(char old_direction);
static struct position_t get_next_position(struct position_t old_position, char direction);
static int creates_loop(char **map, int lines, int columns, struct position_t position, int x, int y);
static int position_eq(struct position_t first, struct position_t second, char first_direction, char second_direction);

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Error: Wrong number of arguments. Expected 3, got %d\n", argc);
        printf("How to use: ./main <path_to_input> <mode>\n");
        return 1;
    }

    char *input = argv[1];
    int mode = atoi(argv[2]);

    clock_t part_one_start = clock(); 
    int part_one_solution = part_one(input);
    clock_t part_one_end = clock();
    double part_one_exec_time = ((double)(part_one_end - part_one_start)) / CLOCKS_PER_SEC;

    clock_t part_two_start = clock();
    int part_two_solution = part_two(input);
    clock_t part_two_end = clock();
    double part_two_exec_time = ((double)(part_two_end - part_two_start)) / CLOCKS_PER_SEC;

    assert(part_one_solution == 4883);
    assert(part_two_solution == 1655);

    if (mode == RUN) {
        printf("[%.6f s] Part One solution is %d\n", part_one_exec_time, part_one_solution);
        printf("[%.6f s] Part Two solution is %d\n", part_two_exec_time, part_two_solution);
    } else if (mode == TEST) {
        printf("Solutions for 2024 Day 06 are correct [P1 %.6f s | P2 %.6f s]\n",
                part_one_exec_time,
                part_two_exec_time);
    } else {
        printf("Error: Wrong mode selected %d\n", mode);
        return -1;
    }

    return 0;
}

static int part_one(char *input)
{
    // Read data from file into memory
    int lines = get_file_line_count(input);
    int columns = get_file_first_line_width(input) + 2; // Account for \0 and \n

    char **map = malloc_2d_char_array(lines, columns);
    if (map == NULL) {
        printf("Failed to allocate enough memory\n");
        return -1;
    }

    read_2d_char_array(input, map, lines, columns);

    // Locate guard's initial position
    struct position_t guard_position = locate_guard(map, lines, columns);

    patrol_map(map, lines, columns, guard_position);

    // Calculate result
    int result = 0;

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (map[i][j] == 'X') {
                ++result;
            }
        }
    }

    // Free allocated memory
    free_2d_char_array(map, lines);

    return result;
}

static int part_two(char *input)
{
    // Read data from file into memory
    int lines = get_file_line_count(input);
    int columns = get_file_first_line_width(input) + 2; // Account for \0 and \n

    char **map = malloc_2d_char_array(lines, columns);
    if (map == NULL) {
        printf("Failed to allocate enough memory\n");
        return -1;
    }

    read_2d_char_array(input, map, lines, columns);

    // Locate guard's initial position
    struct position_t guard_position = locate_guard(map, lines, columns);

    // Locate positions where placing obstacle makes sense
    patrol_map(map, lines, columns, guard_position);

    // Calculate result
    int result = 0;

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (map[i][j] == 'X' && // guard visits this position
                (i != guard_position.i || j != guard_position.j) && // this is not guards starting position 
                creates_loop(map, lines, columns, guard_position, i, j) // this position creates loop
            ) {
                ++result;
            }
        }
    }

    // Free allocated memory
    free_2d_char_array(map, lines);

    return result;
}

static struct position_t locate_guard(char **map, int lines, int columns)
{
    struct position_t result;

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (map[i][j] == '^') {
                result.i = i;
                result.j = j;
                return result;
            }
        }
    }

    result.i = -1;
    result.j = -1;
    return result;
}

static void patrol_map(char **map, int lines, int columns, struct position_t position)
{
    char direction = '^';
    struct position_t next_position = get_next_position(position, direction);

    while (!is_out_of_map(lines, columns, next_position)) {
        if (map[next_position.i][next_position.j] == '#') {
            direction = rotate(direction);
        } else {
            map[position.i][position.j] = 'X';
            position = next_position;
        }

        next_position = get_next_position(position, direction);
    }

    map[position.i][position.j] = 'X';
}

static int creates_loop(char **map, int lines, int columns, struct position_t position, int x, int y)
{
    map[x][y] = '#';

    struct position_t slow_guard = position;
    char slow_direction = '^';

    struct position_t fast_guard = position;
    char fast_direction = '^';

    do {
        struct position_t next_slow_guard_position = get_next_position(slow_guard, slow_direction);
        if (map[next_slow_guard_position.i][next_slow_guard_position.j] == '#') {
            slow_direction = rotate(slow_direction);
        } else {
            slow_guard = next_slow_guard_position;
        }

        for (int idx = 0; idx < 2; ++idx) {
            struct position_t next_fast_guard_position = get_next_position(fast_guard, fast_direction);
            if (is_out_of_map(lines, columns, next_fast_guard_position)) {
                map[x][y] = 'X';
                return FALSE;
            }

            if (map[next_fast_guard_position.i][next_fast_guard_position.j] == '#') {
                fast_direction = rotate(fast_direction);
            } else {
                fast_guard = next_fast_guard_position;
            }
        }
    } while (!is_out_of_map(lines, columns, fast_guard) && !position_eq(slow_guard, fast_guard, slow_direction, fast_direction));

    map[x][y] = 'X';

    if (is_out_of_map(lines, columns, fast_guard)) {
        return FALSE;
    }

    if (position_eq(slow_guard, fast_guard, slow_direction, fast_direction)) {
        return TRUE;
    }

    return FALSE;
}

static char rotate(char old_direction)
{
    switch (old_direction)
    {
        case '^': return '>';
        case '>': return 'v';
        case 'v': return '<';
        case '<': return '^';
        default: 
            printf("Error: Incorrect direction passed\n");
            return 'E';
            break;
    }
}

static struct position_t get_next_position(struct position_t old_position, char direction)
{
    struct position_t offset;

    switch (direction)
    {
        case '^':
            offset.i = -1;
            offset.j = 0;
            break;
        
        case '>':
            offset.i = 0;
            offset.j = 1;
            break;

        case 'v':
            offset.i = 1;
            offset.j = 0;
            break;

        case '<':
            offset.i = 0;
            offset.j = -1;
            break;

        default:
            printf("Error: Incorrect direction passed\n");
            offset.i = 0;
            offset.j = 0;
            return offset;
    }

    struct position_t new_position = {
        .i = old_position.i + offset.i,
        .j = old_position.j + offset.j
    };

    return new_position;
}

static int position_eq(struct position_t first, struct position_t second, char first_direction, char second_direction)
{
    return (first.i == second.i && first.j == second.j && first_direction == second_direction);
}
