#include "min_allocator.h"
#include <list>
#include <iostream>

int main(int, char**)
{
    std::list<int, minimal_allocator<int>> l;

    l.push_back(19);

    return 0;
}
