#ifndef CUSTOM_ALLOCATION_H
#define CUSTOM_ALLOCATION_H

int** malloc_2d_int_array(int lines, int columns);

void free_2d_int_array(int **array, int lines);

char** malloc_2d_char_array(int lines, int columns);

void free_2d_char_array(char **array, int lines);

#endif /* CUSTOM_ALLOCATION_H */
