#pragma once

#include "asyncqueue.h"
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
        RemoteConsoleWriter(MsgQueue& q) : q_(q) {}

        void write(const std::string& data) override
        {
            q_.push(data);
        }

    private:
        MsgQueue& q_;
};

class RemoteFileWriter : public IWriter
{
    public:
        RemoteFileWriter(MsgQueue& q,
                            const std::string& filename)
            : q_(q)
        {
            q_.push(filename);
        }
        void write(const std::string& data) override
        {
            q_.push(data);
        }
    private:
        MsgQueue& q_;
};

using IWriterUPtr = std::unique_ptr<IWriter>;
