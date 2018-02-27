#include "matrix.h"
#include <map>
#define BOOST_TEST_MODULE Matrix
#include <boost/test/unit_test.hpp>
#include <iostream>

//using matrix::Cell;
//using matrix::Matrix;

BOOST_AUTO_TEST_CASE(init)
{
    Matrix<int, 2, 0>::Cell c1(1, 1);
    c1.set_value(10);

    Matrix<int, 2, 0>::Cell c2(1, 1);
    c2.set_value(10);

// error: no matching function for call to ‘matrix::Cell<int, 3>::set(int, int, int)’
//    constexpr int Dimension = 3;
//    Cell<int, 3> c3;
//    int value = 11;
//    int x = 1, y = 1, z = 0;
//    c3.set(value, x, y); Number of coordinates is less than a dimension

    BOOST_CHECK(!(c1 < c2));

    Matrix<int, 2, 0>::Cell c4(0, 0);
    c4.set_value(12);
    BOOST_CHECK(c4 < c1);
}

#if 0
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

    cell_t c5(3, 5);
    c5 = 12;
    rc = matrix.insert(c5);
    BOOST_CHECK(rc.second);
    BOOST_CHECK_EQUAL(c5.get_value(), rc.first->get_value());

    it = matrix.find(c5);
    BOOST_CHECK(it != matrix.end());
    BOOST_CHECK_EQUAL(c5.get_value(), it->get_value());

    int x;
    int y;
    int v = 99;
    std::tie(x, y, v) = c5;
    BOOST_CHECK_EQUAL(3, x);
    BOOST_CHECK_EQUAL(5, y);
    BOOST_CHECK_EQUAL(12, v);
}

BOOST_AUTO_TEST_CASE(matrix_example)
{
    Matrix<int, 2, -1> m;
    BOOST_CHECK_EQUAL(0, m.size());
    auto a = m.get(0, 0);
    BOOST_CHECK_EQUAL(-1, a);
    BOOST_CHECK_EQUAL(0, m.size());
    m.set(314, 100, 100);
    BOOST_CHECK_EQUAL(314, m.get(100, 100));
    BOOST_CHECK_EQUAL(1, m.size());
//    Matrix<int, 2, -1>::iterator it = m.begin();
//    std::cout << (*it).get_value() << "\n";
//    for(auto c : m)
//    {
//        int x;
//        int y;
//        int v;
//        std::tie(x, y, v) = c;
//        std::cout << x << y << v << std::endl;
//    }
}
#endif
