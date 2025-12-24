#include "data_parsing/file_read.h"
#include "presentation/custom_print.h"
#include "memory/custom_allocation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int part_one(char *input);
static int part_two(char *input);
static int xmas_count(char **data, int lines, int columns, int i, int j);
static int x_mas_present(char **data, int i, int j);

int main(int argc, char **argv)
{
    char input[] = "input.txt";

    int part_one_solution = part_one(input);
    int part_two_solution = part_two(input);

    printf("Part One solution is %d\n", part_one_solution);
    printf("Part Two solution is %d\n", part_two_solution);

    assert(part_one_solution == 2434);
    assert(part_two_solution == 1835);

    printf("Solutions are correct\n");

    return 0;
}

static int part_one(char *input)
{
    // Get file dimensions
    int lines = get_file_line_count(input);
    int columns = get_file_first_line_width(input) + 2; // Account for \n and \0

    // Allocate memory for file content
    char **data = malloc_2d_char_array(lines, columns);
    if (data == NULL) {
        printf("Failed to allocate memory\n");
        return -1;
    }

    // Read file content
    read_2d_char_array(input, data, lines, columns);

    // Search for XMAS
    int result = 0;

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (data[i][j] == 'X') {
                result += xmas_count(data, lines, columns, i, j);
            }
        }
    }

    // Free allocated memory
    free_2d_char_array(data, lines);

    return result;
}

static int part_two(char *input)
{
    // Get file dimensions
    int lines = get_file_line_count(input);
    int columns = get_file_first_line_width(input) + 2; // Account for \n and \0

    // Allocate memory for file content
    char **data = malloc_2d_char_array(lines, columns);
    if (data == NULL) {
        printf("Failed to allocate memory\n");
        return -1;
    }

    // Read file content
    read_2d_char_array(input, data, lines, columns);

    // Search for X-MAS
    int result = 0;

    for (int i = 1; i < lines - 1; ++i) {
        for (int j = 1; j < columns - 3; ++j) {
            if (data[i][j] == 'A' && x_mas_present(data, i, j)) {
                ++result;
            }
        }
    }

    // Free allocated memory
    free_2d_char_array(data, lines);

    return result;
}

static int xmas_count(char **data, int lines, int columns, int i, int j)
{
    char mas_array[3] = {'M', 'A', 'S'};
    int moves[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
        {1, 1}, {1, 0}, {1, -1}, {0, -1}
    };
    int result = 0;

    for (int move_idx = 0; move_idx < 8; ++move_idx) {
        int i_offset = i + moves[move_idx][0];
        int j_offset = j + moves[move_idx][1];

        int abort_flag = 0;

        for (int k = 0; k < 3; ++k) {
            if (!(-1 < i_offset && i_offset < lines &&
                -1 < j_offset && j_offset < columns &&
                data[i_offset][j_offset] == mas_array[k]
            )) {
                abort_flag = 1;
                break;
            }

            i_offset += moves[move_idx][0];
            j_offset += moves[move_idx][1];
        }

        if (abort_flag) {
            continue;
        }

        ++result;
    }

    return result;
}

static int x_mas_present(char **data, int i, int j)
{
    char shape[4] = {
        data[i - 1][j - 1], data[i - 1][j + 1],
        data[i + 1][j + 1], data[i + 1][j - 1]
    };

    return (
        !strcmp(shape, "MSSM") ||
        !strcmp(shape, "MMSS") ||
        !strcmp(shape, "SSMM") ||
        !strcmp(shape, "SMMS")
    );
}
