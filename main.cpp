#include "matrix.h"
#include <iostream>

int main(int, char const**)
{
    try {
        using matrix_t = Matrix<int, 2, 0>;
        matrix_t m;
        int size = 10;
        for (int i = 0; i < size; ++i) {
            m(i, i) = i;
            int j = size - i - 1;
            m(i, j) = j;
        }
        for (int i = 1; i < size - 1; ++i) {
            for (int j = 1; j < size - 1; ++j) {
                std::cout << m(i, j) << " ";
            }
            std::cout << "\n";
        }

        std::cout << m.size() << "\n";

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (m(i, j) != m.default_value()) {
                    std::cout << "[" << i << "]" << "[" << j << "] = "
                              << m(i, j) << "\n";
                }
            }
        }
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

