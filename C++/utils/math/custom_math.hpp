#pragma once

#include <utility>
#include <vector>
#include <string>

using position = std::pair<int, int>;
using world_map = std::vector<std::string>;

enum CMD {
    RUN,
    TEST
};

bool is_on_map(world_map &map, position &position);

bool is_out_of_map(world_map &map, position &position);
