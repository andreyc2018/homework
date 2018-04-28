#pragma once

#include <string>

class Mapper
{
    public:
        Mapper(const std::string& filename, off_t begin, off_t end);

        void run();

    private:
        const std::string filename_;
        off_t begin_;
        off_t end_;
};
