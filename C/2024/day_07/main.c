#include "data_parsing/file_read.h"
#include "memory/custom_allocation.h"
#include "presentation/custom_print.h"
#include "math/custom_math.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static long part_one(char *input);
static long part_two(char *input);
static int check_recursive(int *array, int size, long target, long result, int idx);
static int check_recursive_concat(int *array, int size, long target, long result, int idx);
static int is_possible(int *array, int size, long target);
static int is_possible_concat(int *array, int size, long target);

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Error: Wrong number of arguments. Expected 3, got %d\n", argc);
        printf("How to use: ./main <path_to_input> <mode>\n");
        return 1;
    }

    char *input = argv[1];
    int mode = atoi(argv[2]);

    long part_one_solution = part_one(input);
    long part_two_solution = part_two(input);

    assert(part_one_solution == 2941973819040);
    assert(part_two_solution == 249943041417600);

    if (mode == RUN) {
        printf("Part One solution is %ld\n", part_one_solution);
        printf("Part Two solution is %ld\n", part_two_solution);
    } else if (mode == TEST) {
        printf("Solutions for 2024 Day 07 are correct\n");
    } else {
        printf("Error: Wrong mode selected %d\n", mode);
        return -1;
    }

    return 0;
}

static long part_one(char *input)
{
    // Extract data from file
    int lines = get_file_line_count(input);
    int max_columns = get_file_max_char_count_per_line(input, ' ') + 2; // 1 for maximum count and 1
                                                                        // for actual count at index 0

    long *targets = malloc(lines * sizeof(long));
    if (targets == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        return -1;
    }

    int **data = malloc_2d_int_array(lines, max_columns);
    if (data == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        free(targets);
        return -1;
    }

    read_file_with_n_numbers_per_line(input, ' ', data, lines, max_columns);
    read_file_first_column_of_longs(input, ' ', targets, lines);

    // Calculate result
    long result = 0;

    for (int i = 0; i < lines; ++i) {
        if (is_possible(&data[i][2], data[i][0] - 1, targets[i])) {
            result += targets[i];
        }
    }

    free_2d_int_array(data, lines);
    free(targets);

    return result;
}

static long part_two(char *input)
{
    // Extract data from file
    int lines = get_file_line_count(input);
    int max_columns = get_file_max_char_count_per_line(input, ' ') + 2; // 1 for maximum count and 1
                                                                        // for actual count at index 0

    long *targets = malloc(lines * sizeof(long));
    if (targets == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        return -1;
    }

    int **data = malloc_2d_int_array(lines, max_columns);
    if (data == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        free(targets);
        return -1;
    }

    read_file_with_n_numbers_per_line(input, ' ', data, lines, max_columns);
    read_file_first_column_of_longs(input, ' ', targets, lines);

    // Calculate result
    long result = 0;

    for (int i = 0; i < lines; ++i) {
        if (is_possible_concat(&data[i][2], data[i][0] - 1, targets[i])) {
            result += targets[i];
        }
    }

    free_2d_int_array(data, lines);
    free(targets);

    return result;
}

static int check_recursive(int *array, int size, long target, long result, int idx)
{
    if (idx == size) {
        return target == result;
    }

    if (result > target) {
        return FALSE;
    }

    return check_recursive(array, size, target, result + array[idx], idx + 1) ||
           check_recursive(array, size, target, result * array[idx], idx + 1);
}

static int is_possible(int *array, int size, long target)
{
    return check_recursive(array, size, target, array[0], 1);
}

static int check_recursive_concat(int *array, int size, long target, long result, int idx)
{
    if (idx == size) {
        return target == result;
    }

    if (result > target) {
        return FALSE;
    }

    long result_concat = result;
    int to_add = array[idx];

    while (to_add != 0) {
        result_concat *= 10;
        to_add /= 10;
    }

    result_concat += array[idx];

    return check_recursive_concat(array, size, target, result + array[idx], idx + 1) ||
           check_recursive_concat(array, size, target, result * array[idx], idx + 1) ||
           check_recursive_concat(array, size, target, result_concat, idx + 1);
}

static int is_possible_concat(int *array, int size, long target)
{
    return check_recursive_concat(array, size, target, array[0], 1);
}
