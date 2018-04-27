#include "filedivider.h"
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

FileDivider::FileDivider(const std::string& filename, size_t n)
    : filename_(filename)
    , n_(n)
{

}

void FileDivider::create_chunks()
{

}
