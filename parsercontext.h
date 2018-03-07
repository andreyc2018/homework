#pragma once

#include "state.h"
#include "logger.h"
#include <string>

class ParserContext
{
    public:
        explicit ParserContext(int size);

        int level() const { return level_; }

        bool in_state(const char* name) const {
            return state_->name() == name;
        }

        const std::string& state() const {
            return state_->name();
        }

        size_t block_size() const { return block_.size(); }

        bool block_full() const {
            return level_ == 0 && block_.size() == block_size_;
        }

        void set_state(ContextStateUPtr state) {
            state_.swap(state);
        }

        bool handle_state(Expression::Type type, const std::string& input) {
            TRACE();
            return state_->handle(this, type, input);
        }

        void increase_level() { ++level_; }
        void decrease_level() { --level_; }

        void new_block() {
            block_ = Block::create();
        }

        void add_command(const std::string& name) {
            Command cmd = Command::create(name);
            if (cmd.valid()) {
                block_.add_command(cmd);
            }
        }

    private:
        size_t block_size_;
        int level_;
        Block block_;
        ContextStateUPtr state_;
};
