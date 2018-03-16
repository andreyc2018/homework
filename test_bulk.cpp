#include "command.h"
#include "interpreter.h"
#include "observers.h"
#define BOOST_TEST_MODULE Bulk
#include <boost/test/unit_test.hpp>
#include <iostream>

using term_t = TerminalExpression;
using expr_t = ExpressionPtr;
using start_block_t = OrExpression<expr_t, expr_t>;
using end_block_t = OrExpression<expr_t, expr_t, expr_t>;

BOOST_AUTO_TEST_CASE(interpreter_tree)
{
    expr_t open_block = std::make_shared<term_t>("\\{");
    expr_t close_block = std::make_shared<term_t>("\\}");
    expr_t command = std::make_shared<term_t>("[^{}]+");

    BOOST_CHECK(open_block->interpret("{"));
    BOOST_CHECK(!open_block->interpret("{{"));
    BOOST_CHECK(!open_block->interpret("}"));
    BOOST_CHECK(!open_block->interpret("zxcv"));
    BOOST_CHECK(close_block->interpret("}"));
    BOOST_CHECK(!close_block->interpret("}}"));
    BOOST_CHECK(!close_block->interpret("{"));
    BOOST_CHECK(!close_block->interpret("world"));
    BOOST_CHECK(!command->interpret("{"));
    BOOST_CHECK(command->interpret("hello"));

    expr_t start_block = std::make_shared<start_block_t>(open_block, command);
    BOOST_CHECK(start_block->interpret("{"));
    BOOST_CHECK(!start_block->interpret("{{"));
    BOOST_CHECK(!start_block->interpret("}"));
    BOOST_CHECK(start_block->interpret("qwerty"));

    expr_t end_block = std::make_shared<end_block_t>(open_block, command, close_block);
    BOOST_CHECK(end_block->interpret("{"));
    BOOST_CHECK(end_block->interpret("}"));
    BOOST_CHECK(end_block->interpret("asdfg"));
}

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

BOOST_AUTO_TEST_CASE(observer)
{
    std::vector<Observer*> writers;
    Observer* f1 = new FileOut("test.txt");
    Observer* c1 = new ConsoleOut;
    writers.push_back(f1);
    writers.push_back(c1);
    for (const auto& o : writers) {
        o->update("hello");
    }

    for (auto& o : writers) {
        delete o;
    }

    std::fstream file("test.txt");
    std::string result;
    file >> result;
    BOOST_CHECK_EQUAL("hello", result);
}

#if 0
bool run_and_log(ParserContext& ctx, Expression& exp,
                 const std::string& data, int counter)
{
    bool rc = exp.interpret(ctx, data);
    std::cout << counter << ". input: " << data
            << " interpret: " << exp.name()
            << " state: " << ctx.state_name()
            << " rc: " << std::boolalpha << rc << "\n";
    return rc;
}

BOOST_AUTO_TEST_CASE(starting_state)
{
    TRACE();
    ParserContext ctx(1);
    StartBlockExpr exp;

    // Change state to CollectingBlock
    std::string data = "cmd1";
    bool rc = run_and_log(ctx, exp, data, 1);
    BOOST_CHECK(rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));

    // No state change with StartBlockExpr and state CollectingBlock
    rc = run_and_log(ctx, exp, data, 2);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
}

BOOST_AUTO_TEST_CASE(starting_state_1)
{
    ParserContext ctx(1);
    StartBlockExpr exp;

    std::string data = "{";
    bool rc = run_and_log(ctx, exp, data, 1);
    BOOST_CHECK(rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
    rc = run_and_log(ctx, exp, "cmd2", 2);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
    rc = run_and_log(ctx, exp, "{", 3);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
    rc = run_and_log(ctx, exp, "}", 4);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
}

BOOST_AUTO_TEST_CASE(starting_state_2)
{
    ParserContext ctx(1);
    StartBlockExpr exp;

    std::string data = "}";
    bool rc = run_and_log(ctx, exp, data, 1);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("StartingBlock"));
    rc = run_and_log(ctx, exp, "cmd2", 2);
    BOOST_CHECK(rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
}

BOOST_AUTO_TEST_CASE(collecting_state)
{
    ParserContext ctx(1);
    StartBlockExpr exp;

    // Change state to CollectingBlock
    std::string data = "cmd1";
    bool rc = run_and_log(ctx, exp, data, 1);
    BOOST_CHECK(rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));

    // Block size is one, same command and CommandExpr:
    // change state to DoneBlock
    CommandExpr cmd_exp;
    rc = run_and_log(ctx, cmd_exp, data, 2);
    BOOST_CHECK(rc);
    BOOST_CHECK(ctx.in_state("DoneBlock"));
}

BOOST_AUTO_TEST_CASE(collecting_state_2)
{
    ParserContext ctx(1);
    StartBlockExpr exp;

    // Change state to CollectingBlock
    std::string data = "{";
    bool rc = run_and_log(ctx, exp, data, 1);
    BOOST_CHECK(rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));

    // Block size is one, same command "{" and CommandExpr:
    // state stay the same
    CommandExpr cmd_exp;
    rc = run_and_log(ctx, cmd_exp, data, 2);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
    BOOST_CHECK_EQUAL(1, ctx.level());

    // Block size is one, new command "cmd1" and CommandExpr:
    // state stay the same
    rc = run_and_log(ctx, cmd_exp, "cmd1", 3);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
    BOOST_CHECK_EQUAL(1, ctx.level());

    // Block size is one, new command "cmd2" and CommandExpr:
    // state stay the same, block grows
    rc = run_and_log(ctx, cmd_exp, "cmd2", 4);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
    BOOST_CHECK_EQUAL(1, ctx.level());
    BOOST_CHECK_EQUAL(2, ctx.block_size());

    // Block size is one, new command "}" and CommandExpr:
    // state stay the same, block grows
    rc = run_and_log(ctx, cmd_exp, "}", 5);
    BOOST_CHECK(!rc);
    BOOST_CHECK(ctx.in_state("CollectingBlock"));
    BOOST_CHECK_EQUAL(1, ctx.level());
    BOOST_CHECK_EQUAL(2, ctx.block_size());

    EndBlockExpr done_exp;
    // Block size is one, new command "}" and CommandExpr:
    // state stay the same, block grows
    rc = run_and_log(ctx, done_exp, "}", 5);
    BOOST_CHECK(rc);
    BOOST_CHECK(ctx.in_state("DoneBlock"));
    BOOST_CHECK_EQUAL(0, ctx.level());
    BOOST_CHECK_EQUAL(2, ctx.block_size());
}

BOOST_AUTO_TEST_CASE(intrepreter)
{
    ParserContext ctx(2);
    std::vector<ExpressionUPtr> exp;
    exp.emplace_back(new StartBlockExpr());
    exp.emplace_back(new CommandExpr());
    exp.emplace_back(new EndBlockExpr());

    std::vector<std::string> code { "cmd1", "cmd2", "cmd3" };
    for (const auto& data : code) {
        for (size_t i = 0; i < exp.size(); ++i) {
            std::string prev_state = ctx.state_name();
            exp[i]->interpret(ctx, data);
            std::cout << " :: input: " << data
                      << " interpret: " << exp[i]->name()
                      << " state: " << prev_state
                      << " --> "
                      << ctx.state_name() << "\n";
        }
    }
}

#endif
