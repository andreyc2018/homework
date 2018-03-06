#pragma once
#include "state.h"
#include "command.h"

class ExpressionContext
{
    public:
        explicit ExpressionContext(int size)
            : block_size_(size)
            , level_(0)
            , state_(std::make_unique<StartingBlock>())
        {}

        int level() const { return level_; }

        bool in_state(const char* name) const {
            return state_->name() == name;
        }

        const std::string& state() const {
            return state_->name();
        }

        bool can_increase_block() const {
            return (block_.size() + 1) < block_size_;
        }

        bool block_full() const {
            return level_ == 0 && block_.size() == block_size_;
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
        enum class Type { StartBlock, Command, EndBlock };

        Expression(const std::string& name) : name_(name) {}
        virtual bool interpret(ExpressionContext& ctx, std::string input) = 0;

        const std::string& name() const { return name_; }
    private:
        const std::string name_;
};

using ExpressionUPtr = std::unique_ptr<Expression>;

class StartBlockExpr: public Expression
{
    public:
        StartBlockExpr() : Expression("StartBlockExpr") {}

        bool interpret(ExpressionContext& ctx, std::string input) override
        {
            if (input == "{" || input != "}") {
                ctx.handle_state(input);
                return true;
            }
            return false;
        }
};

class CommandExpr: public Expression
{
    public:
        CommandExpr() : Expression("CommandExpr") {}

        bool interpret(ExpressionContext& ctx, std::string input) override
        {
            if (input != "{" && input != "}") {
                ctx.handle_state(input);
                return true;
            }
            return false;
        }
};

class EndBlockExpr: public Expression
{
    public:
        EndBlockExpr() : Expression("EndBlockExpr") {}

        bool interpret(ExpressionContext& ctx, std::string input) override
        {
            ctx.handle_state(input);
            return true;
        }
};
