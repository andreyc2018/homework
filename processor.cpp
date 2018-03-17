#include "processor.h"
#include "logger.h"
#include <numeric>

Processor::Processor(int size)
    : parser_(size, this)
{
}

void Processor::add_token(const std::string& input)
{
    parser_.handle_token(input);
}

void Processor::run()
{
    TRACE();
}

void Processor::add_command(const std::string& input)
{
    TRACE();
    LOG() << "Adding command " << input << "\n";
}

bool Processor::block_complete() const
{
    return true;
}
