#include "data_parsing/file_read.h"
#include "presentation/custom_print.h"
#include "math/custom_math.h"
#include "memory/custom_allocation.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

static int part_one(char *input);
static int part_two(char *input);
static int is_safe(int *array, int size);
static int is_almost_safe(int *array, int size);

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

    assert(part_one_solution == 246);
    assert(part_two_solution == 318);

    if (mode == RUN) {
        printf("[%.6f s] Part One solution is %d\n", part_one_exec_time, part_one_solution);
        printf("[%.6f s] Part Two solution is %d\n", part_two_exec_time, part_two_solution);
    } else if (mode == TEST) {
        printf("Solutions for 2024 Day 02 are correct [P1 %.6f s | P2 %.6f s]\n",
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
    // Max number of lines
    int size = get_file_line_count(input);
    // Max number of integers per line 
    // (first number is counter of integers)
    int k = get_file_max_char_count_per_line(input, ' ') + 2;

    int **data = malloc_2d_int_array(size, k);
    if (data == NULL) {
        printf("Error: Failed to allocat %d x %d array\n", size, k);
        return -1;
    }

    // Save data from file into prepared array
    read_file_with_n_numbers_per_line(input, ' ', data, size, k);

    // Calculate solution
    int result = 0;
    for (int i = 0; i < size; ++i) {
        if (is_safe(&data[i][1], data[i][0])) {
            ++result;
        }
    }

    free_2d_int_array(data, size);

    return result;
}

static int part_two(char *input)
{
    // Max number of lines
    int size = get_file_line_count(input);
    // Max number of integers per line 
    // (first number is counter of integers)
    int k = get_file_max_char_count_per_line(input, ' ') + 2;

    int **data = malloc_2d_int_array(size, k);
    if (data == NULL) {
        printf("Error: Failed to allocat %d x %d array\n", size, k);
        return -1;
    }

    // Save data from file into prepared array
    read_file_with_n_numbers_per_line(input, ' ', data, size, k);

    // Calculate solution
    int result = 0;
    for (int i = 0; i < size; ++i) {
        if (is_almost_safe(&data[i][1], data[i][0])) {
            ++result;
        }
    }

    free_2d_int_array(data, size);

    return result;
}

static int is_safe(int *array, int size)
{
    if (size <= 1) {
        return TRUE;
    }

    int increasing = array[1] > array[0];

    for (int i = 0; i < size - 1; ++i) {
        if (increasing) {

            if (array[i] >= array[i + 1]) {
                return FALSE;
            }

        } else {

            if (array[i] <= array[i + 1]) {
                return FALSE;
            }

        }

        int difference = abs(array[i] - array[i + 1]);

        if (difference < 1 || difference > 3) {
            return FALSE;
        }
    }

    return TRUE;
}

static int is_almost_safe(int *array, int size)
{
    int *copy = malloc(sizeof(int) * (size - 1));
    if (copy == NULL) {
        printf("Failed to allocate memory\n");
        return FALSE;
    }

    for (int i = 0; i < size; ++i) {
        int idx = 0;
        for (int j = 0; j < size; ++j) {
            if (j == i) {
                continue;
            }

            copy[idx] = array[j];
            ++idx;
        }

        if (is_safe(copy, size - 1)) {
            free(copy);
            return TRUE;
        }
    }

    free(copy);
    return FALSE;
}
