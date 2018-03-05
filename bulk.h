#pragma once

#include "observers.h"
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

class Command
{
    public:
        explicit Command(const std::string& name) : name_(name) {}

        static Command create(const std::string& name) {
            return Command(name);
        }

        virtual void run(std::iostream& out) {
            out << name_;
        }

        std::string name() const { return name_; }

    protected:
        std::string name_;
};

class Block : public Command
{
    public:
        using block_t = std::vector<Command>;

        static Block create() {
            return Block();
        }

        Block() : Command ("bulk") {}

        void run(std::iostream& out) override {
            out << name_ << ": ";
            for (size_t i = 0; i < commands_.size(); ++i) {
                if (i != 0) {
                    out << ", ";
                }
                commands_[i].run(out);
            }
            out << "\n";
        }

        void add_command(Command& cmd) {
            commands_.push_back(cmd);
        }

        size_t size() const { return commands_.size(); }

    private:
        block_t commands_;
};

using BlockUPtr = std::unique_ptr<Block>;

class ExpressionContext;

class ContextState
{
    public:
        ContextState(const char* name) : name_(name) {}
        ~ContextState() { std::cout << "dtor: " << name_ << "\n"; }

        const char* name() const { return name_; }
        virtual bool handle(ExpressionContext* ctx, const std::string& input) = 0;

//        virtual BlockUPtr create_block(ExpressionContext*) = 0;

    protected:
        const char* const name_;
};

using ContextStateUPtr = std::unique_ptr<ContextState>;

class Initial : public ContextState
{
    public:
        Initial() : ContextState("initial") {}

        bool handle(ExpressionContext*, const std::string&) override {
            return false;
        }
};

class StartingBlock : public ContextState
{
    public:
        StartingBlock() : ContextState("startingblock") {}

        bool handle(ExpressionContext* ctx, const std::string& input) override;
};

class CollectingBlock : public ContextState
{
    public:
        CollectingBlock() : ContextState("collectingblock") {}

        bool handle(ExpressionContext* ctx, const std::string& input) override;
};

class DoneBlock : public ContextState
{
    public:
        DoneBlock() : ContextState("doneblock") {}

        bool handle(ExpressionContext* ctx, const std::string& input) override {
        }
};

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
        virtual bool interpret(const ExpressionContext& ctx, std::string input) = 0;
};

class StartBlockExpr: public Expression
{
    public:
        bool interpret(const ExpressionContext& ctx, std::string input) override
        {
            if (input == "{" && ctx.level() == 0)
                return true;
            if (input == "{" || input == "}")
                return false;
            if (ctx.in_state("initial"))
                return true;
            return false;
        }
};

class CommandExpr: public Expression
{
    public:
        bool interpret(const ExpressionContext&, std::string input) override
        {
            if (input == "{" || input == "}")
                return false;
            return true;
        }
};

class EndBlockExpr: public Expression
{
    public:
        bool interpret(const ExpressionContext& ctx, std::string input) override
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

class Processor;

class Context
{
    public:
        virtual ~Context() {}
};

using ContextUPtr = std::unique_ptr<Context>;

class State
{
    public:
        State(const char* name) : name_(name) {}
        ~State() { std::cout << "dtor: " << name_ << "\n"; }

        const char* name() const { return name_; }

        virtual bool handle(Processor* proc, Context& ctx) = 0;

    protected:
        const char* const name_;
};

using StateUPtr = std::unique_ptr<State>;

/**
 * @brief The Collecting state class
 * Collects a block of commands
 */
class Collecting : public State
{
    public:
        Collecting() : State("collecting") {}

        bool handle(Processor* proc, Context& ctx) override;
};

/**
 * @brief The Processing state class
 * Process the block of commands
 */
class Processing : public State
{
    public:
        Processing() : State("processing") {}

        bool handle(Processor* proc, Context& ctx) override;
};

class InputContext : public Context
{
    public:
        const std::string& input() const { return input_; }
        void set_input(const std::string& input) { input_ = input; }

    private:
        std::string input_;
};

class Iterpreter
{
    public:
};

/**
 * @brief The Processor class
 * Reads and process the input commands according to the rules
 * The rules:
 *
 */
class Processor
{
    public:
        using block_t = std::vector<Command>;
        Processor();

        void add_token(const std::string& input);
        void handle(const std::string& input);
        void set_block_size(size_t block_size) { block_size_ = block_size; }

        bool add_command(Context& ctx);
        void run();

    private:
        size_t block_size_;
        size_t input_counter_;
        block_t block_;
        std::vector<std::string> commands_;
        StateUPtr state_;
};
