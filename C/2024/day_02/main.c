#include "data_parsing/file_read.h"
#include "presentation/custom_print.h"
#include "math/custom_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int part_one(char *input);
static int part_two(char *input);
static int is_safe(int *array, int size);
static int is_almost_safe(int *array, int size);

int main(int argc, char **argv)
{
    char input[] = "input.txt";

    int part_one_solution = part_one(input);
    int part_two_solution = part_two(input);

    printf("Part One solution is %d\n", part_one_solution);
    printf("Part Two solution is %d\n", part_two_solution);

    assert(part_one_solution == 246);
    assert(part_two_solution == 318);

    printf("Solutions are correct\n");

    return 0;
}

static int part_one(char *input)
{
    // Max number of lines
    int size = get_file_line_count(input);
    // Max number of integers per line 
    // (first number is counter of integers)
    int k = get_file_max_char_count(input, ' ') + 2;

    int **data = malloc(size * sizeof(int *));
    if (data == NULL) {
        printf("Error: Failed to allocat %d x %d array\n", size, k);
        return -1;
    }

    for (int i = 0; i < size; ++i) {
        data[i] = malloc(k * sizeof(int));
        if (data[i] == NULL) {
            printf("Error: Failed to allocat %d x %d array\n", size, k);
            return -1;
        }
    }

    // Save data from file into prepared array
    read_file_with_n_numbers_per_line(input, " ", data, size, k);

    // Calculate solution
    int result = 0;
    for (int i = 0; i < size; ++i) {
        if (is_safe(&data[i][1], data[i][0])) {
            ++result;
        }
    }

    for (int i = 0; i < size; ++i) {
        free(data[i]);
    }

    free(data);

    return result;
}

static int part_two(char *input)
{
    // Max number of lines
    int size = get_file_line_count(input);
    // Max number of integers per line 
    // (first number is counter of integers)
    int k = get_file_max_char_count(input, ' ') + 2;

    int **data = malloc(size * sizeof(int *));
    if (data == NULL) {
        printf("Error: Failed to allocat %d x %d array\n", size, k);
        return -1;
    }

    for (int i = 0; i < size; ++i) {
        data[i] = malloc(k * sizeof(int));
        if (data[i] == NULL) {
            printf("Error: Failed to allocat %d x %d array\n", size, k);
            return -1;
        }
    }

    // Save data from file into prepared array
    read_file_with_n_numbers_per_line(input, " ", data, size, k);

    // Calculate solution
    int result = 0;
    for (int i = 0; i < size; ++i) {
        if (is_almost_safe(&data[i][1], data[i][0])) {
            ++result;
        }
    }

    for (int i = 0; i < size; ++i) {
        free(data[i]);
    }

    free(data);

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
