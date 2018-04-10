#pragma once

#include <string>

enum class MessageId : int
{
    Data,
    EndOfStream
};

struct BlockMessage
{
    std::string data;
    size_t commands;
};

struct Message
{
    MessageId id;
    std::string filename;
    BlockMessage block;
};
