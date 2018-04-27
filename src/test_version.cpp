#include <gtest/gtest.h>
#include "filesystemops.h"

class FakeFS
{
    public:
        size_t file_size(const std::string&)
        {
            return file_size_;
        }

        size_t file_size_ { 0 };
};

using FakeFSOps = FileSystemOps<FakeFS>;

TEST(YAMR, GetSize)
{
    BoostFSOps::file_size("test_version");
}
