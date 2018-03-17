/**
 * @file parserstate.h
 * @image html parser_state_machine.png
 */

#pragma once
#include "interpreter.h"
#include <iostream>
#include <memory>
#include <string>

/**
 * Parser has a state and calls Expression according the state
 * in a state handler.
 */

class Parser;

class ParserState
{
    public:
        ParserState(const std::string& name) : name_(name) {}
        virtual ~ParserState() {}

        const std::string& name() const { return name_; }
        virtual bool handle(Parser* ctx, const std::string& input) = 0;

        template<typename T>
        static ParserState* create() { return new T; }

    protected:
        const std::string name_;
};

using ParserStateUPtr = std::unique_ptr<ParserState>;

class StartingBlock : public ParserState
{
    public:
        StartingBlock() : ParserState("StartingBlock") {}

        bool handle(Parser* ctx, const std::string& input) override;
};

class CollectingBlock : public ParserState
{
    public:
        CollectingBlock() : ParserState("CollectingBlock") {}

        bool handle(Parser* ctx, const std::string& input) override;
};

class DoneBlock : public ParserState
{
    public:
        DoneBlock() : ParserState("DoneBlock") {}

        bool handle(Parser* ctx, const std::string& input) override;
};
