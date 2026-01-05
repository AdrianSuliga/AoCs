#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

#define TRUE 1
#define FALSE 0

#define MAX(a, b) ((a) >= (b) ? (a) : (b)) 
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

struct position_t {
    int i;
    int j;
};

enum cmd {
    RUN,
    TEST
};

int is_on_map(int lines, int columns, struct position_t position);
int is_out_of_map(int lines, int columns, struct position_t position);

#endif /* CUSTOM_MATH_H */
