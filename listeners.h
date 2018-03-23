#pragma once

#include "messagequeue.h"
#include "counters.h"
#include "logger.h"
#include <thread>
#include <memory>

class IListener
{
    public:
        virtual void listen() = 0;
        virtual void report() = 0;

        void run()
        {
            thread_.reset(std::make_unique<std::thread>());
        }

        void wait()
        {
            if (thread_->joinable()) {
                thread_->join();
            }
        }

        MessageQueue& queue() { return q_; }

    protected:
        MessageQueue q_;
        Counters counters_;
        std::unique_ptr<std::thread> thread_;
};

class ConsoleListener : public IListener
{
    public:
        void listen() override
        {
            Message msg;
            do
            {
                gLogger->debug("{}: pop data", __func__);
                msg = q_.pop();
                gLogger->debug("{}: data = {}", __func__, msg.block.data);
                if (msg.id == MessageId::Data) {
                    std::cout << msg.block.data;
                    counters_.commands += msg.block.commands;
                    ++counters_.blocks;
                }
            } while (msg.id != MessageId::EndOfStream);
        }

        void report() override
        {
            std::cout << "log поток - "
                      << counters_.blocks << " блок, "
                      << counters_.commands << " команд\n";
        }
};


