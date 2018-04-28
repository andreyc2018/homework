#include "filesystemops.h"
#include "filedivider.h"
#include <gtest/gtest.h>
#include <fstream>

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

TEST(YAMR, Adjust_Chunks)
{
    std::string content = "first@mail.com\n"

                          "second@aol.com\n"
                          "third@hotmail.com\n"
                          "fourth@hotmail.com\n"

                          "fith@aol.com\n"
                          "sixth@gmail.com\n"
                          "seventh@gmail.com\n"

                          "eighth@gmail.com\n"
                          "ninth@gmail.com\n"
                          "tenth@aol.com\n";

    ssize_t file_size = content.size();
    std::cout << "file_size = " << file_size << "\n";
    EXPECT_EQ(161, file_size);

    size_t n = 4;
    size_t chunk_size = file_size / n;

    EXPECT_EQ(40, chunk_size);

    FileDivider::chunks_t chunks;
    off_t begin = file_size-chunk_size;
    off_t end = begin+chunk_size;
    EXPECT_GE(begin, 0);
    EXPECT_GE(end, 0);

    do {
        std::cout << "b: begin = " << begin << " end = " << end
                  << " e-b = " << end - begin
                  << "\nsubstr = \n"
                  << content.substr(begin, end-begin);

        while (begin > 0 && end > 0 &&
               (content[begin-1] != '\n' || content[end-1] != '\n'))
        {
            if (content[begin-1] != '\n' && begin > 1) {
                --begin;
                ++end;
            }
            if (end != file_size && content[end-1] != '\n' && end > 1) {
                --end;
            }
        }

        std::cout << "\na: begin = " << begin << " end = " << end
                  << " e-b = " << end - begin
                  << "\nsubstr = \n"
                  << content.substr(begin, end-begin);

        FileDivider::chunk_t part (begin, end);
        chunks.push_back(part);

        end = begin;
        begin -= (chunk_size+1);
        if (begin < 0) {
            begin = 0;
        }

    } while (begin >= 0 && end > 0);

    EXPECT_EQ(n, chunks.size());

    for (const auto& c : chunks) {
        std::cout << "b = " << c.begin
                  << " e = " << c.end
                  << "\n:\n" << content.substr(c.begin, c.end-c.begin)
                  << ":\n";
    }
}

TEST(YAMR, Adjust_Chunks_File)
{
    std::string content = "first@mail.com\n"

                          "second@aol.com\n"
                          "third@hotmail.com\n"
                          "fourth@hotmail.com\n"

                          "fith@aol.com\n"
                          "sixth@gmail.com\n"
                          "seventh@gmail.com\n"

                          "eighth@gmail.com\n"
                          "ninth@gmail.com\n"
                          "tenth@aol.com\n";

    std::ofstream test_file("test_file");
    test_file << content;
    test_file.close();

    LinuxFSOps fs;

    ssize_t file_size = fs.file_size("test_file");

    std::cout << "file_size = " << file_size << "\n";
    EXPECT_EQ(161, file_size);

    size_t n = 4;
    size_t chunk_size = file_size / n;

    EXPECT_EQ(40, chunk_size);

    FileDivider::chunks_t chunks;
    off_t begin = file_size-chunk_size;
    off_t end = begin+chunk_size;
    EXPECT_GE(begin, 0);
    EXPECT_GE(end, 0);

#if 0
    std::ifstream file("test_file");

    do {
        while (begin > 0 && end > 0 &&
               (content[begin-1] != '\n' || content[end-1] != '\n'))
        {
            if (content[begin-1] != '\n' && begin > 1) {
                --begin;
                ++end;
            }
            if (end != file_size && content[end-1] != '\n' && end > 1) {
                --end;
            }
        }

        FileDivider::chunk_t part (begin, end);
        chunks.push_back(part);

        end = begin;
        begin -= (chunk_size+1);
        if (begin < 0) {
            begin = 0;
        }

    } while (begin >= 0 && end > 0);

    EXPECT_EQ(n, chunks.size());

    for (const auto& c : chunks) {
        std::cout << "b = " << c.begin
                  << " e = " << c.end
                  << "\n:\n" << content.substr(c.begin, c.end-c.begin)
                  << ":\n";
    }
#endif
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
