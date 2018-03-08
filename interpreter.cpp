#include "interpreter.h"
#include "state.h"
#include "parser.h"
#include "logger.h"

bool StartBlockExpr::interpret(Parser& ctx, std::string input)
{
    TRACE();
    /// Starting with "{"
    if (input == "{") {
        return ctx.handle_state(type(), input);
    }
    /// Starting with "cmdN"
    if (!input.empty() && input != "}")
    {
        return ctx.handle_state(type(), input);
    }
    return false;
}

bool CommandExpr::interpret(Parser& ctx, std::string input)
{
    TRACE();
    if (input != "{" && input != "}") {
        return ctx.handle_state(type(), input);
    }
    return false;
}

bool EndBlockExpr::interpret(Parser& ctx, std::string input)
{
    TRACE();
    return ctx.handle_state(type(), input);
}
