#include "logging_allocator.h"
#include "xray.h"
#include "sl_list.h"

#include <list>
#include <map>
#include <forward_list>
#include <iostream>

#define LINE(msg)  std::cout << "\n" << __COUNTER__ << ": --- " << msg << " ---\n\n";

using x_int = xray<int>;

int main(int, char**)
{
    LINE("begin");
    {
        std::forward_list<x_int, logging_allocator<x_int>> l;
        LINE("after list ctor");
        l.emplace_front(99);
        LINE("after emplace 99");
    }
    LINE("before my list");
    {
        single_linked_list<x_int, logging_allocator<x_int>> l;
        LINE("after my list ctor");
        l.emplace_front(17);
        LINE("after emplace 17");
    }
    LINE("end");

    return 0;
}
