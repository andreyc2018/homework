#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "homework_tools.h"

/*! \test Test for print_ip for a numeric unit
 */
BOOST_AUTO_TEST_CASE(print_ip)
{
    std::stringstream buffer;
    char ip = 1;
    otus::print_ip(buffer, ip);

    std::string expected = "1 --> 1\n";
    BOOST_CHECK_EQUAL(expected, buffer.str());
}

/*! \test Test std::string for print_ip
 * Fails to compile
 */
BOOST_AUTO_TEST_CASE(print_ip_string)
{
//    std::stringstream buffer;
//    std::string ip = "1";
//    otus::print_ip(buffer, ip);

//    std::string expected = "1 --> 1 --> 1\n";
//    BOOST_CHECK_EQUAL(expected, buffer.str());
}

/*! \test Test print_ip for a container
 */
BOOST_AUTO_TEST_CASE(print_ip_container)
{
    std::stringstream buffer;
    std::vector<std::string> ip { "1", "2" };
    otus::print_ip(buffer, ip);

    std::string expected = "1,2 --> 1.2\n";
    BOOST_CHECK_EQUAL(expected, buffer.str());
}
