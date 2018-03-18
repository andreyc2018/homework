#include "parserstate.h"
#include "interpreter.h"
#include "parser.h"
#include "logger.h"

ParserState::Result StartingBlock::handle(Parser* ctx,
                                          const std::string& input)
{
    TRACE();
    if (ctx->open_kw()->interpret(input)) {
        ctx->set_state(ParserState::create<ExpectingDynamicCommand>());
        return Result::Stop;
    }
    if (ctx->command()->interpret(input)) {
        ctx->set_state(ParserState::create<ExpectingStaticCommand>());
        return Result::Continue;
    }
    return Result::Stop;
}

ParserState::Result ExpectingDynamicCommand::handle(Parser* ctx,
                                             const std::string& input)
{
    TRACE();
    if (ctx->command()->interpret(input)) {
        ctx->increase_level();
        ctx->start_block();
        ctx->set_state(ParserState::create<CollectingDynamicBlock>());
        return Result::Continue;
    }
    if (ctx->close_kw()->interpret(input)) {
        ctx->set_state(ParserState::create<StartingBlock>());
    }
    return Result::Stop;
}

ParserState::Result ExpectingStaticCommand::handle(Parser* ctx,
                                                   const std::string& input)
{
    TRACE();
    if (ctx->command()->interpret(input)) {
        ctx->start_block();
        ctx->set_state(ParserState::create<CollectingStaticBlock>());
        return Result::Continue;
    }
    return Result::Stop;
}

ParserState::Result CollectingDynamicBlock::handle(Parser* ctx,
                                            const std::string& input)
{
    TRACE();
    if (ctx->command()->interpret(input)) {
        ctx->add_command(input);
        return Result::Stop;
    }
    if (ctx->open_kw()->interpret(input)) {
        ctx->increase_level();
        return Result::Stop;
    }
    if (ctx->close_kw()->interpret(input)) {
        ctx->decrease_level();
        if (ctx->dynamic_level() == 0) {
            ctx->set_state(ParserState::create<DoneBlock>());
            return Result::Continue;
        }
    }
    return Result::Stop;
}

ParserState::Result CollectingStaticBlock::handle(Parser* ctx,
                                                  const std::string& input)
{
    TRACE();
    if (ctx->command()->interpret(input)) {
        ctx->add_command(input);
        if (ctx->block_complete()) {
            ctx->set_state(ParserState::create<DoneBlock>());
            return Result::Continue;
        }
        return Result::Stop;
    }
    if (ctx->open_kw()->interpret(input)) {
        ctx->set_state(ParserState::create<DoneBlock>());
        return Result::Continue;
    }
    return Result::Stop;
}

ParserState::Result CollectingStaticBlock::end_of_stream(Parser* ctx)
{
    ctx->set_state(ParserState::create<DoneBlock>());
    return Result::Continue;
}

ParserState::Result DoneBlock::handle(Parser* ctx,
                                      const std::string& input)
{
    TRACE();
    ctx->notify_run();
    ctx->set_state(ParserState::create<StartingBlock>());
    if (ctx->open_kw()->interpret(input)) {
        return Result::Continue;
    }
    return Result::Stop;
}
