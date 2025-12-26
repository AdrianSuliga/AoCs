#include "data_parsing/file_read.h"
#include "presentation/custom_print.h"
#include "sorting/heap_sort.h"
#include "math/custom_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int part_one(char *input, int n);
static int part_two(char *input, int n);

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Error: Wrong number of arguments. Expected 3, got %d\n", argc);
        printf("How to use: ./main <path_to_input> <mode>\n");
        return 1;
    }

    char *input = argv[1];
    int mode = atoi(argv[2]);

    int n = get_file_line_count(input);

    if (n < 0) {
        printf("Error: Failed to get line count from %s\n", input);
        return -1;
    }

    int part_one_solution = part_one(input, n);
    int part_two_solution = part_two(input, n);

    assert(part_one_solution == 1970720);
    assert(part_two_solution == 17191599);

    if (mode == RUN) {
        printf("Part One solution is %d\n", part_one_solution);
        printf("Part Two solution is %d\n", part_two_solution);
    } else if (mode == TEST) {
        printf("Solutions for 2024 Day 01 are correct\n");
    } else {
        printf("Error: Wrong mode selected %d\n", mode);
        return -1;
    }

    return 0;
}

static int part_one(char *input, int n)
{
    /* Parse input from text file */
    int *left_array = malloc(sizeof(int) * n);
    if (left_array == NULL) {
        printf("Error: Failed to allocate %d bytes of memory\n", n);
        return -1;
    }

    int *right_array = malloc(sizeof(int) * n);
    if (right_array == NULL) {
        printf("Error: Failed to allocate %d bytes of memory\n", n);
        free(left_array);
        return -1;
    }

    read_file_with_2_columns(input, "  ", left_array, right_array, n);

    /* Sort both arrays */
    heap_sort(left_array, n);
    heap_sort(right_array, n);

    /* Calculate solution */
    int result = 0;

    for (int i = 0; i < n; ++i) {
        result += abs(left_array[i] - right_array[i]);
    }

    free(left_array);
    free(right_array);

    return result;
}

static int part_two(char *input, int n)
{
    /* Parse input from text file */
    int *left_array = malloc(sizeof(int) * n);
    if (left_array == NULL) {
        printf("Error: Failed to allocate %d bytes of memory\n", n);
        return -1;
    }

    int *right_array = malloc(sizeof(int) * n);
    if (right_array == NULL) {
        printf("Error: Failed to allocate %d bytes of memory\n", n);
        free(left_array);
        return -1;
    }

    read_file_with_2_columns(input, "  ", left_array, right_array, n);

    /* Sort both arrays for quicker lookup */
    heap_sort(left_array, n);
    heap_sort(right_array, n);

    /* Calculate solution */
    int similarity_score = 0;

    // For each element of left array
    for (int left_idx = 0; left_idx < n; ++left_idx) {
        
        int occurences = 0;

        // Go through right array looking for occurences
        for (int right_idx = 0; right_idx < n; ++right_idx) {
            // If you find elements on the right bigger than one on
            // the left than abort, no more occurences to be found
            // for this one
            if (right_array[right_idx] > left_array[left_idx]) {
                break;
            }

            // Count found occurences
            if (right_array[right_idx] == left_array[left_idx]) {
                ++occurences;
            }
        }

        similarity_score += occurences * left_array[left_idx];
    }

    return similarity_score;
}
