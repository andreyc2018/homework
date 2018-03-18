#include "processor.h"
#include "logger.h"
#include <numeric>

Processor::Processor(int size)
    : full_block_size_(size)
    , parser_(this)
{
}

Processor::~Processor()
{
    for (auto& o : writers_) {
        delete o;
    }
}

void Processor::add_token(const std::string& input)
{
    parser_.handle_token(input);
}

void Processor::run()
{
    std::stringstream ss;
    block_.run(ss);

    for (const auto& o : writers_) {
        o->update(ss.str());
    }
}

void Processor::add_command(const std::string& input)
{
    auto cmd = Command::create(input);
    block_.add_command(cmd);
}

bool Processor::block_complete() const
{
    return block_.size() == full_block_size_;
}

void Processor::start_block()
{
    block_ = Block::create();
}
