#pragma once

#include "messagequeue.h"
#include "counters.h"
#include "logger.h"
#include <thread>
#include <memory>
#include <fstream>

class IListener
{
    public:
        IListener(MessageQueue& q) : q_(q) {}
        virtual ~IListener()
        {
            wait();
        }

        virtual void listen() = 0;
        virtual void report(std::ostream&) = 0;

        void run()
        {
            thread_ = std::make_unique<std::thread>(&IListener::listen, this);
        }

        void wait()
        {
            if (thread_->joinable()) {
                thread_->join();
            }
        }

        MessageQueue& queue() { return q_; }

    protected:
        MessageQueue& q_;
        Counters counters_;
        std::unique_ptr<std::thread> thread_;

        void update_counters(const Message& msg)
        {
            counters_.commands += msg.block.commands;
            ++counters_.blocks;
        }
};

class ConsoleListener : public IListener
{
    public:
        ConsoleListener(MessageQueue& q) : IListener(q) {}

        void listen() override
        {
            Message msg;
            do
            {
                msg = q_.pop();
                gLogger->debug("{}: data = {}, commands = {}",
                               __func__, msg.block.data, msg.block.commands);
                if (msg.id == MessageId::Data) {
                    std::cout << msg.block.data;
                    update_counters(msg);
                }
            } while (msg.id != MessageId::EndOfStream);
        }

        void report(std::ostream& out) override
        {
            out << "log поток - "
                << counters_.blocks << " блок, "
                << counters_.commands << " команд\n";
        }
};

class FileListener : public IListener
{
    public:
        FileListener(MessageQueue& q, int id) : IListener(q), id_(id) {}

        void listen() override
        {
            Message msg;
            do
            {
                msg = q_.pop();
                if (msg.id == MessageId::Data) {
                    gLogger->debug("{}:{}: filename = {}, data = {}",
                                  __func__, __LINE__, msg.filename, msg.block.data);
                    std::ofstream file(msg.filename);
                    file << msg.block.data;
                    file.close();
                    update_counters(msg);
                }
            } while (msg.id != MessageId::EndOfStream);
        }

        void report(std::ostream& out) override
        {
            out << "file " << id_ << " поток - "
                << counters_.blocks << " блок, "
                << counters_.commands << " команд\n";
        }

    private:
        const int id_;
};
