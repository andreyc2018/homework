#include "command.h"
#include "interpreter.h"
#include "reporters.h"
#include "processor.h"
#include "parserstate.h"
#include "asyncqueue.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;

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
    Observer* f1 = new FileReporter("test1.txt");
    Observer* f2 = new FileReporter("test2.txt");
    Observer* c1 = new ConsoleReporter;
    Observer* c2 = new ConsoleReporter;
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

class MockProcessor : public Processor
{
    public:
        MockProcessor() : Processor(0) {}

        MOCK_METHOD0(run, void());
        MOCK_METHOD1(add_command, void(const std::string&));
        MOCK_CONST_METHOD0(block_complete, bool());
        MOCK_METHOD0(start_block, void());
};

TEST(Processor, StartingToCollectingRun)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command(_)).Times(2);
    EXPECT_CALL(proc, block_complete()).WillRepeatedly(Return(false));
    EXPECT_CALL(proc, start_block());
    Parser p(&proc);
    p.handle_token("cmd1");
    p.handle_token("cmd2");
    EXPECT_EQ("CollectingStaticBlock", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
}

TEST(Processor, StartingToExpectingToCollecting)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete()).WillRepeatedly(Return(false));
    EXPECT_CALL(proc, start_block());
    Parser p(&proc);
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state()->name());
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingDynamicBlock", p.state()->name());
    EXPECT_EQ(1, p.dynamic_level());
}

TEST(Processor, StaticBlockUntilRun)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete())
            .WillOnce(Return(false))
            .WillOnce(Return(true));
    EXPECT_CALL(proc, add_command("cmd2"));
    EXPECT_CALL(proc, run());
    EXPECT_CALL(proc, start_block());
    Parser p(&proc);
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingStaticBlock", p.state()->name());
    p.handle_token("cmd2");
    EXPECT_EQ("StartingBlock", p.state()->name());
}

TEST(Processor, DynamicBlockUntilRun)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete())
            .WillRepeatedly(Return(false));
    EXPECT_CALL(proc, add_command("cmd2"));
    EXPECT_CALL(proc, run());
    EXPECT_CALL(proc, start_block());
    Parser p(&proc);
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingDynamicBlock", p.state()->name());
    EXPECT_EQ(1, p.dynamic_level());
    p.handle_token("cmd2");
    EXPECT_EQ("CollectingDynamicBlock", p.state()->name());
    p.handle_token("}");
    EXPECT_EQ("StartingBlock", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
}

TEST(Processor, EmptyDynamicBlock)
{
    MockProcessor proc;
    Parser p(&proc);
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("}");
    EXPECT_EQ("StartingBlock", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
}

TEST(Processor, StaticInterrupted)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true));
    EXPECT_CALL(proc, add_command("cmd2"));
    EXPECT_CALL(proc, add_command("cmd3"));
    EXPECT_CALL(proc, add_command("cmd4"));
    EXPECT_CALL(proc, add_command("cmd5"));
    EXPECT_CALL(proc, add_command("cmd6"));
    EXPECT_CALL(proc, run()).Times(3);
    EXPECT_CALL(proc, start_block()).Times(3);
    Parser p(&proc);
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingStaticBlock", p.state()->name());
    p.handle_token("cmd2");
    EXPECT_EQ(0, p.dynamic_level());
    EXPECT_EQ("CollectingStaticBlock", p.state()->name());
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state()->name());
    p.handle_token("cmd3");
    EXPECT_EQ(1, p.dynamic_level());
    p.handle_token("}");
    EXPECT_EQ("StartingBlock", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("cmd4");
    EXPECT_EQ("CollectingStaticBlock", p.state()->name());
    p.handle_token("cmd5");
    EXPECT_EQ("CollectingStaticBlock", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("cmd6");
    EXPECT_EQ("StartingBlock", p.state()->name());
}

TEST(Processor, NestedBlocks)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete())
            .WillRepeatedly(Return(false));
    EXPECT_CALL(proc, add_command("cmd2"));
    EXPECT_CALL(proc, add_command("cmd3"));
    EXPECT_CALL(proc, add_command("cmd4"));
    EXPECT_CALL(proc, add_command("cmd5"));
    EXPECT_CALL(proc, run());
    EXPECT_CALL(proc, start_block());
    Parser p(&proc);
    p.handle_token("{");
    EXPECT_EQ(0, p.dynamic_level());
    EXPECT_EQ("ExpectingDynamicCommand", p.state()->name());
    p.handle_token("cmd1");
    EXPECT_EQ(1, p.dynamic_level());
    EXPECT_EQ("CollectingDynamicBlock", p.state()->name());
    p.handle_token("cmd2");
    EXPECT_EQ("CollectingDynamicBlock", p.state()->name());
    p.handle_token("{");
    EXPECT_EQ(2, p.dynamic_level());
    p.handle_token("cmd3");
    p.handle_token("cmd4");
    p.handle_token("}");
    EXPECT_EQ(1, p.dynamic_level());
    p.handle_token("cmd5");
    p.handle_token("}");
    EXPECT_EQ("StartingBlock", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
}

TEST(Processor, BreakStaticBlock)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete())
            .WillOnce(Return(false));
    EXPECT_CALL(proc, run());
    EXPECT_CALL(proc, start_block());
    Parser p(&proc);
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingStaticBlock", p.state()->name());
    p.end_of_stream();
    EXPECT_EQ("StartingBlock", p.state()->name());
}

TEST(Processor, BreakDynamicBlock)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete())
            .WillRepeatedly(Return(false));
    EXPECT_CALL(proc, start_block());
    Parser p(&proc);
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state()->name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingDynamicBlock", p.state()->name());
    EXPECT_EQ(1, p.dynamic_level());
    p.end_of_stream();
    EXPECT_EQ("CollectingDynamicBlock", p.state()->name());
    EXPECT_EQ(1, p.dynamic_level());
}

class Message
{
    public:
        Message(const std::string& msg)
            : msg_(msg)
        {
            TRACE();
        }
        ~Message()
        {
            TRACE();
        }

        std::string msg() const { return msg_; }
        void set_msg(const std::string& msg) { msg_ = msg; }

    private:
        std::string msg_;
};

