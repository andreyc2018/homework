#include "parserstate.h"
#include "interpreter.h"
#include "parser.h"

ParserState::Result StartingBlock::handle(Parser& ctx,
                                          const std::string& input)
{
    if (ctx.open_kw()->interpret(input)) {
        ctx.set_state(std::make_unique<ExpectingDynamicCommand>());
        return Result::Stop;
    }
    if (ctx.command()->interpret(input)) {
        ctx.set_state(std::make_unique<ExpectingStaticCommand>());
        return Result::Continue;
    }
    return Result::Stop;
}

ParserState::Result ExpectingDynamicCommand::handle(Parser& ctx,
                                             const std::string& input)
{
    if (ctx.command()->interpret(input)) {
        ctx.increase_level();
        ctx.start_block();
        ctx.set_state(std::make_unique<CollectingDynamicBlock>());
        return Result::Continue;
    }
    if (ctx.close_kw()->interpret(input)) {
        ctx.set_state(std::make_unique<StartingBlock>());
    }
    return Result::Stop;
}

ParserState::Result ExpectingStaticCommand::handle(Parser& ctx,
                                                   const std::string& input)
{
    if (ctx.command()->interpret(input)) {
        ctx.start_block();
        ctx.set_state(std::make_unique<CollectingStaticBlock>());
        return Result::Continue;
    }
    return Result::Stop;
}

ParserState::Result CollectingDynamicBlock::handle(Parser& ctx,
                                            const std::string& input)
{
    if (ctx.command()->interpret(input)) {
        ctx.add_command(input);
        return Result::Stop;
    }
    if (ctx.open_kw()->interpret(input)) {
        ctx.increase_level();
        return Result::Stop;
    }
    if (ctx.close_kw()->interpret(input)) {
        ctx.decrease_level();
        if (ctx.dynamic_level() == 0) {
            ctx.set_state(std::make_unique<DoneBlock>());
            return Result::Continue;
        }
    }
    return Result::Stop;
}

ParserState::Result CollectingStaticBlock::handle(Parser& ctx,
                                                  const std::string& input)
{
    if (ctx.command()->interpret(input)) {
        ctx.add_command(input);
        if (ctx.block_complete()) {
            ctx.set_state(std::make_unique<DoneBlock>());
            return Result::Continue;
        }
        return Result::Stop;
    }
    if (ctx.open_kw()->interpret(input)) {
        ctx.set_state(std::make_unique<DoneBlock>());
        return Result::Continue;
    }
    return Result::Stop;
}

ParserState::Result CollectingStaticBlock::end_of_stream(Parser& ctx)
{
    ctx.set_state(std::make_unique<DoneBlock>());
    return Result::Continue;
}

ParserState::Result DoneBlock::handle(Parser& ctx,
                                      const std::string& input)
{
    ctx.notify_run();
    ctx.set_state(std::make_unique<StartingBlock>());
    if (ctx.open_kw()->interpret(input)) {
        return Result::Continue;
    }
    return Result::Stop;
}
