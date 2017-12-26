#include "homework_tools.h"
#include <numeric>
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

    otus::map_alloc_t map_one;
    otus::fill(map_one);

    otus::map_alloc_t map_two;
    otus::fill(map_two);

    BOOST_CHECK_EQUAL(expected.size(), map_one.size());
    BOOST_CHECK_EQUAL(expected.size(), map_two.size());

    for (size_t i = 0; i < expected.size(); ++i) {
        BOOST_CHECK_EQUAL(expected[i], map_one[i]);
    }

    for (size_t i = 0; i < expected.size(); ++i) {
        BOOST_CHECK_EQUAL(expected[i], map_two[i]);
    }
}

BOOST_AUTO_TEST_CASE(single_linked_list)
{
    otus::custom_list_t list(5);
    auto it = list.begin();
    *it = 7;
    BOOST_CHECK_EQUAL(7, *it);
    *(++it) = 8;
    BOOST_CHECK_EQUAL(8, *it);
    *(it++) = 9;
    BOOST_CHECK_EQUAL(0, *it);
    it = list.begin();
    BOOST_CHECK_EQUAL(7, *it);
    ++it;
    BOOST_CHECK_EQUAL(9, *it);
    ++it;
    BOOST_CHECK_EQUAL(0, *it);

    std::iota(list.begin(), list.end(), 0);
    int i = 0;
    for (auto& n : list) {
        BOOST_CHECK_EQUAL(i, n);
        ++i;
    }
}

BOOST_AUTO_TEST_CASE(single_linked_list_custom_allocator)
{
    otus::custom_list_alloc_t list(5);
    auto it = list.begin();
    *it = 7;
    BOOST_CHECK_EQUAL(7, *it);
    *(++it) = 8;
    BOOST_CHECK_EQUAL(8, *it);
    *(it++) = 9;
    BOOST_CHECK_EQUAL(0, *it);
    it = list.begin();
    BOOST_CHECK_EQUAL(7, *it);
    ++it;
    BOOST_CHECK_EQUAL(9, *it);
    ++it;
    BOOST_CHECK_EQUAL(0, *it);

    std::iota(list.begin(), list.end(), 0);
    int i = 0;
    for (auto& n : list) {
        BOOST_CHECK_EQUAL(i, n);
        ++i;
    }
}
