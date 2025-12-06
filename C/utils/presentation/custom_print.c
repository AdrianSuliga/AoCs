#include "custom_print.h"

#include <stdio.h>

void print_int_array(const int *array, int size, const char *end)
{
    for (int i = 0; i < size; ++i) {
        printf("%d%s", array[i], end);
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
