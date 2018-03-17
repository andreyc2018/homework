#include "command.h"
#include "interpreter.h"
#include "observers.h"
#include "processor.h"
#include "parser.h"
#include "logger.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(Bulk, Interpreter)
{
    expr_t open_kw = std::make_shared<term_t>("\\{");
    expr_t close_kw = std::make_shared<term_t>("\\}");
    expr_t command = std::make_shared<term_t>("[^{}]+");

    EXPECT_TRUE(open_kw->interpret("{"));
    EXPECT_TRUE(!open_kw->interpret("{{"));
    EXPECT_TRUE(!open_kw->interpret("}"));
    EXPECT_TRUE(!open_kw->interpret("zxcv"));
    EXPECT_TRUE(close_kw->interpret("}"));
    EXPECT_TRUE(!close_kw->interpret("}}"));
    EXPECT_TRUE(!close_kw->interpret("{"));
    EXPECT_TRUE(!close_kw->interpret("world"));
    EXPECT_TRUE(!command->interpret("{"));
    EXPECT_TRUE(command->interpret("hello"));

    expr_t start_block = std::make_shared<start_block_t>(open_kw, command);
    EXPECT_TRUE(start_block->interpret("{"));
    EXPECT_TRUE(!start_block->interpret("{{"));
    EXPECT_TRUE(!start_block->interpret("}"));
    EXPECT_TRUE(start_block->interpret("qwerty"));

    expr_t end_block = std::make_shared<end_block_t>(open_kw, command, close_kw);
    EXPECT_TRUE(end_block->interpret("{"));
    EXPECT_TRUE(end_block->interpret("}"));
    EXPECT_TRUE(end_block->interpret("asdfg"));
}

TEST(Bulk, Block)
{
    auto b1 = Block::create();

    auto c1 = Command::create("c1");
    b1.add_command(c1);

    auto c2 = Command::create("c2");
    b1.add_command(c2);

    std::stringstream ss;
    b1.run(ss);

    std::cout << ss.str();

    EXPECT_EQ("bulk: c1, c2\n", ss.str());
}

TEST(Bulk, Observer)
{
    std::vector<Observer*> writers;
    Observer* f1 = new FileOut("test1.txt");
    Observer* f2 = new FileOut("test2.txt");
    Observer* c1 = new ConsoleOut;
    Observer* c2 = new ConsoleOut;
    writers.push_back(f1);
    writers.push_back(c1);
    writers.push_back(c2);
    writers.push_back(f2);
    for (const auto& o : writers) {
        o->update("hello\n");
    }

    for (auto& o : writers) {
        delete o;
    }

    std::fstream file1("test1.txt");
    std::string result;
    file1 >> result;
    EXPECT_EQ("hello", result);
    unlink("test1.txt");

    std::fstream file2("test1.txt");
    file2 >> result;
    EXPECT_EQ("hello", result);
    unlink("test2.txt");
}

class MockProcessor
{
    public:
        MOCK_METHOD0(run, void());
        MOCK_METHOD1(add_command, void(const std::string&));
        MOCK_METHOD0(block_complete, void());
        MOCK_METHOD0(start_block, void());
};

TEST(Bulk, Parser)
{
}
