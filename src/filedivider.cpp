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
    auto file_size = fs.file_size(filename_);
    auto chunk_size = file_size / n_;
    off_t begin = file_size - chunk_size;
    off_t end = begin + chunk_size;

    if (begin <= 0 && end <= 0) {
        return;
    }

    std::ifstream file(filename_);
}
