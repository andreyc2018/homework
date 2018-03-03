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
