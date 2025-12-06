#include "custom_print.hpp"

#include <iostream>

void print_int_vector(const std::vector<int> &vector, const std::string end)
{
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << end;
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
