#pragma once
#include "message.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class Command
{
    public:
        explicit Command(const std::string& name)
            : name_(name), valid_(name != "{" && name != "}") {}

        static Command create(const std::string& name) {
            return Command(name);
        }

        virtual void run(std::iostream& out) {
            out << name_;
        }

        bool valid() const { return valid_; }

        std::string name() const { return name_; }

    protected:
        std::string name_;
        bool valid_;
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
            if (cmd.valid()) {
                commands_.push_back(cmd);
            }
        }

        size_t size() const { return commands_.size(); }

    private:
        block_t commands_;
};

using BlockUPtr = std::unique_ptr<Block>;
