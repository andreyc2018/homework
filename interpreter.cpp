#include "interpreter.h"
#include "state.h"
#include "parsercontext.h"
#include "logger.h"

bool StartBlockExpr::interpret(ParserContext& ctx, std::string input)
{
    TRACE();
    if (input == "{" || input != "}") {
        return ctx.handle_state(type(), input);
    }
    return false;
}

bool CommandExpr::interpret(ParserContext& ctx, std::string input)
{
    TRACE();
    if (input != "{" && input != "}") {
        return ctx.handle_state(type(), input);
    }
    return false;
}

bool EndBlockExpr::interpret(ParserContext& ctx, std::string input)
{
    TRACE();
    return ctx.handle_state(type(), input);
}
