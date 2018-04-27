#pragma once

#include <string>

class FileSystemOps
{
    public:
        virtual size_t file_size(const std::string& filename) = 0;
        virtual void unlink(const std::string& filename) = 0;
};

class LinuxFSOps : public FileSystemOps
{
    public:
        size_t file_size(const std::string& filename) override;
        void unlink(const std::string& filename) override;
};
