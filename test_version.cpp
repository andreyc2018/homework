#include "allocator.h"
#define BOOST_TEST_MODULE Test_Allocator
#include <boost/test/unit_test.hpp>

template <typename T>
void fill_expected(T& e)
{
    /* https://www.rapidtables.com/math/algebra/Factorial.html */
    e.insert(std::make_pair(0, 1));
    e.insert(std::make_pair(1, 1));
    e.insert(std::make_pair(2, 2));
    e.insert(std::make_pair(3, 6));
    e.insert(std::make_pair(4, 24));
    e.insert(std::make_pair(5, 120));
    e.insert(std::make_pair(6, 720));
    e.insert(std::make_pair(7, 5040));
    e.insert(std::make_pair(8, 40320));
    e.insert(std::make_pair(9, 362880));
}

BOOST_AUTO_TEST_CASE(fill)
{
    otus::map_t expected;
    fill_expected(expected);

    otus::map_t m;
    otus::fill(m);

    BOOST_CHECK_EQUAL(expected.size(), m.size());

    for (size_t i = 0; i < expected.size(); ++i) {
        BOOST_CHECK_EQUAL(expected[i], m[i]);
    }
}

BOOST_AUTO_TEST_CASE(allocator)
{
    otus::map_t expected;
    fill_expected(expected);

    otus::map_alloc_t m;
    otus::fill(m);

    BOOST_CHECK_EQUAL(expected.size(), m.size());

    for (size_t i = 0; i < expected.size(); ++i) {
        BOOST_CHECK_EQUAL(expected[i], m[i]);
    }
}
