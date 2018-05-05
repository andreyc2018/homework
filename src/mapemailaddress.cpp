#include "mapemailaddress.h"
#include "logger.h"

MapEmailAddress::MapEmailAddress()
    : unique_idx_(0)
{
    gLogger->debug("{}", data_.end());
}

void MapEmailAddress::process_input(const std::string& input)
{
    data_.push_back(input);
}

std::vector<std::string> MapEmailAddress::data()
{
    return data_;
}
