#ifndef FILE_READ_H
#define FILE_READ_H

// Count number of lines in file with given file name
int get_file_line_count(const char *file_name);

// Count maximum number of times sign appears in one line
int get_file_max_char_count(const char *file_name, const char sign);

// Read numbers from file containing two columns of 
// integers separated by separator string
void read_file_with_2_columns(const char *file_name, const char *separator, 
                            int *left_array, int *right_array, int size);

// Read numbers from file where each line has maximum of k
// integers separated by separator string. Output is 2D
// integer array where each row starts with number of integers
// present in a row
void read_file_with_n_numbers_per_line(const char *file_name, const char *separator,
                                    int **output, int size, int k);

#endif /* FILE_READ_H */
