#pragma once

#include "maprunner.h"
#include <vector>
#include <thread>

class Scheduler
{
    public:
        using mappers_t = std::vector<MapRunnerUPtr>;
        using runners_t = std::vector<std::thread>;
        Scheduler();
        ~Scheduler();

        void run(const std::string& filename, size_t mnum, size_t rnum);

    private:
        const std::string filename_;
        mappers_t mappers_;
        runners_t threads_;
};
