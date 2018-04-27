#include "filedivider.h"
#include "filesystemops.h"
#include <fstream>

FileDivider::FileDivider(const std::string& filename, size_t n)
    : filename_(filename)
    , n_(n)
{

}

void FileDivider::create_chunks()
{
    LinuxFSOps fs;
    auto filesize = fs.file_size(filename_);
    auto size = filesize / n_;
    size_t chunk_size = size;
    std::ifstream file(filename_);

    for (size_t offset = 0; offset <= filesize; offset += chunk_size) {
    }
}
