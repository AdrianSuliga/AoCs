#ifndef FILE_READ_H
#define FILE_READ_H

#include <regex.h>

// Count number of chars in file with given file name
int get_file_total_char_count(const char *file_name);

// Count number of times given char appears in the file
int get_file_char_count(const char *file_name, const char sign);

// Count number of lines in file with given file name
int get_file_line_count(const char *file_name);

// Count number of chars in first line of a file
int get_file_first_line_width(const char *file_name);

// Count maximum number of times sign appears in one line
int get_file_max_char_count_per_line(const char *file_name, const char sign);

// Count how many times given regex appears in the text file
int get_file_regex_count(const char *file_name, const regex_t *regex);

// Read numbers from file containing two columns of 
// integers separated by separator string
void read_file_with_2_columns(const char *file_name, const char *separator, 
                            int *left_array, int *right_array, int size);

// Read numbers from file where each line has maximum of k
// integers separated by separator char. Output is 2D
// integer array where each row starts with number of integers
// present in a row
void read_file_with_n_numbers_per_line(const char *file_name, const char separator,
                                    int **output, int size, int k);

// Read strings from file with n lines and k columns
void read_2d_char_array(const char *file_name, char **output, int n, int k);

// Read file that starts with two columns of integers seperated by column_separator
// string and ends with readings_size lines of integers separated by line_separator
// char, each column has at most max_read_per_line numbers
void read_file_with_2_columns_n_numbers_per_line(const char *file_name, int *left_column, 
                                                 int *right_column, const char *column_separator,
                                                 int column_size, int **readings, const char line_separator,
                                                 int readings_size, int max_read_per_line);

// Read file that has columns of longs separated by separator char and save
// first column into given array
void read_file_first_column_of_longs(const char *file_name, const char separator,
                                     long *output, int n);

// Scan file for given regex, save maximum of size to output
void scan_file_for_regex(const char *file_name, const regex_t *regex,
                        char **output, int size);

#endif /* FILE_READ_H */
