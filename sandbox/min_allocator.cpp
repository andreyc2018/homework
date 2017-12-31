#include "minimal_allocator.h"
#include <vector>
#include <list>
#include <iostream>

int main(int, char**)
{
    std::vector<int, minimal_allocator<int>> v;
    v.push_back(19);

    for (const auto& i : v)
        std::cout << i << "\n";

    std::list<int, minimal_allocator<int>> l;
    l.push_back(14);

    for (const auto& i : l)
        std::cout << i << "\n";

    return 0;
}
