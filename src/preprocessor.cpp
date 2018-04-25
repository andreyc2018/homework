#include "preprocessor.h"
#include "async_internal.h"

Preprocessor::Preprocessor(async::details::AsyncLibrary& lib)
    : library_(lib)
    , eol_re("\n")
{
}

void Preprocessor::open_processor(async::handle_t id, size_t bulk,
                                  MessageQueue& console_q, MessageQueue& file_q)
{
    auto twf = std::make_unique<ThreadWriterFactory>(console_q, file_q);
    auto p = std::make_unique<Processor>(bulk, std::move(twf));
    processors_.emplace(id, std::move(p));
}

void Preprocessor::close_processor(async::handle_t id, Counters& counters)
{
    auto it = processors_.find(id);
    if (it != processors_.end()) {
        if (processors_[id]) {
            processors_[id]->end_of_stream();
            processors_[id]->report(counters);
            processors_.erase(it);
        }
    }
}

void Preprocessor::parse_input(async::handle_t id,
                               const std::string& data)
{
    std::cout << "preproc: " << (void*)this << "\n";
    for (auto& i : data) {
        if (i != '{') {
        }
    }
    for (auto it = std::sregex_token_iterator(data.begin(), data.end(), eol_re, -1);
         it != std::sregex_token_iterator(); ++it) {
        const auto& token = *it;
        std::cout << "*it = " << token << "\n";
        if (token == "{") {
            parse_block(id, it);
        }
        else {
            library_.process_token(async::details::CommonProcessor, token);
            std::cout << "token = " << token << "\n";
        }
    }
}

void Preprocessor::parse_block(async::handle_t id,
                               std::sregex_token_iterator& it)
{
    int level = 1;
    for (++it; it != std::sregex_token_iterator(); ++it) {
        const auto& token = *it;
        library_.process_token(id, token);

        std::cout << "block:*it = " << token
                  << " level = " << level << "\n";
        if (token == "{") {
            ++level;
            continue;
        }
        if (token == "}") {
            --level;
            if (level == 0) {
                break;
            }
            continue;
        }
        std::cout << "block:token = " << token << "\n";
    }
}
