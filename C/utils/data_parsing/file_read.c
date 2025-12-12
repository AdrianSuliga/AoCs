#include "file_read.h"
#include "math/custom_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_file_char_count(const char *file_name)
{
    FILE* fptr = fopen(file_name, "r");

    if (fptr == NULL) {
        printf("Error: Failed to open %s", file_name);
        return -1;
    }

    int result = 0;
    char buffer;

    while ((buffer = fgetc(fptr))) {
        if (buffer == EOF) {
            break;
        }
        ++result;
    }

    fclose(fptr);

    return result;
}

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

int get_file_regex_count(const char *file_name, const regex_t *regex)
{
    int file_length = get_file_char_count(file_name);

    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        printf("Failed to open file %s\n", file_name);
        return -1;
    }

    char *buffer = malloc(file_length * sizeof(char));
    if (buffer == NULL) {
        printf("Failed to allocated enough memory\n");
        return -1;
    }

    fread(buffer, sizeof(char) * file_length, 1, fptr);

    regmatch_t found;
    int total_offset = 0;
    int result = 0;
    
    while (regexec(regex, buffer, 1, &found, 0) == 0) {
        total_offset += found.rm_eo;
        buffer += found.rm_eo;
        ++result;

        if (total_offset >= file_length * sizeof(char)) {
            break;
        }
    }
    buffer -= total_offset;

    fclose(fptr);
    free(buffer);

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

void scan_file_for_regex(const char *file_name, const regex_t *regex,
                        char **output, int size)
{
    int file_length = get_file_char_count(file_name);

    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        printf("Failed to open file %s\n", file_name);
        return;
    }

    char *buffer = malloc(file_length * sizeof(char));
    if (buffer == NULL) {
        printf("Failed to allocated enough memory\n");
        return;
    }

    fread(buffer, sizeof(char) * file_length, 1, fptr);

    regmatch_t found;
    int total_offset = 0;
    int idx = 0;
    
    while (regexec(regex, buffer, 1, &found, 0) == 0) {
        int found_size = found.rm_eo - found.rm_so;
        
        strncpy(output[idx], buffer + found.rm_so, found_size);
        output[idx][found_size] = '\0'; // End string

        total_offset += found.rm_eo;
        buffer += found.rm_eo;
        ++idx;

        if (total_offset >= file_length * sizeof(char)) {
            break;
        }
    }
    buffer -= total_offset;

    fclose(fptr);
    free(buffer);
}
