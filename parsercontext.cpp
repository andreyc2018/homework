#include "parsercontext.h"

ParserContext::ParserContext(int size)
        : block_size_(size)
        , level_(0)
        , state_(std::make_unique<StartingBlock>())
{}
