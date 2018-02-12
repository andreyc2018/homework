#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
void read_input(T& student, T& professor)
{
    size_t n;
    std::string line;
    std::getline(std::cin, line);
    n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        professor.push_back(std::stoul(line));
    }
    std::getline(std::cin, line);
    n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        student.push_back(std::stoul(line));
    }
}

template<typename T>
void print_output(T& student, T& professor)
{
    std::sort(student.begin(), student.end());
    std::sort(professor.begin(), professor.end());
    T up;
    std::unique_copy(professor.begin(), professor.end(), std::back_inserter(up));
    size_t count = 0;
    for (const auto& s : up) {
        auto lower = std::lower_bound(student.begin(), student.end(), s);
        auto upper = std::upper_bound(lower, student.end(), s);
        count += std::distance(lower, upper);
    }
    std::cout << count << "\n";
}

int main(int, char const**)
{
    try {
        std::vector<uint64_t> student;
        std::vector<uint64_t> professor;
        read_input(student, professor);
        print_output(student, professor);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
