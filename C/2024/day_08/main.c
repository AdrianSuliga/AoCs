#include "data_parsing/file_read.h"
#include "memory/custom_allocation.h"
#include "presentation/custom_print.h"
#include "math/custom_math.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int part_one(char *input);
static int part_two(char *input);
static int find_antinodes(char *input, void (*mark_function)(char**, int, int, int, int, int, int));
static int is_antenna(char sign);
static void mark_antinodes(char **antinodes, int lines, int columns, 
                           int x1, int y1, int x2, int y2);
static void mark_antinodes_resonant(char **antinodes, int lines, int columns, 
                                    int x1, int y1, int x2, int y2);

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
    long part_one_solution = part_one(input);
    clock_t part_one_end = clock();

    double part_one_exec_time = ((double)(part_one_end - part_one_start)) / CLOCKS_PER_SEC;

    clock_t part_two_start = clock();
    long part_two_solution = part_two(input);
    clock_t part_two_end = clock();

    double part_two_exec_time = ((double)(part_two_end - part_two_start)) / CLOCKS_PER_SEC;

    assert(part_one_solution == 376);
    assert(part_two_solution == 1352);

    if (mode == RUN) {
        printf("[%.6f s] Part One solution is %ld\n", part_one_exec_time, part_one_solution);
        printf("[%.6f s] Part Two solution is %ld\n", part_two_exec_time, part_two_solution);
    } else if (mode == TEST) {
        printf("Solutions for 2024 Day 08 are correct [P1 %.6f s | P2 %.6f s]\n",
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
    return find_antinodes(input, &mark_antinodes);
}

static int part_two(char *input)
{
    return find_antinodes(input, &mark_antinodes_resonant);
}

static int find_antinodes(char *input, void (*mark_function)(char**, int, int, int, int, int, int))
{
    // Read data from file
    int lines = get_file_line_count(input);
    int columns = get_file_first_line_width(input);

    // +2 to account for endline and null terminator
    char **data = malloc_2d_char_array(lines, columns + 2);
    if (data == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        return -1;
    }

    char **antinodes = malloc_2d_char_array(lines, columns + 1);
    if (antinodes == NULL) {
        free_2d_char_array(data, lines);
        printf("Error: Failed to allocate enough memory\n");
        return -1;
    }

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            antinodes[i][j] = '.';
        }
        antinodes[i][columns] = '\0';
    }

    read_2d_char_array(input, data, lines, columns + 2);

    // Mark antinodes
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (is_antenna(data[i][j])) {
                for (int p = j + 1; p < columns; ++p) {
                    if (data[i][j] == data[i][p]) {
                        (*mark_function)(antinodes, lines, columns, i, j, i, p);
                    }
                }

                for (int k = i + 1; k < lines; ++k) {
                    for (int l = 0; l < columns; ++l) {
                        if (data[i][j] == data[k][l]) {
                            (*mark_function)(antinodes, lines, columns, i, j, k, l);
                        }
                    }
                }
            }
        }
    }

    // Calculate solution
    int result = 0;

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (antinodes[i][j] == '#') {
                ++result;
            }
        }
    }

    free_2d_char_array(data, lines);
    free_2d_char_array(antinodes, lines);

    return result;
}

static int is_antenna(char sign)
{
    return (
        ('0' <= sign && sign <= '9') ||
        ('a' <= sign && sign <= 'z') ||
        ('A' <= sign && sign <= 'Z')
    );
}

static void mark_antinodes(char **antinodes, int lines, int columns, 
                           int x1, int y1, int x2, int y2)
{
    int x_distance = x2 - x1;
    int y_distance = y2 - y1;

    int a1_x = -1, a1_y = -1;
    int a2_x = -1, a2_y = -1;

    a1_x = x2 + x_distance;
    a1_y = y2 + y_distance;
    
    a2_x = x1 - x_distance;
    a2_y = y1 - y_distance;

    if (-1 < a1_x && a1_x < lines && -1 < a1_y && a1_y < columns) {
        antinodes[a1_x][a1_y] = '#';
    }
    
    if (-1 < a2_x && a2_x < lines && -1 < a2_y && a2_y < columns) {
        antinodes[a2_x][a2_y] = '#';
    }
}

static void mark_antinodes_resonant(char **antinodes, int lines, int columns, 
                                    int x1, int y1, int x2, int y2)
{
    int x_difference = x2 - x1;
    int y_difference = y2 - y1;

    int a1_x = x2;
    int a1_y = y2;

    while (-1 < a1_x && a1_x < lines && -1 < a1_y && a1_y < columns) {
        antinodes[a1_x][a1_y] = '#';
        
        a1_x += x_difference;
        a1_y += y_difference;
    }

    int a2_x = x1;
    int a2_y = y1;

    while (-1 < a2_x && a2_x < lines && -1 < a2_y && a2_y < columns) {
        antinodes[a2_x][a2_y] = '#';

        a2_x -= x_difference;
        a2_y -= y_difference;
    }
}
