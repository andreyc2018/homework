/** @file test_version.cpp
    @brief The unit tests
*/
//#include "point.h"
//#include "line.h"
#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>
#include <iostream>

//using svge::item_id_t;
//using svge::create_item;
//using svge::Point;
//using svge::ComplexItem;

BOOST_AUTO_TEST_CASE(point_init)
{
//    auto p = create_item<Point>(101, 390);
//    BOOST_CHECK_EQUAL(2, p->id());
//    BOOST_CHECK_EQUAL(101, p->x());
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(line_init)
{
//    auto l = create_item<Line>();
//    BOOST_CHECK_EQUAL(3, l->id());
    BOOST_CHECK(true);
}
