#pragma once
#include "interpreter.h"
#include <iostream>
#include <memory>
#include <string>

class ExpressionContext;

class ContextState
{
    public:
        ContextState(const std::string& name) : name_(name) {}
        virtual ~ContextState() { std::cout << "dtor: " << name_ << "\n"; }

        const std::string& name() const { return name_; }
        virtual bool handle(ExpressionContext* ctx, Expression::Type type, const std::string& input) = 0;

//        virtual BlockUPtr create_block(ExpressionContext*) = 0;

    protected:
        const std::string name_;
};

using ContextStateUPtr = std::unique_ptr<ContextState>;

class StartingBlock : public ContextState
{
    public:
        StartingBlock() : ContextState("startingblock") {}

        bool handle(ExpressionContext* ctx, Expression::Type type, const std::string& input) override;
};

class CollectingBlock : public ContextState
{
    public:
        CollectingBlock() : ContextState("collectingblock") {}

        bool handle(ExpressionContext* ctx, Expression::Type type, const std::string& input) override;
};

class DoneBlock : public ContextState
{
    public:
        DoneBlock() : ContextState("doneblock") {}

        bool handle(ExpressionContext* ctx, Expression::Type type, const std::string& input) override;
};
