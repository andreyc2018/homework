#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <fstream>
#include "writers.h"

class Reporter
{
    public:
        Reporter(IWriterUPtr& w) : w_(std::move(w)) {}
        ~Reporter() {}
        void update(const std::string& data)
        {
            w_->write(data);
        }

    private:
        IWriterUPtr w_;
};
