#pragma once

#include <string>

class Preprocessor
{
    public:
        Preprocessor();

        virtual void parse_input(const std::string& input);
};
