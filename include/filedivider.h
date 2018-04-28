#pragma once
#include <string>
#include <vector>

/**
 * @brief Calculates the file parts
 *
 * Take a file name and a number of parts.
 * Calculates the offsets and sizes for each part.
 * Opens a file and adjusts the offsets and sizes
 * to be on an end of a string.
 * A result is an array of the pairs offset and size.
 */
class FileDivider
{
    public:
        struct chunk_t
        {
            chunk_t(off_t b, off_t e) : begin(b), end(e) {}
            off_t begin;
            off_t end;
        };
        using chunks_t = std::vector<chunk_t>;

        FileDivider(const std::string& filename, size_t n);

        void create_chunks();

    private:
        const std::string filename_;
        size_t n_;
        chunks_t chunks_;
};
