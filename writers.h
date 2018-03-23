#pragma once

#include "messagequeue.h"
#include <iostream>
#include <memory>
#include <fstream>

class IWriter
{
    public:
        virtual ~IWriter() {}

        virtual void write(const std::string& data) = 0;
};

class NonWriter : public IWriter
{
    public:
        void write(const std::string&) override {}
};

class ConsoleWriter : public IWriter
{
    public:
        void write(const std::string& data) override
        {
            std::cout << data;
        }
};

class FileWriter : public IWriter
{
    public:
        FileWriter(const std::string& filename)
            : filename_(filename) {}

        void write(const std::string& data) override
        {
            std::ofstream file(filename_);
            file << data;
            file.close();
        }

    private:
        std::string filename_;
};

class RemoteConsoleWriter : public IWriter
{
    public:
        RemoteConsoleWriter(MessageQueue& q) : q_(q) {}

        void write(const std::string& data) override
        {
            Message msg { MessageId::Data, "", data, 0 };
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
        void write(const std::string& data) override
        {
            Message msg { MessageId::Data, filename_, data, 0 };
            q_.push(msg);
        }
    private:
        MessageQueue& q_;
        std::string filename_;
};

using IWriterUPtr = std::unique_ptr<IWriter>;
