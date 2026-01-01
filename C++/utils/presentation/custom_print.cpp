#include "custom_print.hpp"

#include <iostream>

void print_int_vector(const std::vector<int> &vector, const std::string end)
{
    for (int number : vector) {
        std::cout << number << end;
    }

    std::cout << '\n';
}

void print_long_vector(const std::vector<long> &vector, const std::string end)
{
    for (long number : vector) {
        std::cout << number << end;
    }

    std::cout << '\n';
}

void print_string_vector(const std::vector<std::string> &vector, 
                         const std::string end)
{
    for (std::string text : vector) {
        std::cout << text << end;
    }

    std::cout << '\n';
}

void print_2_int_vectors(const std::vector<int> &left_vector, 
                        const std::vector<int> &right_vector, 
                        const std::string end)
{
    for (size_t i = 0; i < left_vector.size(); ++i) {
        std::cout << left_vector[i] << " " << right_vector[i] << end;
    }

    std::cout << '\n';
}

void print_2d_vector(const std::vector<std::vector<int>> &data,
                     const std::string end)
{
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            std::cout << data[i][j] << " ";
        }
        
        std::cout << end;
    }
}
