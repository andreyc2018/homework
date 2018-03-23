#pragma once

#include "messagequeue.h"
#include <iostream>
#include <memory>
#include <fstream>

class IWriter
{
    public:
        virtual ~IWriter() {}

        virtual void write(const BlockMessage& data) = 0;
};

class NonWriter : public IWriter
{
    public:
        void write(const BlockMessage&) override {}
};

class ConsoleWriter : public IWriter
{
    public:
        void write(const BlockMessage& data) override
        {
            std::cout << data.data;
        }
};

class FileWriter : public IWriter
{
    public:
        FileWriter(const std::string& filename)
            : filename_(filename) {}

        void write(const BlockMessage& data) override
        {
            std::ofstream file(filename_);
            file << data.data;
            file.close();
        }

    private:
        std::string filename_;
};

class RemoteConsoleWriter : public IWriter
{
    public:
        RemoteConsoleWriter(MessageQueue& q) : q_(q) {}

        void write(const BlockMessage& data) override
        {
            Message msg { MessageId::Data, "", data };
            q_.push(msg);
        }

    private:
        MessageQueue& q_;
};

class RemoteFileWriter : public IWriter
{
    public:
        RemoteFileWriter(MessageQueue& q,
                         const std::string& filename)
            : q_(q), filename_(filename)
        {
        }
        void write(const BlockMessage& data) override
        {
            Message msg { MessageId::Data, filename_, data };
            q_.push(msg);
        }
    private:
        MessageQueue& q_;
        std::string filename_;
};

using IWriterUPtr = std::unique_ptr<IWriter>;
