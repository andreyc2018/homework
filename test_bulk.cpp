#include "command.h"
#include "interpreter.h"
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
    std::vector<Expression> exp;
    exp.push_back(StartBlockExpr());
    exp.push_back(CommandExpr());
    exp.push_back(EndBlockExpr());

    std::vector<std::string> code { "cmd1", "cmd2", "cmd3" };
    for (const auto& data : code) {
        for (size_t i = 0; i < exp.size(); ++i) {
            if (exp[i].interpret(ctx, data));
        }
    }
}
