#ifndef CUSTOM_PRINT_H
#define CUSTOM_PRINT_H

// print array of ints ending each character with end string
void print_int_array(const int *array, int size, const char *end);

// print array of longs ending each character with end string
void print_long_array(const long *array, int size, const char *end);

// print 2 arrays of ints ending each pair of characters with end string
void print_2_int_arrays(const int *left_array, const int *right_array, int size, const char *end);

// print 2D array with n rows and k columns
void print_2d_int_array(int **array, int n, int k);

// print array of n strings ending each string with end
void print_string_array(char **array, int n, const char *end);

#endif /* CUSTOM_PRINT_H */
