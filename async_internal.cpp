#include "async_internal.h"

using namespace async;
using namespace async::details;

std::atomic<handle_t> AsyncLibrary::next_id_ { 0 };

AsyncLibrary::AsyncLibrary()
    : console_q_()
    , console_(console_q_)
    , file_q_()
    , file_1_(file_q_, 1)
    , file_2_(file_q_, 2)
{
    gLogger->info("next_id = {}", next_id_);
    next_id_.fetch_add(1, std::memory_order_relaxed);
    gLogger->info("next_id = {}", next_id_);
    console_.run();
    file_1_.run();
    file_2_.run();
}

AsyncLibrary::~AsyncLibrary()
{
    Message msg { MessageId::EndOfStream, "", { "", 0 } };
    console_.queue().push(msg);
    file_1_.queue().push(msg);
    file_2_.queue().push(msg);

    console_.wait();
    file_1_.wait();
    file_2_.wait();

    console_.report(std::cout);
    file_1_.report(std::cout);
    file_2_.report(std::cout);
}

handle_t AsyncLibrary::open_processor(size_t bulk)
{
    gLogger->info("next_id = {}", next_id_);
    handle_t id = next_id_.fetch_add(1, std::memory_order_relaxed);

    gLogger->info("id = {}", id);

    auto p = std::make_unique<Processor>(bulk, std::make_unique<ThreadWriterFactory>(console_q_, file_q_));
    processors_.emplace(id, std::move(p));
    return id;
}

void AsyncLibrary::process_input(handle_t id, const std::string& token)
{
    auto it = processors_.find(id);
    if (it != processors_.end()) {
        processors_[id]->add_string(token);
    }
}

void AsyncLibrary::close_processor(handle_t id)
{
    auto it = processors_.find(id);
    if (it != processors_.end()) {
        processors_[id]->end_of_stream();
        processors_[id]->report(std::cout);
        processors_.erase(it);
    }
}
