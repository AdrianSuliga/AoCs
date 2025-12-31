#include "custom_print.h"

#include <stdio.h>

void print_int_array(const int *array, int size, const char *end)
{
    for (int i = 0; i < size; ++i) {
        printf("%d%s", array[i], end);
    }
    printf("\n");
}

void print_long_array(const long *array, int size, const char *end)
{
    for (int i = 0; i < size; ++i) {
        printf("%ld%s", array[i], end);
    }
    printf("\n");
}

void print_2_int_arrays(const int *left_array, const int *right_array, int size, const char *end)
{
    for (int i = 0; i < size; ++i) {
        printf("%d %d%s", left_array[i], right_array[i], end);
    }
    printf("\n");
}

void print_2d_int_array(int **array, int n, int k)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= array[i][0]; ++j) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

void print_string_array(char **array, int n, const char *end)
{
    for (int i = 0; i < n; ++i) {
        printf("%s%s", array[i], end);
    }
    printf("\n");
}
