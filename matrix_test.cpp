#include "matrix.h"
#include <map>
#define BOOST_TEST_MODULE Matrix
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(init)
{
    Matrix<int, 2, 0>::Cell c1(nullptr, 1, 1);
    c1 = 10;

    Matrix<int, 2, 0>::Cell c2(nullptr, 1, 1);
    c2 = 10;

// error: no matching function for call to ‘Matrix<int, 3, 0>::Cell::Cell(std::nullptr_t, int, int)
//    Matrix<int, 3, 0>::Cell c3(nullptr, 1, 1);

    BOOST_CHECK(!(c1 < c2));

    Matrix<int, 2, 0>::Cell c4(nullptr, 0, 0);
    c4 = 12;
    BOOST_CHECK(c4 < c1);
}

BOOST_AUTO_TEST_CASE(matrix_example)
{
    Matrix<int, 2, -1> m;
    BOOST_CHECK_EQUAL(0, m.size());
    auto a = m(0, 0);
    BOOST_CHECK_EQUAL(-1, a);
    BOOST_CHECK_EQUAL(0, m.size());
    m(100, 100) = 314;
    BOOST_CHECK_EQUAL(314, m(100, 100));
    BOOST_CHECK_EQUAL(1, m.size());
    Matrix<int, 2, -1>::iterator it = m.begin();
    std::cout << (*it) << "\n";
    for(auto c : m)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << "[" << x << "][" << y << "] = " << v << std::endl;
    }
}

BOOST_AUTO_TEST_CASE(matrix_example_four_dim)
{
    Matrix<int, 4, -1> m;
    BOOST_CHECK_EQUAL(0, m.size());
    auto a = m(0, 0, 0, 0);
    BOOST_CHECK_EQUAL(-1, a);
    BOOST_CHECK_EQUAL(0, m.size());
    m(100, 100, 200, 300) = 314;
    BOOST_CHECK_EQUAL(314, m(100, 100, 200, 300));
    BOOST_CHECK_EQUAL(1, m.size());
    Matrix<int, 4, -1>::iterator it = m.begin();
    std::cout << (*it) << "\n";
    for(auto c : m)
    {
        int w;
        int x;
        int y;
        int z;
        int v;
        std::tie(w, x, y, z, v) = c;
        std::cout << "[" << w << "][" << x << "]" << "[" << y << "][" << z << "] = " << v << std::endl;
    }
}
