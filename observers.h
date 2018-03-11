#pragma once

#include "logger.h"
#include <memory>
#include <mutex>
#include <fstream>

template <typename T>
class Singleton
{
    public:
        typedef T  type;

        static type& instance()
        {
            static type the_instance;
            return the_instance;
        }

    private:
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) = delete;
};

class AbstractWriter
{
    public:
        virtual ~AbstractWriter() {}

        virtual void write(const std::string& data) = 0;
};

class ConsoleWriter : public AbstractWriter
{
    public:
        void write(const std::string& data) override
        {
            std::lock_guard<std::mutex> g(m_);
            std::cout << data;
        }

    private:
        std::mutex m_;
};

class FileWriter : public AbstractWriter
{
    public:
        FileWriter(const std::string& filename)
            : file_(filename) {}

        ~FileWriter() {
            file_.close();
        }

        void write(const std::string& data) override
        {
            file_ << data;
        }

    private:
        std::ofstream file_;
};

using GlobalConsoleWriter = Singleton<ConsoleWriter>;

class Observer
{
    public:
        Observer(AbstractWriter& writer) : writer_(writer) {}
        void update(const std::string& data)
        {
            writer_.write(data);
        }

    private:
        AbstractWriter writer_;
};

using ConsoleOut = Observer<ConsoleWriter>;
using FileOut = Observer<FileWriter>;
