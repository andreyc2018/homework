#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>

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

        virtual void handle(Processor* proc, Context& ctx) = 0;

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

        void handle(Processor* proc, Context& ctx) override;
};

/**
 * @brief The Processing state class
 * Process the block of commands
 */
class Processing : public State
{
    public:
        Processing() : State("processing") {}

        void handle(Processor* proc, Context& ctx) override;
};

class InputContext : public Context
{
    public:
        const std::string& input() const { return input_; }
        void set_input(const std::string& input) { input_ = input; }

    private:
        std::string input_;
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
        Processor();

        void handle(const std::string& input);
        void set_block_size(size_t block_size) { block_size_ = block_size; }

        void add_command(Context& ctx);
        void run();

    private:
        size_t block_size_;
        size_t input_counter_;
        std::vector<std::string> commands_;
        StateUPtr state_;
};
