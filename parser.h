#pragma once

#include "interpreter.h"

class ParserState;

class Parser
{
    public:
        Parser();
        ~Parser();

        void handle_token(const std::string& token);

    private:
        StartBlockExpr start_exp_;
        CommandExpr command_exp_;
        EndBlockExpr end_exp_;
        ParserState* state_;
};
