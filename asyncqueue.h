#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <string>

#define xtrace()  std::cout << __PRETTY_FUNCTION__ << "\n"

template<typename T>
class AsyncQueue
{
    public:
        using queue_t = std::queue<T>;
        using guard_t = std::lock_guard<std::mutex>;
        using lock_t = std::unique_lock<std::mutex>;

        AsyncQueue() {}
        ~AsyncQueue() {}

        void push(const T& data)
        {
            guard_t g(m_);
            q_.push(data);
            c_.notify_all();
        }

        void push(T&& data)
        {
            guard_t g(m_);
            q_.push(std::move(data));
            c_.notify_all();
        }

        T pop()
        {
            lock_t l(m_);
            c_.wait(l, [&]() { return !q_.empty(); });
            auto data (std::move(q_.front()));
            q_.pop();
            return data;
        }

        bool empty() const
        {
            guard_t g(m_);
            return q_.empty();
        }

    private:
        mutable std::mutex m_;
        std::condition_variable c_;
        queue_t q_;
};

using MsgQueue = AsyncQueue<std::string>;
