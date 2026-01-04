#include "custom_math.hpp"

bool is_on_map(world_map &map, position &position)
{
    int height = map.size();
    int width = map[0].size();

    return (-1 < position.first && position.first < height &&
            -1 < position.second && position.second < width);
}

bool is_out_of_map(world_map &map, position &position)
{
    return !is_on_map(map, position);   
}
