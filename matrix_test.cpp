#include "matrix.h"
#define BOOST_TEST_MODULE Test_Ip_Filter
#include <boost/test/unit_test.hpp>
#include <iostream>

using matrix::Cell;

BOOST_AUTO_TEST_CASE(init)
{
    Cell<int, 2> c1;
    c1.set(10, 1, 1);
    
    BOOST_CHECK_EQUAL(1, 0);
    BOOST_CHECK(false);
}

