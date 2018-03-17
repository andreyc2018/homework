#pragma once

#include "command.h"
#include "parser.h"
#include "observers.h"
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
        void add_command(const std::string& input);
        bool block_complete() const;
        void start_block();

    private:
        size_t block_size_;
        Parser parser_;
};
