#include "bulk.h"
#define BOOST_TEST_MODULE Bulk
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(block)
{
    auto b1 = Block::create();

    auto c1 = Command::create("c1");
    b1.add_command(c1);

    auto c2 = Command::create("c2");
    b1.add_command(c2);

    std::stringstream ss;
    b1.run(ss);

    std::cout << ss.str();

    BOOST_CHECK_EQUAL("bulk: c1, c2\n", ss.str());
}

BOOST_AUTO_TEST_CASE(intrepreter)
{
    ExpressionContext ctx(2);
    StartBlockExpr start_expr;
}
