#include "processor.h"
#include "logger.h"
#include "writerfactory.h"
#include "spdlog/fmt/fmt.h"
#include <numeric>
#include <chrono>

using sc = std::chrono::system_clock;
using seconds = std::chrono::seconds;

Processor::Processor(int size, WriterFactoryUPtr&& factory)
    : full_block_size_(size)
    , parser_(*this)
    , writer_factory_(std::move(factory))
    , unique_filename_id_(1)
{
}

Processor::~Processor()
{
    destroy_writers();
}

void Processor::add_token(const std::string& input)
{
    ++counters_.lines;
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
    BlockMessage msg { ss.str(), block_.size() };
    for (const auto& o : writers_) {
        o->update(msg);
    }
    ++counters_.blocks;
    counters_.commands += block_.size();
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

    destroy_writers();

    /** By default system_clock uses nanoseconds as a duration.
     * Most probably it will be enough to distinguish the subsequent file names
     * Using unique_filename_id_ helps to ensure that the file names are unique
     */
    auto secs = sc::now().time_since_epoch().count();
    std::string filename = fmt::format("bulk{}_{}.log", secs, unique_filename_id_);
    ++unique_filename_id_;

    auto file_writer = writer_factory_->create_file_writer(filename);
    auto console_writer = writer_factory_->create_console_writer();

    writers_.push_back(std::make_unique<Reporter>(file_writer));
    writers_.push_back(std::make_unique<Reporter>(console_writer));
}

void Processor::report(std::ostream& out) const
{
    out << "main поток - "
        << counters_.lines << " строк, "
        << counters_.commands << " команд, "
        << counters_.blocks << " блок\n";
}

void Processor::destroy_writers()
{
    writers_.clear();
}
