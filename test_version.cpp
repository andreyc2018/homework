#include "ip_filter.h"
#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(split)
{
    auto result = otus::split<otus::entry_types_t>("", '.');
    BOOST_CHECK_EQUAL(1, result.size());
    BOOST_CHECK(result[0] == 0);

    result = otus::split<otus::entry_types_t>("11", '.');
    BOOST_CHECK_EQUAL(1, result.size());
    BOOST_CHECK_EQUAL(11, result[0]);

    result = otus::split<otus::entry_types_t>("..", '.');
    BOOST_CHECK_EQUAL(3, result.size());
    for (const auto& r : result) {
        BOOST_CHECK(r == 0);
    }
}

BOOST_AUTO_TEST_CASE(reverse)
{
    otus::pool_t pool {
        {1, 2, 1, 1},
        {1, 10, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 1, 1}
    };

    std::string expected_reversed = "1.10.1.1\n"
                                    "1.2.3.1\n"
                                    "1.2.1.1\n"
                                    "1.1.1.1\n";

    otus::reverse(pool);
    std::stringstream buffer;
    otus::print(buffer, pool);
    BOOST_CHECK_EQUAL(expected_reversed, buffer.str());
}

BOOST_AUTO_TEST_CASE(print_reverse)
{
    otus::pool_t pool {
        {1, 2, 1, 1},
        {1, 10, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 1, 1}
    };

    std::string expected_reversed = "1.10.1.1\n"
                                    "1.2.3.1\n"
                                    "1.2.1.1\n"
                                    "1.1.1.1\n";

    std::stringstream buffer;
    otus::print_reverse(buffer, pool);
    BOOST_CHECK_EQUAL(expected_reversed, buffer.str());

    buffer.str("");
    otus::print(buffer, pool);
    BOOST_CHECK_EQUAL(expected_reversed, buffer.str());
}

BOOST_AUTO_TEST_CASE(filter)
{
    otus::pool_t pool {
        {185, 69, 186, 168},
        {110, 152, 103, 161},
        {185, 182, 81, 68},
        {68, 45, 152, 8},
        {114, 68, 179, 117},
        {185, 69, 68, 249}
    };

    std::string expected = "185.69.186.168\n"
                           "110.152.103.161\n"
                           "185.182.81.68\n"
                           "68.45.152.8\n"
                           "114.68.179.117\n"
                           "185.69.68.249\n";

    std::stringstream buffer;
    otus::print(buffer, pool);
    BOOST_CHECK_EQUAL(expected, buffer.str());

    std::string expected_filter_first = "185.69.186.168\n"
                                        "185.182.81.68\n"
                                        "185.69.68.249\n";
    buffer.str("");
    otus::print_filter(buffer, pool, 185u);
    BOOST_CHECK_EQUAL(expected_filter_first, buffer.str());

    std::string expected_filter_two = "185.69.186.168\n"
                                      "185.69.68.249\n";
    buffer.str("");
    otus::print_filter(buffer, pool, 185u, 69u);
    BOOST_CHECK_EQUAL(expected_filter_two, buffer.str());
}

BOOST_AUTO_TEST_CASE(filter_any)
{
    otus::pool_t pool {
        {185, 69, 186, 168},
        {110, 152, 103, 161},
        {185, 182, 81, 68},
        {68, 45, 152, 8},
        {114, 68, 179, 117},
        {185, 69, 68, 249}
    };

    std::string expected_any = "185.182.81.68\n"
                               "68.45.152.8\n"
                               "114.68.179.117\n"
                               "185.69.68.249\n";
    std::stringstream buffer;
    otus::print_filter_any(buffer, pool, 68u);
    BOOST_CHECK_EQUAL(expected_any, buffer.str());
}
