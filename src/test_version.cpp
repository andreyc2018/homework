#include "filesystemops.h"
#include <gtest/gtest.h>
#include <fstream>

class FakeFSOps : public FileSystemOps
{
    public:
        size_t file_size(const std::string&)
        {
            return file_size_;
        }

        size_t file_size_ { 0 };
};

TEST(YAMR, GetSize)
{
    std::ofstream file("test_file");

    std::string content = "hello, world!\n";
    file << content;
    file.close();

    LinuxFSOps fs;

    auto size = fs.file_size("test_file");

    EXPECT_EQ(content.size(), size);

    fs.unlink("test_file");
}

TEST(ERROR, Try_Catch)
{
    LinuxFSOps fs;
    try {
        auto size = fs.file_size("test_file");
        std::cout << size << "\n";
    } catch (const std::system_error& e) {
        std::cout << "Caught a system_error: "
                  << e.code()
                  << " " << e.what() << "\n";
    }
    EXPECT_THROW(fs.file_size("test_file"), std::system_error);
}
