#pragma once

#include "observers.h"
#include "command.h"
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

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
