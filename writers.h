#pragma once

#include "observers.h"
#include "singleton.h"

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
