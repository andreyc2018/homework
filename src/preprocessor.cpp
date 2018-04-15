#include "preprocessor.h"
#include "async_internal.h"
#include <regex>
#include <iostream>

namespace {
std::regex eol_re("\n");

void parse_block(std::sregex_token_iterator& it,
                 async::handle_t handle,
                 async::details::AsyncLibrary& library);
}

Preprocessor::Preprocessor()
{

}

void Preprocessor::parse_input(const std::string& data,
                               async::handle_t handle,
                               async::details::AsyncLibrary& library)
{
    for (auto it = std::sregex_token_iterator(data.begin(), data.end(), eol_re, -1);
         it != std::sregex_token_iterator(); ++it) {
        const auto& token = *it;
        if (token == "{") {
            library.create_processor(handle);
            library.process_token(handle, token);
            parse_block(it, handle, library);
        }
        else {
            library.process_token(async::details::CommonProcessor, token);
        }
    }
}

namespace {
void parse_block(std::sregex_token_iterator& it,
                 async::handle_t handle,
                 async::details::AsyncLibrary& library)
{
    int level = 1;
    for (++it; it != std::sregex_token_iterator(); ++it) {
        const auto& token = *it;
        library.process_token(handle, token);
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
    }
}
}
