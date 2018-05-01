#include "scheduler.h"
#include "filedivider.h"
#include "logger.h"
#include <algorithm>

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
    std::for_each(threads_.begin(), threads_.end(),
                  [](std::thread& t) { t.join(); });
}

void Scheduler::run(const std::string& filename, size_t mnum, size_t rnum)
{
    FileDivider fd(filename, mnum);
    fd.create_chunks();
    for(auto i = fd.begin(); i != fd.end(); ++i) {
        mappers_.emplace_back(filename, i->begin, i->end);
        gLogger->debug("Mapper {}, filename {}, range {} - {}",
                       (void*)&mappers_.back(), mappers_.back().filename(),
                       mappers_.back().begin(), mappers_.back().end());
        threads_.emplace_back(&Mapper::run, &mappers_.back());
    }
}
