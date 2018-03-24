#pragma once

#include "async.h"
#include "processor.h"
#include "listeners.h"
#include <map>

namespace async {
namespace details {
class AsyncLibrary
{
    public:
        AsyncLibrary();
        ~AsyncLibrary();

    private:
        std::map<handle_t, Processor> processors;
        MessageQueue console_q;
        ConsoleListener console;
        MessageQueue file_q;
        FileListener file_1;
        FileListener file_2;
};

}}
