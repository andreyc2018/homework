#include "parser.h"
#include "parserstate.h"
#include "processor.h"
#include "logger.h"

Parser::Parser(int size, Processor* processor)
    : block_size_(size)
    , dynamic_block_(false)
    , state_(new StartingBlock)
    , processor_(processor)
    , open_kw_(std::make_shared<term_t>("\\{"))
    , close_kw_(std::make_shared<term_t>("\\}"))
    , command_(std::make_shared<term_t>("[^{}]+"))
//    , start_block_(std::make_shared<start_block_t>(open_kw_, command_))
//    , end_block_(std::make_shared<end_block_t>(open_kw_, command_, close_kw_))
{
}

Parser::~Parser()
{
    delete state_;
}

void Parser::handle_token(const std::string& token)
{
    while(state_->handle(this, token) == ParserState::Result::Continue);
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
    if (!dynamic_block() && processor_->block_complete()) {
        return true;
    }
    return false;
}

void Parser::start_block()
{
    processor_->start_block();
}

void Parser::notify_run()
{
    processor_->run();
}
