#include "data_parsing/file_read.h"
#include "memory/custom_allocation.h"
#include "presentation/custom_print.h"
#include "math/custom_math.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static int part_one(char *input);
static int part_two(char *input);
static int is_correctly_ordered(int *reading, int size, int *left_array,
                                int *right_array, int column_size);
static void order_correctly(int *reading, int size, int *left_array,
                            int *right_array, int column_size);

int main(int argc, char **argv)
{
    char input[] = "input.txt";

    int part_one_solution = part_one(input);
    int part_two_solution = part_two(input);

    printf("Part One solution is %d\n", part_one_solution);
    printf("Part Two solution is %d\n", part_two_solution);

    assert(part_one_solution == 4959);
    assert(part_two_solution == 4655);

    printf("Solutions are correct\n");

    return 0;
}

static int part_one(char *input)
{
    // Allocate needed memory 
    int column_height = get_file_char_count(input, '|');

    int *left_array = malloc(column_height * sizeof(int));
    if (left_array == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        return -1;
    }

    int *right_array = malloc(column_height * sizeof(int));
    if (right_array == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        free(left_array);
        return -1;
    }

    int readings_size = get_file_line_count(input) - column_height - 1;
    int max_readings_per_line = get_file_max_char_count_per_line(input, ',') + 1;

    int **readings = malloc_2d_int_array(readings_size, max_readings_per_line + 1);
    if (readings == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        free(left_array);
        free(right_array);
        return -1;
    }

    // Extract data from the file
    read_file_with_2_columns_n_numbers_per_line(input, left_array, right_array, "|",
                                                column_height, readings, ',', readings_size, 
                                                max_readings_per_line);

    // Calculate solution
    int result = 0;

    for (int i = 0; i < readings_size; ++i) {
        if (is_correctly_ordered(&readings[i][1], readings[i][0], left_array, right_array, column_height)) {
            result += readings[i][(readings[i][0] / 2) + 1];
        }
    }

    // Free memory
    free(left_array);
    free(right_array);

    free_2d_int_array(readings, readings_size);

    return result;
}

static int part_two(char *input)
{
    // Allocate needed memory 
    int column_height = get_file_char_count(input, '|');

    int *left_array = malloc(column_height * sizeof(int));
    if (left_array == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        return -1;
    }

    int *right_array = malloc(column_height * sizeof(int));
    if (right_array == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        free(left_array);
        return -1;
    }

    int readings_size = get_file_line_count(input) - column_height - 1;
    int max_readings_per_line = get_file_max_char_count_per_line(input, ',') + 1;

    int **readings = malloc_2d_int_array(readings_size, max_readings_per_line + 1);
    if (readings == NULL) {
        printf("Error: Failed to allocate enough memory\n");
        free(left_array);
        free(right_array);
        return -1;
    }

    // Extract data from the file
    read_file_with_2_columns_n_numbers_per_line(input, left_array, right_array, "|",
                                                column_height, readings, ',', readings_size, 
                                                max_readings_per_line);

    // Calculate solution
    int result = 0;

    for (int i = 0; i < readings_size; ++i) {
        if (!is_correctly_ordered(&readings[i][1], readings[i][0], left_array, right_array, column_height)) {
            order_correctly(&readings[i][1], readings[i][0], left_array, right_array, column_height);
            result += readings[i][(readings[i][0] / 2) + 1];
        }
    }

    // Free memory
    free(left_array);
    free(right_array);

    free_2d_int_array(readings, readings_size);

    return result;
}

static int is_correctly_ordered(int *reading, int size, int *left_array, 
                                int *right_array, int column_size)
{
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            for (int k = 0; k < column_size; ++k) {
                if (reading[i] == right_array[k] && reading[j] == left_array[k]) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

static void swap(int *array, int i, int j)
{
    int buffer = array[i];
    array[i] = array[j];
    array[j] = buffer;
}

static void order_correctly(int *reading, int size, int *left_array,
                            int *right_array, int column_size)
{
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            for (int k = 0; k < column_size; ++k) {
                if (reading[i] == right_array[k] && reading[j] == left_array[k]) {
                    swap(reading, i, j);
                }
            }
        }
    }
}
