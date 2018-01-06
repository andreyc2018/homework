#include "homework_tools.h"
#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(print_ip)
{
    std::stringstream buffer;
    char ip = 1;
    otus::print_ip(buffer, ip);

    std::string expected = "1 --> 1 --> 1\n";
    BOOST_CHECK_EQUAL(expected, buffer.str());
}
