#include "scheduler.h"
#include "filedivider.h"

Scheduler::Scheduler()
{
}

void Scheduler::run(const std::string& filename, size_t mnum, size_t rnum)
{
    FileDivider fd(filename, mnum);
    fd.create_chunks();
    for(auto i = fd.begin(); i != fd.end(); ++i) {
    }
}
