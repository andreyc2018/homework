#include "state.h"
#include "interpreter.h"

bool StartingBlock::handle(ExpressionContext* ctx, Expression::Type type, const std::string&)
{
    if (type == Expression::Type::StartBlock) {
        ctx->new_block();
        ctx->set_state(std::make_unique<CollectingBlock>());
        return true;
    }
    return false;
}

bool CollectingBlock::handle(ExpressionContext* ctx, Expression::Type type, const std::string& input)
{
    if (type == Expression::Type::Command) {
        ctx->add_command(input);
        if (ctx->block_full()) {
            ctx->set_state(std::make_unique<DoneBlock>());
            return true;
        }
    }
    return false;
}

bool DoneBlock::handle(ExpressionContext* ctx, Expression::Type type, const std::string& input) 
{
    return false;
}
