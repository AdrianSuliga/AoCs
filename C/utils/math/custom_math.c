#include "custom_math.h"

int is_on_map(int lines, int columns, struct position_t position)
{
    return (-1 < position.i && position.i < lines &&
            -1 < position.j && position.j < columns);
}

int is_out_of_map(int lines, int columns, struct position_t position)
{
    return !is_on_map(lines, columns, position);
}
