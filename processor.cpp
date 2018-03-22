#include "processor.h"
#include "logger.h"
#include "writerfactory.h"
#include <numeric>
#include <chrono>

using sc = std::chrono::system_clock;
using seconds = std::chrono::seconds;

Processor::Processor(int size, WriterFactoryUPtr&& factory)
    : full_block_size_(size)
    , parser_(this)
    , writer_factory_(std::move(factory))
{
}

Processor::~Processor()
{
    destroy_writers();
}

void Processor::add_token(const std::string& input)
{
    parser_.handle_token(input);
}

void Processor::end_of_stream()
{
    parser_.end_of_stream();
}

void Processor::run()
{
    std::stringstream ss;
    block_.run(ss);
    for (const auto& o : writers_) {
        o->update(ss.str());
    }
}

void Processor::add_command(const std::string& input)
{
    auto cmd = Command::create(input);
    block_.add_command(cmd);
}

bool Processor::block_complete() const
{
    return block_.size() == full_block_size_;
}

void Processor::start_block()
{
    block_ = Block::create();
    std::string filename = "bulk";
    auto secs = std::chrono::duration_cast<seconds>(sc::now().time_since_epoch()).count();
    filename.append(std::to_string(secs));
    filename.append(".log");

    destroy_writers();

    auto file_writer = writer_factory_->create_file_writer(filename);
    auto console_writer = writer_factory_->create_console_writer();

    writers_.push_back(new Reporter(file_writer));
    writers_.push_back(new Reporter(console_writer));
}

void Processor::destroy_writers()
{
    while (!writers_.empty()) {
        delete writers_.back();
        writers_.pop_back();
    }
}
