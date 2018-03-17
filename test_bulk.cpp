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
    expr_t open_block = std::make_shared<term_t>("\\{");
    expr_t close_block = std::make_shared<term_t>("\\}");
    expr_t command = std::make_shared<term_t>("[^{}]+");

    EXPECT_TRUE(open_block->interpret("{"));
    EXPECT_TRUE(!open_block->interpret("{{"));
    EXPECT_TRUE(!open_block->interpret("}"));
    EXPECT_TRUE(!open_block->interpret("zxcv"));
    EXPECT_TRUE(close_block->interpret("}"));
    EXPECT_TRUE(!close_block->interpret("}}"));
    EXPECT_TRUE(!close_block->interpret("{"));
    EXPECT_TRUE(!close_block->interpret("world"));
    EXPECT_TRUE(!command->interpret("{"));
    EXPECT_TRUE(command->interpret("hello"));

    expr_t start_block = std::make_shared<start_block_t>(open_block, command);
    EXPECT_TRUE(start_block->interpret("{"));
    EXPECT_TRUE(!start_block->interpret("{{"));
    EXPECT_TRUE(!start_block->interpret("}"));
    EXPECT_TRUE(start_block->interpret("qwerty"));

    expr_t end_block = std::make_shared<end_block_t>(open_block, command, close_block);
    EXPECT_TRUE(end_block->interpret("{"));
    EXPECT_TRUE(end_block->interpret("}"));
    EXPECT_TRUE(end_block->interpret("asdfg"));
}
