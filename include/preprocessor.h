#pragma once

#include "async.h"
#include <regex>
#include <string>
#include <iostream>

template<typename L, async::handle_t common_id>
class Preprocessor
{
    public:
        Preprocessor() : eol_re("\n") {}

        virtual void parse_input(const std::string& data,
                                 async::handle_t handle, L& library)
        {
            std::cout << "preproc: " << (void*)this << "\n";
            for (auto& i : data) {
                if (i != '{') {
                }
            }
            for (auto it = std::sregex_token_iterator(data.begin(), data.end(), eol_re, -1);
                 it != std::sregex_token_iterator(); ++it) {
                const auto& token = *it;
                std::cout << "*it = " << token << "\n";
                if (token == "{") {
                    library.create_processor(handle);
                    library.process_token(handle, token);
                    parse_block(it, handle, library);
                }
                else {
                    library.process_token(common_id, token);
                    std::cout << "token = " << token << "\n";
                }
            }
        }

    private:
        std::regex eol_re;

        void parse_block(std::sregex_token_iterator& it,
                         async::handle_t handle, L& library)
        {
            int level = 1;
            for (++it; it != std::sregex_token_iterator(); ++it) {
                const auto& token = *it;
                library.process_token(handle, token);

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
};
