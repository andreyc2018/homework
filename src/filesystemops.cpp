#include "filesystemops.h"

#include <boost/filesystem.hpp>

size_t BoostFS::file_size(const std::string& filename)
{
    return boost::filesystem::file_size(filename);
}
