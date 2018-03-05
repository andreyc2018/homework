#pragma once

#include "logger.h"

class Observer
{
    public:
        virtual void update() = 0;
};

class ConsoleOut : public Observer
{
    public:
        void update() override
        {
            TRACE();
        }
};

class FileOut : public Observer
{
    public:
        void update() override
        {
            TRACE();
        }
};

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

using SingleConsole = Singleton<ConsoleOut>;
