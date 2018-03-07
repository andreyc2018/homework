#pragma once

#include "command.h"
#include <vector>
#include <string>

/**
 * @brief The Processor class
 * Reads and process the input commands according to the rules
 * The rules:
 *
 */
class Processor
{
    public:
        explicit Processor(int size);

        void add_token(const std::string& input);
        void run();

    private:
        size_t block_size_;
};
