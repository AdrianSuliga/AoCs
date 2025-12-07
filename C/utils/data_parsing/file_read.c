#include "file_read.h"
#include "math/custom_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_file_line_count(const char *file_name)
{
    FILE* fptr = fopen(file_name, "r");
    int result = 0;

    if (fptr == NULL) {
        printf("Error: Failed to open %s", file_name);
        return -1;
    }

    size_t buffer_size = 64;
    char buffer[buffer_size];

    while (fgets(buffer, buffer_size, fptr) != NULL) {
        ++result;
    }

    fclose(fptr);

    return result;
}

int get_file_max_char_count(const char *file_name, const char sign)
{
    FILE* fptr = fopen(file_name, "r");
    int result = 0;

    if (fptr == NULL) {
        printf("Error: Failed to open %s", file_name);
        return -1;
    }

    size_t buffer_size = 64;
    char buffer[buffer_size];

    while (fgets(buffer, buffer_size, fptr) != NULL) {
        int local = 0;
        for (size_t i = 0; buffer[i] != '\n'; ++i) {
            if (buffer[i] == sign) {
                ++local;
            }
        }

        result = MAX(result, local);
    }

    fclose(fptr);

    return result;
}

void read_file_with_2_columns(const char *file_name, const char *separator, int *left_array, int *right_array, int size)
{
    FILE* fptr = fopen(file_name, "r");

    if (fptr == NULL) {
        printf("Error: Failed to open %s", file_name);
        return;
    }

    size_t buffer_size = 64;
    char buffer[buffer_size];
    int write_idx = 0;

    while (fgets(buffer, buffer_size, fptr) != NULL) {
        char *left_num = strtok(buffer, separator);
        char *right_num = strtok(NULL, separator);

        int left = atoi(left_num);
        int right = atoi(right_num);

        left_array[write_idx] = left;
        right_array[write_idx] = right;

        ++write_idx;
    }

    fclose(fptr);
}

void read_file_with_n_numbers_per_line(const char *file_name, const char *separator,
                                    int **output, int size, int k)
{
    FILE *fptr = fopen(file_name, "r");

    if (fptr == NULL) {
        printf("Error: Failed to open %s", file_name);
        return;
    }

    size_t buffer_size = 64;
    char buffer[buffer_size];
    int line_idx = 0;

    while (fgets(buffer, buffer_size, fptr) != NULL) {
        int counter = 0;
        // Count number of integers in one line
        for (size_t i = 0; buffer[i] != '\n'; ++i) {
            if (buffer[i] == ' ') {
                ++counter;
            }
        }
        ++counter;
        output[line_idx][0] = counter;

        int column_idx = 1;
        char *number = strtok(buffer, " ");
        
        while (number != NULL) {
            output[line_idx][column_idx] = atoi(number);
            ++column_idx;
            number = strtok(NULL, " ");
        }

        ++line_idx;
    }

    fclose(fptr);
}
