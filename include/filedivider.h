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
            chunk_t(off_t o, size_t s) : offset(o), size(s) {}
            off_t offset;
            size_t size;
        };
        using chunks_t = std::vector<chunk_t>;

        FileDivider(const std::string& filename, size_t n);

        void create_chunks();

    private:
        const std::string filename_;
        size_t n_;
        chunks_t chunks_;
};
