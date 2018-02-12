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
        professor.push_back(line);
    }
    std::getline(std::cin, line);
    n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        student.push_back(line);
    }
}

// template<typename T>
// void print_input(const T& student, const T& professor)
// {
//     std::cout << "professor:\n";
//     for (const auto& s : professor) {
//         std::cout << s << "\n";
//     }
//     std::cout << "Student:\n";
//     for (const auto& s : student) {
//         std::cout << s << "\n";
//     }
// }

template<class InputIt, class T>
typename std::iterator_traits<InputIt>::difference_type
    count_until(InputIt first, InputIt last, const T& value)
{
    typename std::iterator_traits<InputIt>::difference_type ret = 0;
    std::cout << "enter: " << *first << " : " << *(last-1) << "\n";
    for (; first != last && *first <= value; ++first) {
        if (*first == value) {
            ret++;
        }
    }
    std::cout << "exit: " << *first << " : " << *(last-1) << "\n";

    return ret;
}

template<typename T>
void print_output(T& student, T& professor)
{
    std::sort(student.begin(), student.end());
    // std::sort(professor.begin(), professor.end());
    // T intersection;
    // std::set_difference(student.begin(), student.end(),
    //                       professor.begin(), professor.end(),
    //                       std::back_inserter(intersection));
    std::cout << "professor:\n";
    for (const auto& s : professor) {
        std::cout << s << "\n";
    }
    std::cout << "Student:\n";
    for (const auto& s : student) {
        std::cout << s << "\n";
    }
    std::cout << "Intersection:\n";

    // for (const auto& s : intersection) {
    //     std::cout << s << "\n";
    // }

    size_t count = 0;
    for (const auto& s : professor) {
        count += count_until(student.begin(), student.end(), s);
    }
    std::cout << count << "\n";
}

int main(int, char const**)
{
    try {
        std::vector<std::string> student;
        std::vector<std::string> professor;
        read_input(student, professor);
        // print_input(student, professor);
        print_output(student, professor);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
