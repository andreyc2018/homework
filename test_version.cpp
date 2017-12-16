#include "ip_filter.h"
#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>

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

BOOST_AUTO_TEST_CASE(filter)
{
    std::vector<std::vector<std::string>> pool { 
        {"", "", "", ""}, {"1", "70", "44", "170"}
    };

    
    BOOST_CHECK_EQUAL(2, pool.size());
}
