#pragma once

struct Counters
{
    unsigned int lines = 0;
    unsigned int blocks = 0;
    unsigned int commands = 0;

    void reset()
    {
        lines = blocks = commands = 0;
    }
};
