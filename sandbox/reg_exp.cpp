#include <regex>
#include <iostream>
#include <map>
#include <stdexcept>

//std::regex::flag_type string_to_type(const std::string& type)
//{
//    static
//    std::map<const std::string, std::regex::flag_type> regex_types {
//        { "ecmascript", std::regex::ECMAScript },
//        { "basic", std::regex::basic },
//        { "extended", std::regex::extended },
//        { "awk", std::regex::awk },
//        { "grep", std::regex::grep },
//        { "egrep", std::regex::egrep }
//    };

//    auto it = regex_types.find(type);
//    if (it == regex_types.end()) {
//        std::string what { "unknown regex type: " };
//        what.append(type);
//        throw std::invalid_argument(what);
//    }
//    return it->second;
//}

int main(int argc, char** argv)
{
    try {
        std::string reg_exp = (argc > 1)? argv[1] : ".*";
        std::string search = (argc > 2)? argv[2] : "hello";
//        std::string type_str = (argc > 3)? argv[3] : "extended";
        std::cout << "Regexp: " << reg_exp
                  << " search: " << search
                  << '\n';
//                  << " type: " << type_str;
//        std::regex::flag_type type = string_to_type(type_str);
//        std::cout << " " << type << '\n';
        std::regex re(reg_exp);
        std::cout << std::boolalpha << std::regex_match(search, re) << '\n';
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

