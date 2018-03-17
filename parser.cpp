#include "parser.h"
#include "parserstate.h"
#include "processor.h"
#include "logger.h"

Parser::Parser(int size, Processor* processor)
    : block_size_(size)
    , level_(0)
    , state_(new StartingBlock)
    , processor_(processor)
    , open_block_(std::make_shared<term_t>("\\{"))
    , close_block_(std::make_shared<term_t>("\\}"))
    , command_(std::make_shared<term_t>("[^{}]+"))
    , start_block_(std::make_shared<start_block_t>(open_block_, command_))
    , end_block_(std::make_shared<end_block_t>(open_block_, command_, close_block_))
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

void Parser::set_state(ParserState* state)
{
    LOG() << "from state: " << state_->name();
    delete state_;
    state_ = state;
    LOG() << "to state: " << state_->name();
}

void Parser::add_command(const std::string& token)
{
    processor_->add_command(token);
}

bool Parser::block_complete() const
{
    if (level_ == 0 && processor_->block_complete()) {
        return true;
    }
    return false;
}

void Parser::notify_run()
{
    processor_->run();
}
