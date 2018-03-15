#include "processor.h"
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
}
