#include "async_internal.h"

using namespace async;
using namespace async::details;

std::atomic<handle_t> AsyncLibrary::next_id_ { (handle_t)1 };

AsyncLibrary::AsyncLibrary()
    : console_q_()
    , console_(console_q_)
    , file_q_()
    , file_1_(file_q_, 1)
    , file_2_(file_q_, 2)
    , bulk_(0)
{
    console_.run();
    file_1_.run();
    file_2_.run();
}

AsyncLibrary::~AsyncLibrary()
{
    close_processor(CommonProcessor);

    Message msg { MessageId::EndOfStream, "", { "", 0 } };
    console_.queue().push(msg);
    file_1_.queue().push(msg);
    file_2_.queue().push(msg);

    console_.wait();
    file_1_.wait();
    file_2_.wait();

    report(std::cout);
    console_.report(std::cout);
    file_1_.report(std::cout);
    file_2_.report(std::cout);
}

handle_t AsyncLibrary::open_processor(size_t bulk)
{
    if (bulk_ == 0 && processors_.empty()) {
        bulk_ = bulk;
        auto p = std::make_unique<Processor>(bulk,
                                             std::make_unique<ThreadWriterFactory>(console_q_,
                                                                                   file_q_));
        processors_.emplace(CommonProcessor, std::move(p));
    }
    handle_t id = next_id_.fetch_add(1, std::memory_order_relaxed);

//    auto p = std::make_unique<Processor>(bulk,
//                                         std::make_unique<ThreadWriterFactory>(console_q_,
//                                                                               file_q_));
    ProcessorUPtr p;
    processors_.emplace(id, std::move(p));
    ++async_counters_.procesors;
    return id;
}

void AsyncLibrary::process_input(handle_t id, const std::string& token)
{
    preprocessor_.parse_input(token);
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
        processors_[id]->report(counters_);
//        processors_[id]->report(std::cout);
        processors_.erase(it);
    }
}

void AsyncLibrary::set_bulk(std::size_t bulk)
{
    bulk_ = bulk;
}

void AsyncLibrary::report(std::ostream& out) const
{
    //    out << "processors - " << async_counters_.procesors << "\n";
    out << "main поток - "
        << counters_.lines << " строк, "
        << counters_.commands << " команд, "
        << counters_.blocks << " блок\n";
}
