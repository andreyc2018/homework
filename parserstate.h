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
        static
        ParserState* create(ParserState* state) {
            delete state;
            return  new T;
        }

    protected:
        const std::string name_;
};

using ParserStateUPtr = std::unique_ptr<ParserState>;

class StartingBlock : public ParserState
{
    public:
        StartingBlock() : ParserState("StartingBlock") {}

        static ParserState* create(ParserState* state) {
            return ParserState::create<StartingBlock>(state);
        }

        bool handle(Parser* ctx, const std::string& input) override;
};

class CollectingBlock : public ParserState
{
    public:
        CollectingBlock() : ParserState("CollectingBlock") {}

        static ParserState* create(ParserState* state) {
            return ParserState::create<CollectingBlock>(state);
        }

        bool handle(Parser* ctx, const std::string& input) override;
};

class DoneBlock : public ParserState
{
    public:
        DoneBlock() : ParserState("DoneBlock") {}

        static ParserState* create(ParserState* state) {
            return ParserState::create<DoneBlock>(state);
        }

        bool handle(Parser* ctx, const std::string& input) override;
};
