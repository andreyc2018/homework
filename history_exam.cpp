#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
void read_input(T& student, T& proffesor)
{
    size_t n;
    std::string line;
    std::getline(std::cin, line);
    n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        proffesor.push_back(line);
    }
    std::getline(std::cin, line);
    n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        student.push_back(line);
    }
}

// template<typename T>
// void print_input(const T& student, const T& proffesor)
// {
//     std::cout << "Proffesor:\n";
//     for (const auto& s : proffesor) {
//         std::cout << s << "\n";
//     }
//     std::cout << "Student:\n";
//     for (const auto& s : student) {
//         std::cout << s << "\n";
//     }
// }

template<typename T>
void print_output(T& student, T& proffesor)
{
    std::sort(student.begin(), student.end());
    std::sort(proffesor.begin(), proffesor.end());
    T intersection;
    std::set_intersection(proffesor.begin(), proffesor.end(),
                          student.begin(), student.end(),
                          std::back_inserter(intersection));
    // std::cout << "Proffesor:\n";
    // for (const auto& s : proffesor) {
    //     std::cout << s << "\n";
    // }
    // std::cout << "Student:\n";
    // for (const auto& s : student) {
    //     std::cout << s << "\n";
    // }
    // std::cout << "Intersection:\n";

    // for (const auto& s : intersection) {
    //     std::cout << s << "\n";
    // }

    size_t count = 0;
    for (const auto& s : intersection) {
        count += std::count(student.begin(), student.end(), s);
    }
    std::cout << count << "\n";
}

int main(int, char const**)
{
    try {
        std::vector<std::string> student;
        std::vector<std::string> proffesor;
        read_input(student, proffesor);
        // print_input(student, proffesor);
        print_output(student, proffesor);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
