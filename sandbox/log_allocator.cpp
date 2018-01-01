#include "logging_allocator.h"
#include <list>
#include <map>
#include <iostream>

int main(int, char**)
{
//    std::list<int, logging_allocator<int>> l;
//    l.push_back(19);

    std::map<int, int, std::less<int>, logging_allocator<std::pair<int, int>>> m;
    m[1] = 10;

    return 0;
}
