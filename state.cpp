#include "state.h"
#include "interpreter.h"

bool StartingBlock::handle(ExpressionContext* ctx, const std::string&)
{
    ctx->new_block();
    ctx->set_state(std::make_unique<CollectingBlock>());
    return true;
}

bool CollectingBlock::handle(ExpressionContext* ctx, const std::string& input)
{
    ctx->add_command(input);
    return false;
}

bool DoneBlock::handle(ExpressionContext* ctx, const std::string& input) 
{
    return false;
}
