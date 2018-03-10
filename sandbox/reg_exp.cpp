#include <regex>
#include <iostream>

int main(int, char**)
{
    try {
        std::regex re("[^{}]+", std::regex::extended);
        std::cout << std::boolalpha << std::regex_match("he", re) << '\n';
    } 
    catch (const std::regex_error& e) {
        std::cout << "regex_error caught: " << e.what() << " code " << e.code() << '\n';
        if (e.code() == std::regex_constants::error_paren) {
            std::cout << "The code was error_paren\n";
        }
        if (e.code() == std::regex_constants::error_brace) {
            std::cout << "The code was error_brace\n";
        }
        if (e.code() == std::regex_constants::error_brack) {
            std::cout << "The code was error_brack\n";
        }
    }
}

