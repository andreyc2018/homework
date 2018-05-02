#pragma once

#include <string>
#include <memory>

class MapRunner
{
    public:
        MapRunner(const std::string& filename, off_t begin, off_t end);

        void run();

        const std::string& filename() const { return filename_; }
        off_t begin() const { return begin_; }
        off_t end() const { return end_; }

    private:
        const std::string filename_;
        const off_t begin_;
        const off_t end_;
};

using MapRunnerUPtr = std::unique_ptr<MapRunner>;
