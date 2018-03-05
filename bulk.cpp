#include "bulk.h"
#include <iostream>
#include <numeric>

Processor::Processor()
    : block_size_(0)
    , input_counter_(0)
    , state_(std::make_unique<Collecting>())
{
}

void Processor::add_token(const std::string& input)
{

}

void Processor::handle(const std::string& input)
{
    InputContext ctx;
    ctx.set_input(input);
    state_->handle(this, ctx);
}

bool Processor::add_command(Context& ctx)
{
    commands_.push_back(dynamic_cast<InputContext&>(ctx).input());
    input_counter_++;
    if (input_counter_ == block_size_) {
        state_ = std::make_unique<Processing>();
        return true;
    }
    return false;
}

void Processor::run()
{
    std::string s = std::accumulate(std::next(commands_.begin()), commands_.end(),
                                        commands_[0], // start with first element
                                        [](std::string a, std::string b) {
                                            return a + ',' + b;
                                        });
    std::cout << "bulk: " << s << "\n";
    commands_.clear();
}

bool Collecting::handle(Processor* proc, Context& ctx)
{
    return proc->add_command(ctx);
}

bool Processing::handle(Processor* proc, Context& ctx)
{
    proc->run();
    return true;
}

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
