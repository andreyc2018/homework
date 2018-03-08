#include "parserstate.h"
#include "interpreter.h"
#include "parser.h"
#include "logger.h"

bool StartingBlock::handle(Parser* ctx,
                           const std::string& input)
{
    TRACE();
    return false;
}

bool CollectingBlock::handle(Parser* ctx,
                             const std::string& input)
{
    TRACE();
    return false;
}

bool DoneBlock::handle(Parser* ctx,
                       const std::string& input)
{
    TRACE();
    return false;
}
