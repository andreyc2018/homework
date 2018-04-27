#pragma once

#include <string>

template<typename Impl>
class FileSystemOps : public Impl
{
    public:
        static size_t file_size(const std::string& filename)
        {
            return Impl::file_size(filename);
        }
};

class BoostFS
{
    public:
        size_t file_size(const std::string& filename);
};

using BoostFSOps = FileSystemOps<BoostFS>;
