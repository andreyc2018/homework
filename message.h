#pragma once

#include <string>

enum class MessageId : int
{
    Data,
    EndOfStream
};

struct Message
{
    MessageId id;
    std::string filename;
    std::string data;
    uint commands;
};
