#include "parserstate.h"
#include "interpreter.h"
#include "parser.h"
#include "logger.h"

bool StartingBlock::handle(Parser* ctx,
                           const std::string& input)
{
    TRACE();
    if (ctx->open_block()->interpret(input)) {
        ctx->increase_level();
        ctx->set_state(ParserState::create<CollectingBlock>());
    }
    else if (ctx->command()->interpret(input)) {
        ctx->add_command(input);
        if (ctx->block_complete()) {
            ctx->notify_run();
        }
        else {
            ctx->set_state(ParserState::create<CollectingBlock>());
        }
    }
    return false;
}

bool CollectingBlock::handle(Parser* ctx,
                             const std::string& input)
{
    TRACE();
    if (ctx->command()->interpret(input)) {
        ctx->add_command(input);
        if (ctx->block_complete()) {
            ctx->notify_run();
        }
    }
    else if (ctx->end_block()->interpret(input)) {
        ctx->notify_run();
        ctx->set_state(ParserState::create<StartingBlock>());
    }
    return false;
}

bool DoneBlock::handle(Parser* ctx,
                       const std::string& input)
{
    TRACE();
    return false;
}
