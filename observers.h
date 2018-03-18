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

using GlobalConsoleWriter = Singleton<ConsoleWriter>;

class Observer
{
    public:
        virtual ~Observer() {}
        virtual void update(const std::string& data) = 0;
};

class ConsoleOut : public Observer
{
    public:
        void update(const std::string& data) override
        {
            GlobalConsoleWriter::instance().write(data);
        }
};

class FileOut : public Observer
{
    public:
        FileOut(const std::string& filename)
            : writer_(filename) {}
        ~FileOut() {}

        void update(const std::string& data) override
        {
            writer_.write(data);
        }

    private:
        FileWriter writer_;
};
