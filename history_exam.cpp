#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename S, typename P>
void read_input(S& student, P& proffesor)
{
    size_t n;
    std::string line;
    std::getline(std::cin, line);
    n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        proffesor.push_back(line);
    }
    n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        student.push_back(line);
    }
}

template<typename S, typename P>
void print_input(const S& student, const P& proffesor)
{
    for (const auto& s : proffesor) {
        std::cout << s << "\n";
    }
    for (const auto& s : student) {
        std::cout << s << "\n";
    }
}

//template<typename S, typename P>
//void print_output(const S& student, const P& proffesor)
//{
//    std::vector<std::string> result;
//    for (const auto& s : spammers) {
//        std::cout << s << "\n";
//    }
//}

int main(int, char const**)
{
    try {
        std::vector<std::string> student;
        std::vector<std::string> proffesor;
        read_input(student, proffesor);
        print_input(student, proffesor);
//        print_output(student, proffesor);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
