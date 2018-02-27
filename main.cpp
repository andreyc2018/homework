#include "matrix.h"
#include <iostream>

int main(int, char const**)
{
    try {
        using matrix_t = Matrix<int, 2, 0>;
        matrix_t m;
        int size = 10;
        for (int i = 0; i < size; ++i) {
            m.set(i, i, i);
            int j = size - i - 1;
            m.set(j, i, j);
        }
        m.get(1, 2) = 10;
        std::cout << m.get(1, 2).get_value() << "\n";
        for (int i = 1; i < size - 1; ++i) {
            for (int j = 1; j < size - 1; ++j) {
                std::cout << m.get(i, j).get_value() << " ";
            }
            std::cout << "\n";
        }

        std::cout << m.size() << "\n";

        for (int i = 1; i < size - 1; ++i) {
            for (int j = 1; j < size - 1; ++j) {
                if (m.get(i, j).get_value() != m.default_value()) {
                    std::cout << "[" << i << "]" << "[" << j << "] = "
                              << m.get(i, j).get_value() << "\n";
                }
            }
        }
        m.get(0, 1) = 10;
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

