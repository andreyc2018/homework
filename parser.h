#pragma once

#include "interpreter.h"

class ParserState;
class Processor;

class Parser
{
    public:
        Parser(int size, Processor* processor);
        ~Parser();

        void handle_token(const std::string& token);

        const expr_t& open_block() const { return open_block_; }
        const expr_t& close_block() const { return close_block_; }
        const expr_t& command() const { return command_; }
        const expr_t& start_block() const { return start_block_; }
        const expr_t& end_block() const { return end_block_; }

        void set_state(ParserState* state);
        ParserState* state() const { return state_; }

        void add_command(const std::string& token);
        bool block_complete() const;
        void increase_level() { level_ ++; }
        void decrease_level() { level_ --; }
        void notify_run();

    private:
        size_t block_size_;
        int level_;
        ParserState* state_;
        Processor* processor_;

        const expr_t open_block_;
        const expr_t close_block_;
        const expr_t command_;
        const expr_t start_block_;
        const expr_t end_block_;
};
