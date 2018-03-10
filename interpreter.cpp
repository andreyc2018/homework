#include "interpreter.h"

bool TerminalExpression::interpret(const std::string& input)
{
    return std::regex_match(input, reg_exp_);
}

bool NonTerminalExpression::interpret(const std::string& input)
{
    return term_left_->interpret(input) ||
            term_right_->interpret(input);
}
