#include "ip_filter.h"
#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(split)
{
    auto result = otus::split("", '.');
    BOOST_CHECK_EQUAL(1, result.size());
    BOOST_CHECK(result[0].empty());

    result = otus::split("11", '.');
    BOOST_CHECK_EQUAL(1, result.size());
    BOOST_CHECK_EQUAL("11", result[0]);

    result = otus::split("..", '.');
    BOOST_CHECK_EQUAL(3, result.size());
    for (const auto& r : result) {
        BOOST_CHECK(r.empty());
    }
}

BOOST_AUTO_TEST_CASE(reverse)
{
    std::vector<std::vector<std::string>> pool {
        {"1", "2", "1", "1"},
        {"1", "10", "1", "1"},
        {"1", "2", "3", "1"},
        {"1", "1", "1", "1"}
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
    std::vector<std::vector<std::string>> pool {
        {"1", "2", "1", "1"},
        {"1", "10", "1", "1"},
        {"1", "2", "3", "1"},
        {"1", "1", "1", "1"}
    };

    std::string expected_original = "1.2.1.1\n"
                                    "1.10.1.1\n"
                                    "1.2.3.1\n"
                                    "1.1.1.1\n";

    std::string expected_reversed = "1.10.1.1\n"
                                    "1.2.3.1\n"
                                    "1.2.1.1\n"
                                    "1.1.1.1\n";

    std::stringstream buffer;
    otus::print(buffer, pool);
    BOOST_CHECK_EQUAL(expected_original, buffer.str());

    buffer.str("");
    otus::print_reverse(buffer, pool);
    BOOST_CHECK_EQUAL(expected_reversed, buffer.str());
}

BOOST_AUTO_TEST_CASE(filter)
{
    std::vector<std::vector<std::string>> pool {
        {"185", "69", "186", "168"},
        {"110", "152", "103", "161"},
        {"185", "182", "81", "68"},
        {"68", "45", "152", "8"},
        {"114", "68", "179", "117"},
        {"185", "69", "68", "249"}
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
    otus::print_filter(buffer, pool, 185);
    BOOST_CHECK_EQUAL(expected_filter_first, buffer.str());

    std::string expected_filter_two = "185.69.186.168\n"
                                      "185.69.68.249\n";
    buffer.str("");
    otus::print_filter(buffer, pool, 185, 69);
    BOOST_CHECK_EQUAL(expected_filter_two, buffer.str());
}

BOOST_AUTO_TEST_CASE(filter_any)
{
    std::vector<std::vector<std::string>> pool {
        {"185", "69", "186", "168"},
        {"110", "152", "103", "161"},
        {"185", "182", "81", "68"},
        {"68", "45", "152", "8"},
        {"114", "68", "179", "117"},
        {"185", "69", "68", "249"}
    };

    std::string expected_any = "185.182.81.68\n"
                               "68.45.152.8\n"
                               "114.68.179.117\n"
                               "185.69.68.249\n";
    std::stringstream buffer;
    otus::print_filter_any(buffer, pool, 68);
    BOOST_CHECK_EQUAL(expected_any, buffer.str());
}
