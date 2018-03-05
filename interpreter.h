#pragma once
#include "state.h"
#include "command.h"

class ExpressionContext
{
    public:
        explicit ExpressionContext(int size)
            : block_size_(size)
            , level_(0)
            , state_(std::make_unique<Initial>())
        {}

        int level() const { return level_; }

        bool in_state(const char* name) const {
            return state_->name() == name;
        }

        bool can_increase_block() const {
            return (block_.size() + 1) < block_size_;
        }

        void set_state(ContextStateUPtr state) {
            state_.swap(state);
        }

        bool handle_state(const std::string& input) {
            return state_->handle(this, input);
        }

        void new_block() {
            block_ = Block::create();
        }

        void add_command(const std::string& name) {
            Command cmd = Command::create(name);
            block_.add_command(cmd);
        }

    private:
        size_t block_size_;
        int level_;
        Block block_;
        ContextStateUPtr state_;
};

/**
 * @brief The expression tree
 * @details
 *  Expression: StartBlock | Command | EndBlock
 *  StartBlock: "{" | Command
 *  Command: "[a-z]+"
 *  EndBlock: "}" | Command | "{"
 */

class Expression
{
    public:
        virtual bool interpret(ExpressionContext& ctx, std::string input) = 0;
};

class StartBlockExpr: public Expression
{
    public:
        bool interpret(ExpressionContext& ctx, std::string input) override
        {
            if (input == "{" && ctx.level() == 0) {
                ctx.handle_state(input);
                return true;
            }
            if (input == "{" || input == "}")
                return false;
            if (ctx.in_state("initial")) {
                ctx.handle_state(input);
                return true;
            }
            return false;
        }
};

class CommandExpr: public Expression
{
    public:
        bool interpret(ExpressionContext&, std::string input) override
        {
            if (input == "{" || input == "}")
                return false;
            return true;
        }
};

class EndBlockExpr: public Expression
{
    public:
        bool interpret(ExpressionContext& ctx, std::string input) override
        {
            if (input == "}" && ctx.level() == 1)
                return true;
            if (input == "{" && ctx.level() == 0)
                return true;
            if (!ctx.can_increase_block())
                return true;
            return false;
        }
};
