#include <data_parsing/file_read.hpp>
#include <presentation/custom_print.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <utility>

static int part_one(std::string file_name);
static int part_two(std::string file_name);
static int xmas_count(std::vector<std::string> &data, int i, int j);
static int x_mas_count(std::vector<std::string> &data, int i, int j);

int main()
{
    std::string filename = "input.txt";

    std::cout << "Part One solution is " << part_one(filename) << "\n";
    std::cout << "Part Two solution is " << part_two(filename) << "\n";

    return 0;
}

static int part_one(std::string file_name)
{
    // Read file content
    std::vector<std::string> data;
    read_file_into_string_vector(file_name, data);

    // Count XMAS
    int result = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            if (data[i][j] == 'X') {
                result += xmas_count(data, i, j);
            }
        }
    }

    return result;
}

static int part_two(std::string file_name)
{
    // Read file content
    std::vector<std::string> data;
    read_file_into_string_vector(file_name, data);

    // Count XMAS
    int result = 0;

    for (size_t i = 1; i < data.size() - 1; ++i) {
        for (size_t j = 1; j < data[i].size() - 1; ++j) {
            if (data[i][j] == 'A') {
                result += x_mas_count(data, i, j);
            }
        }
    }

    return result;
}

static int xmas_count(std::vector<std::string> &data, int i, int j)
{
    std::string mas = "MAS";
    std::vector<std::pair<int, int>> moves = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
        {1, 1}, {1, 0}, {1, -1}, {0, -1}
    };
    int result = 0;

    for (auto &move : moves) {
        int i_offset = i + move.first;
        int j_offset = j + move.second;

        int lines = data.size();
        int columns = data[i].size();

        bool abort = false;

        for (char sign : mas) {
            if (!(-1 < i_offset && i_offset < lines &&
                -1 < j_offset && j_offset < columns &&
                data[i_offset][j_offset] == sign
            )) {
                abort = true;
                break;
            }

            i_offset += move.first;
            j_offset += move.second;
        }

        if (abort) {
            continue;
        }

        ++result;
    }

    return result;
}

static int x_mas_count(std::vector<std::string> &data, int i, int j)
{
    std::string shape = "";
    shape += data[i - 1][j - 1];
    shape += data[i - 1][j + 1];
    shape += data[i + 1][j + 1];
    shape += data[i + 1][j - 1];

    return static_cast<int>(
        shape == "MSSM" ||
        shape == "MMSS" ||
        shape == "SSMM" ||
        shape == "SMMS"
    );
}
