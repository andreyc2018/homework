#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <fstream>
#include "writers.h"

class Observer
{
    public:
        virtual ~Observer() {}
        virtual void update(const std::string& data) = 0;
};

class ConsoleReporter : public Observer
{
    public:
        void update(const std::string& data) override
        {
            GlobalConsoleWriter::instance().write(data);
        }
};

class FileReporter : public Observer
{
    public:
        FileReporter(const std::string& filename)
            : writer_(filename) {}
        ~FileReporter() {}

        void update(const std::string& data) override
        {
            writer_.write(data);
        }

    private:
        FileWriter writer_;
};
