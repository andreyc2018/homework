#include "logging_allocator.h"
#include "xray.h"
#include <list>
#include <map>
#include <forward_list>
#include <iostream>

#define LINE(n)  std::cout << "---------- " << n << " ----------\n";

int main(int, char**)
{
//    std::list<int, logging_allocator<int>> l;
//    l.push_back(19);

//    std::map<int, int, std::less<int>, logging_allocator<std::pair<int, int>>> m;
//    m[1] = 10;


    LINE(1);
    {
        std::forward_list<xray, logging_allocator<xray>> l;
        LINE(2);
        l.emplace_front();
        LINE(3);
    }
    LINE(4);

    return 0;
}
