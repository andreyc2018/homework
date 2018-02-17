#include "matrix.h"
#define BOOST_TEST_MODULE Matrix
#include <boost/test/unit_test.hpp>
#include <iostream>

using matrix::Cell;
using matrix::Matrix;

BOOST_AUTO_TEST_CASE(init)
{
    Cell<int> c1(1, 1);
    c1.set_value(10);

    Cell<int> c2(1, 1);
    c2.set_value(10);

// error: no matching function for call to ‘matrix::Cell<int, 3>::set(int, int, int)’
//    constexpr int Dimension = 3;
//    Cell<int, 3> c3;
//    int value = 11;
//    int x = 1, y = 1, z = 0;
//    c3.set(value, x, y); Number of coordinates is less than a dimension

    BOOST_CHECK(!(c1 < c2));

    Cell<int> c4(0, 0);
    c4.set_value(12);
    BOOST_CHECK(c4 < c1);
}

BOOST_AUTO_TEST_CASE(add_to_set)
{
    constexpr int Dimension = 2;
    using cell_t = Cell<int, Dimension>;
    std::set<cell_t> matrix;

    cell_t c1;
    c1.set_coordinates(1, 1);
    c1.set_value(10);

    cell_t c2(1, 1);
    c2.set_value(11);

    auto rc = matrix.insert(c1);
    BOOST_CHECK(rc.second);
    BOOST_CHECK_EQUAL(1, matrix.size());
    BOOST_CHECK_EQUAL(c1.get_value(), rc.first->get_value());

    rc = matrix.insert(c2);
    BOOST_CHECK(!rc.second);
    BOOST_CHECK_EQUAL(1, matrix.size());
    BOOST_CHECK_EQUAL(c1.get_value(), rc.first->get_value());

    cell_t c3(1, 1);
    BOOST_CHECK_EQUAL(0, c3.get_value());
    auto it = matrix.find(c3);
    BOOST_CHECK_EQUAL(c1.get_value(), it->get_value());
}

BOOST_AUTO_TEST_CASE(assignment)
{
    constexpr int Dimension = 2;
    using cell_t = Cell<int, Dimension>;

    std::set<cell_t> matrix;

    cell_t c4(1, 2);
    auto it = matrix.find(c4);
    BOOST_CHECK(it == matrix.end());

    c4.set_value(12);
    auto rc = matrix.insert(c4);
    BOOST_CHECK(rc.second);
    BOOST_CHECK_EQUAL(c4.get_value(), rc.first->get_value());

    it = matrix.find(c4);
    BOOST_CHECK(it != matrix.end());
    BOOST_CHECK_EQUAL(c4.get_value(), it->get_value());

    cell_t c5(3, 3);
    c5 = 12;
    rc = matrix.insert(c5);
    BOOST_CHECK(rc.second);
    BOOST_CHECK_EQUAL(c5.get_value(), rc.first->get_value());

    it = matrix.find(c5);
    BOOST_CHECK(it != matrix.end());
    BOOST_CHECK_EQUAL(c5.get_value(), it->get_value());
}

//BOOST_AUTO_TEST_CASE(matrix_init)
//{
//    using matrix_t = Matrix<int, 2, -1>;

//    matrix_t m;
//    std::cout << m[1] << "\n";
//}
