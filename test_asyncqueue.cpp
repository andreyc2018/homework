#include "asyncqueue.h"
#include <gtest/gtest.h>
#include "logger.h"
#include "xray.h"
#include <thread>

TEST(AsyncQueue, Init)
{
    gLogger->set_level(spdlog::level::trace);
    AsyncQueue<xray> q;
    EXPECT_TRUE(q.empty());

    xray v;
    q.push(std::move(v));
    EXPECT_FALSE(q.empty());

    EXPECT_EQ(v, q.pop());
    EXPECT_TRUE(q.empty());
}

template<typename T>
class Queue
{
    public:
        using queue_t = std::queue<T>;

        Queue() {}
        ~Queue() {}
        void push(const T& data)
        {
            q_.push(data);
        }

        void push(T&& data)
        {
            q_.push(std::move(data));
        }

        T pop()
        {
            auto data (std::move(q_.front()));
            q_.pop();
            return data;
        }

        bool empty() const
        {
            return q_.empty();
        }

    private:
        queue_t q_;
};

template<typename Q>
void producer(Q& q, int total)
{
    for (int i = 1; i < total; ++i) {
        q.push(i);
    }
    q.push(-1);
}

template<typename Q>
void consumer(Q& q)
{
    int prev = 0;
    int i;
    do {
        i = q.pop();
        if (i >= 0) {
            EXPECT_EQ(prev+1, i);
        }
        prev = i;
    }
    while(i >= 0);
}

//TEST(AsyncQueue, ProducerConsumerNonConcurent)
//{
//    Queue<int> q;

//    std::thread c(consumer<Queue<int>>, std::ref(q));
//    std::thread p(producer<Queue<int>>, std::ref(q), 5);

//    c.join();
//    p.join();
//}

TEST(AsyncQueue, ProducerConsumer)
{
    AsyncQueue<int> q;

    std::thread c(consumer<AsyncQueue<int>>, std::ref(q));
    std::thread p(producer<AsyncQueue<int>>, std::ref(q), 3000);

    c.join();
    p.join();
}
