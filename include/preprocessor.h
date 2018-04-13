#pragma once

#include "async.h"
#include <string>

namespace async {
namespace details {

class AsyncLibrary;

}}

class Preprocessor
{
    public:
        Preprocessor();

        virtual void parse_input(const std::string& data,
                                 async::handle_t handle,
                                 async::details::AsyncLibrary& library);
};
