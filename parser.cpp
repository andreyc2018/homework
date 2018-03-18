#include "parser.h"
#include "parserstate.h"
#include "processor.h"
#include "logger.h"

Parser::Parser(Processor* processor)
    : dynamic_level_(0)
    , state_(new StartingBlock)
    , processor_(processor)
    , open_kw_(std::make_shared<term_t>("\\{"))
    , close_kw_(std::make_shared<term_t>("\\}"))
    , command_(std::make_shared<term_t>("[^{}]+"))
{
}

Parser::~Parser()
{
    delete state_;
}

void Parser::handle_token(const std::string& token)
{
    LOG() << "Processing: " << token << "\n";
    while (state_->handle(this, token) == ParserState::Result::Continue) {}
}

void Parser::set_state(ParserState* state)
{
    LOG() << "from state: " << state_->name();
    delete state_;
    state_ = state;
    LOG() << " to state: " << state_->name() << "\n";
}

void Parser::add_command(const std::string& token)
{
    processor_->add_command(token);
}

bool Parser::block_complete() const
{
    return processor_->block_complete();
}

void Parser::start_block()
{
    processor_->start_block();
}

void Parser::notify_run()
{
    processor_->run();
}
