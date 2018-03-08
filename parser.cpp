#include "parser.h"
#include "parserstate.h"

Parser::Parser()
    : state_(new StartingBlock)
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
