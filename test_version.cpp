/** @file test_version.cpp
    @brief The unit tests
*/
#include "point.h"
#define BOOST_TEST_MODULE Test_SVGE
#include <boost/test/unit_test.hpp>
#include <sstream>

using svge::shape_type_t;
using svge::Point;

BOOST_AUTO_TEST_CASE(shape_type)
{
    shape_type_t t = shape_type_t::Point;

    std::stringstream ss;
    ss.write(reinterpret_cast<const char*>(&t), sizeof (t));
    std::cout << "Read type as uint8_t and compare with 1\n";
    ss.seekg(0);
    uint8_t ut;
    ss.read(reinterpret_cast<char*>(&ut), sizeof (ut));
    BOOST_CHECK_EQUAL(1, ut);

    std::cout << "Read type as shape_type_t and compare with Point\n";
    ss.seekg(0);
    shape_type_t t2;
    ss.read(reinterpret_cast<char*>(&t2), sizeof (t2));
    BOOST_CHECK_EQUAL(shape_type_t::Point, t2);

    std::cout << "Set uint8_t to value more than shape_type_t and write to stringstream\n";
    uint8_t ut1 = 99;
    ss.str(std::string());
    ss.write(reinterpret_cast<const char*>(&ut1), sizeof (ut1));
    std::cout << "Read out of range value into shape_type_t\n";
    ss.seekg(0);
    shape_type_t t3;
    ss.read(reinterpret_cast<char*>(&t3), sizeof (t3));
}

BOOST_AUTO_TEST_CASE(point_init)
{
    auto p = std::make_unique<Point>();
    BOOST_CHECK(p);
    BOOST_CHECK_EQUAL(0, p->id());
    BOOST_CHECK_EQUAL(0, p->x());
}
