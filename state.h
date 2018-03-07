#pragma once
#include "interpreter.h"
#include <iostream>
#include <memory>
#include <string>

class ParserContext;

class ContextState
{
    public:
        ContextState(const std::string& name) : name_(name) {}
        virtual ~ContextState() { std::cout << "dtor: " << name_ << "\n"; }

        const std::string& name() const { return name_; }
        virtual bool handle(ParserContext* ctx, Expression::Type type, const std::string& input) = 0;

    protected:
        const std::string name_;
};

using ContextStateUPtr = std::unique_ptr<ContextState>;

class StartingBlock : public ContextState
{
    public:
        StartingBlock() : ContextState("StartingBlock") {}

        bool handle(ParserContext* ctx, Expression::Type type, const std::string& input) override;
};

class CollectingBlock : public ContextState
{
    public:
        CollectingBlock() : ContextState("CollectingBlock") {}

        bool handle(ParserContext* ctx, Expression::Type type, const std::string& input) override;
};

class DoneBlock : public ContextState
{
    public:
        DoneBlock() : ContextState("DoneBlock") {}

        bool handle(ParserContext* ctx, Expression::Type type, const std::string& input) override;
};
