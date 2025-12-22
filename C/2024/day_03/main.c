#include "data_parsing/file_read.h"
#include "presentation/custom_print.h"

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <assert.h>

static int part_one(char *input);
static int part_two(char *input);
static int extract_from_mul(char *input);

int main(int argc, char **argv)
{
    char input[] = "input.txt";

    int part_one_solution = part_one(input);
    int part_two_solution = part_two(input);

    printf("Part One solution is %d\n", part_one_solution);
    printf("Part Two solution is %d\n", part_two_solution);

    assert(part_one_solution == 196826776);
    assert(part_two_solution == 106780429);

    printf("Solutions are correct\n");

    return 0;
}

static int part_one(char *input)
{
    // Prepare regex
    regex_t *regex = malloc(sizeof(regex_t));
    if (regex == NULL)
    {
        printf("Error: Failed to allocate memory for regex\n");
        return -1;
    }

    if (regcomp(regex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED))
    {
        printf("Error: Could not compile regex\n");
        return -1;
    }

    // Prepare output array
    int regex_count = get_file_regex_count(input, regex);
    if (regex_count < 0)
    {
        printf("Failed to count regexes\n");
        return -1;
    }

    int max_regex_size = 12; // mul(XXX,XXX)

    char **output = malloc(regex_count * sizeof(char *));
    if (output == NULL)
    {
        printf("Error: Failed to allocate memory for output\n");
        return -1;
    }

    for (int i = 0; i < regex_count; ++i)
    {
        output[i] = malloc(max_regex_size * sizeof(char));
        if (output[i] == NULL)
        {
            printf("Error: Failed to allocate memory for output\n");
            return -1;
        }
    }

    // Extract all regexes
    scan_file_for_regex(input, regex, output, regex_count);

    // Calculate solution
    int result = 0;

    for (int i = 0; i < regex_count; ++i)
    {
        result += extract_from_mul(output[i]);
    }

    // Free allocated memory
    regfree(regex);

    for (int i = 0; i < regex_count; ++i)
    {
        free(output[i]);
    }

    free(output);

    return result;
}

static int part_two(char *input)
{
    // Prepare regex
    regex_t *regex = malloc(sizeof(regex_t));
    if (regex == NULL)
    {
        printf("Error: Failed to allocate memory for regex\n");
        return -1;
    }

    if (regcomp(regex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\)", REG_EXTENDED))
    {
        printf("Error: Could not compile regex\n");
        return -1;
    }

    // Prepare output array
    int regex_count = get_file_regex_count(input, regex);
    if (regex_count < 0)
    {
        printf("Failed to count regexes\n");
        return -1;
    }

    int max_regex_size = 12; // mul(XXX,XXX)

    char **output = malloc(regex_count * sizeof(char *));
    if (output == NULL)
    {
        printf("Error: Failed to allocate memory for output\n");
        return -1;
    }

    for (int i = 0; i < regex_count; ++i)
    {
        output[i] = malloc(max_regex_size * sizeof(char));
        if (output[i] == NULL)
        {
            printf("Error: Failed to allocate memory for output\n");
            return -1;
        }
    }

    // Extract all regexes
    scan_file_for_regex(input, regex, output, regex_count);

    int result = 0;
    int extract = 1;

    for (int i = 0; i < regex_count; ++i) {
        if (!strncmp(output[i], "mul", 3)) {
            if (extract) {
                result += extract_from_mul(output[i]);
            }
        } else if (!strncmp(output[i], "do()", 4)) {
            extract = 1;
        } else if (!strncmp(output[i], "don't()", 6)) {
            extract = 0;
        } else {
            printf("Error: Invalid regex found %s\n", output[i]);
            return -1;
        }
    }

    // Free allocated memory
    regfree(regex);

    for (int i = 0; i < regex_count; ++i)
    {
        free(output[i]);
    }

    free(output);

    return result;
}

static int extract_from_mul(char *input)
{
    // Find first number
    char number[4];
    int j = 0, midpoint = 0;
    for (int k = 0; input[k] != '\0'; ++k)
    {
        if ('0' <= input[k] && input[k] <= '9')
        {
            number[j] = input[k];
            ++j;
        }

        if (input[k] == ',')
        {
            number[j] = '\0';
            midpoint = k;
            break;
        }
    }

    j = 0;

    int first_number = atoi(number);

    // Find second number
    for (int k = midpoint; input[k] != '\0'; ++k)
    {
        if ('0' <= input[k] && input[k] <= '9')
        {
            number[j] = input[k];
            ++j;
        }

        if (input[k] == ')')
        {
            number[j] = '\0';
            break;
        }
    }

    int second_number = atoi(number);

    return first_number * second_number;
}
