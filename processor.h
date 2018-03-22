#pragma once

#include "command.h"
#include "parser.h"
#include "asyncqueue.h"
#include "writerfactory.h"
#include <vector>
#include <string>

/**
 * @brief The Processor class
 * Reads and process the input commands according to the rules
 */
class Processor
{
    public:
        using reporters_t = std::vector<Reporter*>;

        explicit Processor(int size,
                           WriterFactoryUPtr&& factory);
        ~Processor();

        virtual void add_token(const std::string& input);
        virtual void end_of_stream();
        virtual void run();
        virtual void add_command(const std::string& input);
        virtual bool block_complete() const;
        virtual void start_block();

    private:
        size_t full_block_size_;
        Parser parser_;
        Block block_;
        reporters_t writers_;
        WriterFactoryUPtr writer_factory_;

        void destroy_writers();
};
