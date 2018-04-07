#pragma once

#include "async.h"
#include "processor.h"
#include "listeners.h"
#include "logger.h"
#include <atomic>
#include <map>
#include <memory>

namespace async {
namespace details {
class AsyncLibrary
{
    public:
        AsyncLibrary();
        ~AsyncLibrary();

        handle_t open_processor(size_t bulk);
        void process_input(handle_t id,
                           const std::string& token);
        void close_processor(handle_t id);

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

using AsyncLibraryUPtr = std::unique_ptr<AsyncLibrary>;

}}
