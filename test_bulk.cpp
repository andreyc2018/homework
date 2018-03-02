#include "bulk.h"
#define BOOST_TEST_MODULE Bulk
#include <boost/test/unit_test.hpp>
#include <iostream>

#define TRACE()  std::cout << __PRETTY_FUNCTION__

class P;

class S
{
    public:
        S(const char* name) : name_(name) { TRACE(); }
        virtual ~S() { TRACE(); }

        virtual void handle(P& p) = 0;

    protected:
        const std::string name_;
};

using SUPtr = std::unique_ptr<S>;

class P
{
    public:
        P() { TRACE(); }
        ~P() { TRACE(); }

    private:
        SUPtr s_;
};

class S1 : public S
{
    public:
        S1() : S("S1") {}

        void handle(P& p) override
        {

        }
};

BOOST_AUTO_TEST_CASE(init)
{

    BOOST_CHECK_EQUAL(1, 1);
    BOOST_CHECK(true);
}

