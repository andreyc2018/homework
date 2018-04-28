#include "filesystemops.h"
#include "filedivider.h"
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

TEST(YAMR, Calculate_Chunks)
{
    size_t file_size = 417;
    size_t n = 5;
    size_t chunk_size = file_size / n;

    EXPECT_EQ(83, chunk_size);

    FileDivider::chunks_t chunks;
    for (size_t offset = 0; offset < file_size; offset += chunk_size) {
        if (chunks.size() == n - 1) {
            chunk_size = file_size - offset;
        }
        FileDivider::chunk_t part (offset, chunk_size);
        chunks.push_back(part);
    }

    EXPECT_EQ(n, chunks.size());

    for (const auto& c : chunks) {
        std::cout << "o = " << c.offset
                  << " s = " << c.size << "\n";
    }
}

TEST(YAMR, Adjust_Chunks)
{
    std::string content = "cblagf@mail.com\n"
                          "cjjage@aol.com\n"
                          "ejd@hotmail.com\n"
                          "fiflb@hotmail.com\n"
                          "fka@aol.com\n"
                          "gbf@gmail.com\n"
                          "hdl@gmail.com\n"
                          "ibe@gmail.com\n"
                          "icilalc@gmail.com\n"
                          "jlf@aol.com\n";

    size_t file_size = content.size();
    size_t n = 4;
    size_t chunk_size = file_size / n;

    EXPECT_EQ(37, chunk_size);

    FileDivider::chunks_t chunks;
    for (size_t offset = 0, size = chunk_size; offset < file_size; offset += size, size = chunk_size) {
        for (;content[offset+size-1] != '\n' && size > 0; --size);

        if (chunks.size() == n - 1) {
            size = file_size - offset;
        }
        FileDivider::chunk_t part (offset, size);
        chunks.push_back(part);
    }

    EXPECT_EQ(n, chunks.size());

    for (const auto& c : chunks) {
        std::cout << "o = " << c.offset
                  << " s = " << c.size
                  << "\n:\n" << content.substr(c.offset, c.size)
                  << ":\n";
    }
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
