/** @file test_version.cpp
    @brief The unit tests
*/
#include "item.h"
#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>
#include <iostream>

using svge::Item;
using svge::item_id_t;
using svge::create_item;
using svge::SimpleItem;
using svge::ComplexItem;

class Point : public SimpleItem
{
    public:
        Point(item_id_t id, ssize_t x, ssize_t y)
            : SimpleItem(id), x_(x), y_(y) {}

        ssize_t x() const { return x_; }
        void setX(const ssize_t& x) { x_ = x; }

        ssize_t y() const { return y_; }
        void setY(const ssize_t& y) { y_ = y; }

    protected:
        ssize_t x_;
        ssize_t y_;

};

class Line : public ComplexItem
{
    public:
        Line(item_id_t id) : ComplexItem(id) {}

        void set_start(Point* p) { add_item(p); }
        void set_end(Point* p) { add_item(p); }
};

BOOST_AUTO_TEST_CASE(item_init)
{
    auto v = create_item<Item>();
    BOOST_CHECK_EQUAL(1, v->id());
//    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(point_init)
{
    auto p = create_item<Point>(101, 390);
    BOOST_CHECK_EQUAL(2, p->id());
    BOOST_CHECK_EQUAL(101, p->x());
//    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(line_init)
{
    auto l = create_item<Line>();
    BOOST_CHECK_EQUAL(3, l->id());
//    BOOST_CHECK(false);
}
