#include "logger.h"
#include "googletest/googletest/include/gtest/gtest.h"
#include "googletest/googlemock/include/gmock/gmock.h"

class NonVirtProc
{
    public:
        void run() { TRACE(); }
};

template<typename Proc>
class UseNonVirtProc
{
    public:
        UseNonVirtProc(Proc* p) : p_(p) {}

        void notify() { p_->run(); }

    private:
        Proc* p_;
};

TEST(NonVirtMock, CallBaseClass)
{
    NonVirtProc* proc = new NonVirtProc;
    UseNonVirtProc<NonVirtProc> use(proc);
    use.notify();
    delete proc;
}

class MockNonVirtProc
{
    public:
        MOCK_METHOD0(run, void());
};

TEST(NonVirtMock, CallMockClass)
{
    MockNonVirtProc proc;
    EXPECT_CALL(proc, run());
    UseNonVirtProc<MockNonVirtProc> use(&proc);
    use.notify();
}
