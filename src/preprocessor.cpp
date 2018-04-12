#include "preprocessor.h"
#include <regex>
#include <iostream>

namespace {
std::regex eol_re("\n");

void parse_block(std::sregex_token_iterator& it);
}

Preprocessor::Preprocessor()
{

}

void Preprocessor::parse_input(const std::string& input)
{
    for (auto it = std::sregex_token_iterator(input.begin(), input.end(), eol_re, -1);
         it != std::sregex_token_iterator(); ++it) {
        const auto& token = *it;
        std::cout << "*it = " << token << "\n";
        if (token == "{") {
            parse_block(it);
        }
        else {
            std::cout << "token = " << token << "\n";
        }
    }
}

namespace {
void parse_block(std::sregex_token_iterator& it)
{
    int level = 1;
    for (++it; it != std::sregex_token_iterator(); ++it) {
        const auto& token = *it;
        std::cout << "block:*it = " << token
                  << " level = " << level << "\n";
        if (token == "{") {
            ++level;
            continue;
        }
        if (token == "}") {
            --level;
            if (level == 0) {
                break;
            }
            continue;
        }
        std::cout << "block:token = " << token << "\n";
    }
}
}
