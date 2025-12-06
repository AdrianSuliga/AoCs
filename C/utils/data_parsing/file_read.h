#ifndef FILE_READ_H
#define FILE_READ_H

// Count number of lines in file with given file name
int get_file_line_count(const char *file_name);

// Read numbers from file containing two columns of 
// integers separated by separator string
void read_file_with_2_columns(const char *file_name, const char *separator, 
                            int *left_array, int *right_array, int size);

#endif /* FILE_READ_H */
