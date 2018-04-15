#pragma once

#include "async.h"
#include "processor.h"
#include "preprocessor.h"
#include "listeners.h"
#include "logger.h"
#include "singleton.h"
#include <atomic>
#include <map>
#include <memory>

namespace async {
namespace details {

const handle_t InvalidHandle = 0;
constexpr handle_t CommonProcessor = 0;

using processors_t = std::map<handle_t, ProcessorUPtr>;

struct AsyncCounters
{
    unsigned int procesors = 0;
};

class AsyncLibrary
{
    public:
        AsyncLibrary();
        ~AsyncLibrary();

        handle_t open_processor(size_t bulk);
        void process_input(handle_t id,
                           const std::string& data);
        void close_processor(handle_t id);

        void create_processor(handle_t id);
        void process_token(handle_t id,
                           const std::string& token);

        MessageQueue& console_q() { return console_q_; }
        MessageQueue& file_q() { return file_q_; }

        void set_bulk(std::size_t bulk);

    private:
        static std::atomic<handle_t> next_id_;
        processors_t processors_;
        Preprocessor<AsyncLibrary, CommonProcessor> preprocessor_;
        MessageQueue console_q_;
        ConsoleListener console_;
        MessageQueue file_q_;
        FileListener file_1_;
        FileListener file_2_;
        Counters counters_;
        AsyncCounters async_counters_;
        std::size_t bulk_;

        void report(std::ostream& out) const;
};

using Async = Singleton<AsyncLibrary>;
}}
