#include "custom_allocation.h"

#include <stdlib.h>

int** malloc_2d_int_array(int lines, int columns)
{
    int **array = malloc(lines * sizeof(int *));
    if (array == NULL) {
        return NULL;
    }

    for (int i = 0; i < lines; ++i) {
        array[i] = malloc(columns * sizeof(int));
        if (array[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }

    return array;
}

void free_2d_int_array(int **array, int lines)
{
    for (int i = 0; i < lines; ++i) {
        free(array[i]);
    }

    free(array);
}

char** malloc_2d_char_array(int lines, int columns)
{
    char **array = malloc(lines * sizeof(char *));
    if (array == NULL) {
        return NULL;
    }

    for (int i = 0; i < lines; ++i) {
        array[i] = malloc(columns * sizeof(char));
        if (array[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }
    
    return array;
}

void free_2d_char_array(char **array, int lines)
{
    for (int i = 0; i < lines; ++i) {
        free(array[i]);
    }

    free(array);
}
