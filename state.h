#pragma once
#include <iostream>
#include <memory>
#include <string>

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

        bool handle(ExpressionContext* ctx, const std::string& input) override;
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
