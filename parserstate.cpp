#include "parserstate.h"
#include "interpreter.h"
#include "parser.h"
#include "logger.h"

ParserState::Result StartingBlock::handle(Parser* ctx, const std::string& input)
{
    TRACE();
    if (ctx->open_kw()->interpret(input)) {
        ctx->enable_dynamic_block();
        ctx->set_state(ParserState::create<ExpectingCommand>());
        return Result::Stop;
    }
    if (ctx->command()->interpret(input)) {
        ctx->set_state(ParserState::create<CollectingBlock>());
        return Result::Continue;
    }
    return Result::Stop;
}

ParserState::Result ExpectingCommand::handle(Parser* ctx, const std::string& input)
{
    TRACE();
    if (ctx->command()->interpret(input)) {
        ctx->set_state(ParserState::create<CollectingBlock>());
        return Result::Continue;
    }
    if (ctx->close_kw()->interpret(input)) {
        ctx->disable_dynamic_block();
        ctx->set_state(ParserState::create<StartingBlock>());
    }
    return Result::Stop;
}

ParserState::Result CollectingBlock::handle(Parser* ctx,
                                            const std::string& input)
{
    TRACE();
    if (ctx->command()->interpret(input)) {
        ctx->add_command(input);
        if (ctx->block_complete()) {
            ctx->set_state(ParserState::create<DoneBlock>());
            return Result::Continue;
        }
    }
    else if (ctx->dynamic_block() && ctx->close_kw()->interpret(input)) {
        ctx->set_state(ParserState::create<DoneBlock>());
        return Result::Continue;
    }
    else if (!ctx->dynamic_block() && ctx->open_kw()->interpret(input)) {
        ctx->set_state(ParserState::create<DoneBlock>());
        return Result::Continue;
    }
    return Result::Stop;
}

ParserState::Result DoneBlock::handle(Parser* ctx, const std::string&)
{
    TRACE();
    ctx->notify_run();
    ctx->start_block();
    ctx->set_state(ParserState::create<StartingBlock>());
    return Result::Stop;
}
