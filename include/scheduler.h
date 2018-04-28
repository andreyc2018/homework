#pragma once

#include <vector>
#include <thread>

class Scheduler
{
    public:
        using mappers_t = std::vector<std::thread>;
        Scheduler();

        void run(const std::string& filename, size_t mnum, size_t rnum);

    private:
        const std::string filename_;
        mappers_t mappers_;
};
