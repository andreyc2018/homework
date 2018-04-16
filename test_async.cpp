#include "command.h"
#include "interpreter.h"
#include "processor.h"
#include "parserstate.h"
#include "logger.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <regex>

using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;

TEST(Bulk, Interpreter)
{
    expr_t open_kw = std::make_shared<term_t>("\\{");
    expr_t close_kw = std::make_shared<term_t>("\\}");
    expr_t command = std::make_shared<term_t>("^$|[^{}]+");

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
    EXPECT_TRUE(command->interpret(""));

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
    LocalWriterFactory factory;
    std::vector<ReporterUPtr> writers;
    auto f1 = factory.create_file_writer("test1.txt");
    auto f2 = factory.create_file_writer("test2.txt");
    auto c1 = factory.create_console_writer();
    auto c2 = factory.create_console_writer();
    writers.push_back(std::make_unique<Reporter>(f1));
    writers.push_back(std::make_unique<Reporter>(c1));
    writers.push_back(std::make_unique<Reporter>(c2));
    writers.push_back(std::make_unique<Reporter>(f2));

    BlockMessage msg { "hello\n", 1 };
    for (const auto& o : writers) {
        o->update(msg);
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
        MockProcessor() : Processor(0, std::make_unique<NonWriterFactory>()) {}

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
    Parser p(proc);
    p.handle_token("cmd1");
    p.handle_token("cmd2");
    EXPECT_EQ("CollectingStaticBlock", p.state().name());
    EXPECT_EQ(0, p.dynamic_level());
}

TEST(Processor, StartingToExpectingToCollecting)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete()).WillRepeatedly(Return(false));
    EXPECT_CALL(proc, start_block());
    Parser p(proc);
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state().name());
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingDynamicBlock", p.state().name());
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
    Parser p(proc);
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingStaticBlock", p.state().name());
    p.handle_token("cmd2");
    EXPECT_EQ("StartingBlock", p.state().name());
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
    Parser p(proc);
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state().name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingDynamicBlock", p.state().name());
    EXPECT_EQ(1, p.dynamic_level());
    p.handle_token("cmd2");
    EXPECT_EQ("CollectingDynamicBlock", p.state().name());
    p.handle_token("}");
    EXPECT_EQ("StartingBlock", p.state().name());
    EXPECT_EQ(0, p.dynamic_level());
}

TEST(Processor, EmptyDynamicBlock)
{
    MockProcessor proc;
    Parser p(proc);
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state().name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("}");
    EXPECT_EQ("StartingBlock", p.state().name());
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
    Parser p(proc);
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingStaticBlock", p.state().name());
    p.handle_token("cmd2");
    EXPECT_EQ(0, p.dynamic_level());
    EXPECT_EQ("CollectingStaticBlock", p.state().name());
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state().name());
    p.handle_token("cmd3");
    EXPECT_EQ(1, p.dynamic_level());
    p.handle_token("}");
    EXPECT_EQ("StartingBlock", p.state().name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("cmd4");
    EXPECT_EQ("CollectingStaticBlock", p.state().name());
    p.handle_token("cmd5");
    EXPECT_EQ("CollectingStaticBlock", p.state().name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("cmd6");
    EXPECT_EQ("StartingBlock", p.state().name());
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
    Parser p(proc);
    p.handle_token("{");
    EXPECT_EQ(0, p.dynamic_level());
    EXPECT_EQ("ExpectingDynamicCommand", p.state().name());
    p.handle_token("cmd1");
    EXPECT_EQ(1, p.dynamic_level());
    EXPECT_EQ("CollectingDynamicBlock", p.state().name());
    p.handle_token("cmd2");
    EXPECT_EQ("CollectingDynamicBlock", p.state().name());
    p.handle_token("{");
    EXPECT_EQ(2, p.dynamic_level());
    p.handle_token("cmd3");
    p.handle_token("cmd4");
    p.handle_token("}");
    EXPECT_EQ(1, p.dynamic_level());
    p.handle_token("cmd5");
    p.handle_token("}");
    EXPECT_EQ("StartingBlock", p.state().name());
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
    Parser p(proc);
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingStaticBlock", p.state().name());
    p.end_of_stream();
    EXPECT_EQ("StartingBlock", p.state().name());
}

TEST(Processor, BreakDynamicBlock)
{
    MockProcessor proc;
    EXPECT_CALL(proc, add_command("cmd1"));
    EXPECT_CALL(proc, block_complete())
            .WillRepeatedly(Return(false));
    EXPECT_CALL(proc, start_block());
    Parser p(proc);
    p.handle_token("{");
    EXPECT_EQ("ExpectingDynamicCommand", p.state().name());
    EXPECT_EQ(0, p.dynamic_level());
    p.handle_token("cmd1");
    EXPECT_EQ("CollectingDynamicBlock", p.state().name());
    EXPECT_EQ(1, p.dynamic_level());
    p.end_of_stream();
    EXPECT_EQ("CollectingDynamicBlock", p.state().name());
    EXPECT_EQ(1, p.dynamic_level());
}

TEST(Processor, ParseStringRe)
{
    std::regex eol_re("\n");
    std::vector<std::string> inputs { "1", "", "2", "\n" };
    for (const auto& input : inputs) {
        std::cout << "input: " << input << " ";
        for (auto it = std::sregex_token_iterator(input.begin(), input.end(), eol_re, -1);
             it != std::sregex_token_iterator(); ++it) {
            std::cout << ":" << *it << ":\n";
        }
    }
}

bool end_of_token(char l)
{
    return (l == '\n' || l == '{' || l == '}');
}

bool build_token(std::string& token, char l)
{
    if (!end_of_token(l)) {
        token.push_back(l);
        return false;
    }
    return true;
}

TEST(Processor, BuildToken)
{
    Processor p(3, std::make_unique<NonWriterFactory>());
    std::string input;
    std::string token;

    for (auto& i : input) {
        if (build_token(token, i)) {
            break;
        }
    }

    EXPECT_TRUE(token.empty());

    input = "1234";

    for (auto& i : input) {
        if (build_token(token, i)) {
            break;
        }
    }

    EXPECT_EQ("1234", token);

    input = "1{2";

    for (auto& i : input) {
        if (build_token(token, i)) {
            break;
        }
    }

    EXPECT_EQ("12341", token);

    input = "12}34";

    for (auto& i : input) {
        if (build_token(token, i)) {
            break;
        }
    }

    EXPECT_EQ("1234112", token);

    input = "123\n4";

    for (auto& i : input) {
        if (build_token(token, i)) {
            break;
        }
    }

    EXPECT_EQ("1234112123", token);
}

void string_info(const std::string& data)
{
    std::cout << "capacity = " << data.capacity() << ", "
              << "size = " << data.size() << "\n";
}

TEST(String, Reserve)
{
    std::string data;
    for (int i = 1; i < 32; i += 2) {
        string_info(data);
        data.push_back('0');
        data.push_back('1');
    }
}
