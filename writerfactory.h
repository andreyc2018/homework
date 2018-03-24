#pragma once

#include "writers.h"
#include "reporters.h"
#include "messagequeue.h"

class IWriterFactory
{
    public:
        virtual IWriterUPtr create_console_writer() = 0;
        virtual IWriterUPtr create_file_writer(const std::string& filename) = 0;
};

class NonWriterFactory : public IWriterFactory
{
    public:
        IWriterUPtr create_console_writer() override
        {
            return std::make_unique<NonWriter>();
        }
        IWriterUPtr create_file_writer(const std::string&) override
        {
            return std::make_unique<NonWriter>();
        }
};

class LocalWriterFactory : public IWriterFactory
{
    public:
        IWriterUPtr create_console_writer() override
        {
            return std::make_unique<ConsoleWriter>();
        }
        IWriterUPtr create_file_writer(const std::string& filename) override
        {
            return std::make_unique<FileWriter>(filename);
        }
};

class ThreadWriterFactory : public IWriterFactory
{
    public:
        ThreadWriterFactory(MessageQueue& console_q,
                            MessageQueue& file_q)
            : console_queue_(console_q)
            , file_queue_(file_q) {}

        IWriterUPtr create_console_writer() override
        {
            return std::make_unique<RemoteConsoleWriter>(console_queue_);
        }
        IWriterUPtr create_file_writer(const std::string& filename) override
        {
            return std::make_unique<RemoteFileWriter>(file_queue_, filename);
        }

    private:
        MessageQueue& console_queue_;
        MessageQueue& file_queue_;
};

using WriterFactoryUPtr = std::unique_ptr<IWriterFactory>;
