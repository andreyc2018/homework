#include "async_internal.h"

using namespace async;
using namespace async::details;

AsyncLibrary::AsyncLibrary()
    : console_q()
    , console(console_q)
    , file_q()
    , file_1(file_q, 1)
    , file_2(file_q, 2)
{
    console.run();
    file_1.run();
    file_2.run();
}

AsyncLibrary::~AsyncLibrary()
{
    Message msg { MessageId::EndOfStream, "", { "", 0 } };
    console.queue().push(msg);
    file_1.queue().push(msg);
    file_2.queue().push(msg);

    console.wait();
    file_1.wait();
    file_2.wait();
}
