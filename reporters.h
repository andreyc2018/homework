#pragma once

#include "message.h"
#include "writers.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <fstream>

class Reporter
{
    public:
        Reporter(IWriterUPtr& w) : w_(std::move(w)) {}
        ~Reporter() {}
        void update(const BlockMessage& data)
        {
            w_->write(data);
        }

    private:
        IWriterUPtr w_;
};
