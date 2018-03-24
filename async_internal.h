#pragma once

#include "async.h"
#include "processor.h"
#include "listeners.h"
#include "logger.h"
#include <atomic>
#include <map>

namespace async {
namespace details {
class AsyncLibrary
{
    public:
        AsyncLibrary();
        ~AsyncLibrary();

        handle_t add_processor(size_t bulk);
        void process_input(handle_t id,
                           const std::string& token);

        MessageQueue& console_q() { return console_q_; }
        MessageQueue& file_q() { return file_q_; }

    private:
        static std::atomic<handle_t> next_id_;
        std::map<handle_t, ProcessorUPtr> processors_;
        MessageQueue console_q_;
        ConsoleListener console_;
        MessageQueue file_q_;
        FileListener file_1_;
        FileListener file_2_;
};

}}
