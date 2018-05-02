#include "mapper.h"
#include "logger.h"
#include <iostream>

Mapper::Mapper(const std::string& filename, off_t begin, off_t end)
    : filename_(filename)
    , begin_(begin)
    , end_(end)
{
    gLogger->debug("{}: Creating mapper for file {} and range {} - {}",
                   (void*)this, filename_, begin, end);
}

void Mapper::run()
{
    gLogger->debug("{}: Running mapper on {} reading range {} - {}",
                   (void*)this, filename_, begin_, end_);
    std::cout << "file: " << filename_ << '\n';
}
