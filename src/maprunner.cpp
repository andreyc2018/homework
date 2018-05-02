#include "maprunner.h"
#include "logger.h"
#include <fstream>

MapRunner::MapRunner(const std::string& filename, off_t begin, off_t end)
    : filename_(filename)
    , begin_(begin)
    , end_(end)
{
    gLogger->debug("{}: Creating MapRunner for file {} and range {} - {}",
                   (void*)this, filename_, begin, end);
}

void MapRunner::run()
{
    gLogger->debug("{}: Running MapRunner on {} reading range {} - {}",
                   (void*)this, filename_, begin_, end_);
    std::ifstream in_file(filename_);
    in_file.seekg(begin_);
    do {
        std::string line;
        std::getline(in_file, line);
        gLogger->debug("{}: {} : {}, {}",
                       (void*)this, line, in_file.tellg(), in_file.eof());
    } while(!in_file.eof() && in_file.tellg() < end_);
}
