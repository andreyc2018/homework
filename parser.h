#pragma once

#include "interpreter.h"

class ParserState;
class Processor;

class Parser
{
    public:
        Parser(int size, Processor* processor);
        ~Parser();

        void handle_token(const std::string& token);

    private:
        size_t block_size_;
        ParserState* state_;
        Processor* processor_;
};
