#include "state.h"
#include "interpreter.h"
#include "parsercontext.h"
#include "logger.h"

bool StartingBlock::handle(ParserContext* ctx,
                           Expression::Type type,
                           const std::string& input)
{
    TRACE();
    if (type == Expression::Type::StartBlock) {
        ctx->new_block();
        if (input == "{") {
            ctx->increase_level();
        }
        ctx->set_state(std::make_unique<CollectingBlock>());
        return true;
    }
    return false;
}

bool CollectingBlock::handle(ParserContext* ctx, Expression::Type type, const std::string& input)
{
    TRACE();
    if (type == Expression::Type::Command) {
        ctx->add_command(input);
        if (ctx->block_full()) {
            ctx->set_state(std::make_unique<DoneBlock>());
            return true;
        }
    }
    else if (type == Expression::Type::EndBlock) {
        ctx->decrease_level();
        ctx->add_command(input);
        ctx->set_state(std::make_unique<DoneBlock>());
        return true;
    }
    return false;
}

bool DoneBlock::handle(ParserContext* ctx, Expression::Type type, const std::string& input) 
{
    TRACE();
    return false;
}
