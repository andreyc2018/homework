#include "parser.h"
#include "parserstate.h"

Parser::Parser(int size, Processor* processor)
    : block_size_(size)
    , state_(new StartingBlock)
    , processor_(processor)
{
}

Parser::~Parser()
{
    delete state_;
}

void Parser::handle_token(const std::string& token)
{
    state_->handle(this, token);
}
