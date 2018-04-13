#include "async.h"
#include "async_internal.h"
#include "logger.h"
#include <mutex>

namespace async {

std::mutex mutex;

handle_t connect(std::size_t bulk)
{
    if (bulk < 1) {
        return details::InvalidHandle;
    }

    std::lock_guard<std::mutex> g(mutex);
    return details::Async::instance().open_processor(bulk);
}

void receive(handle_t handle, const char *data, std::size_t size)
{
    if (handle == details::InvalidHandle || data == nullptr || size == 0) {
        return;
    }
    std::string data_str(data, size);
    details::Async::instance().process_input(handle, data_str);
}

void disconnect(handle_t handle)
{
    if (handle == details::InvalidHandle) {
        return;
    }
    std::lock_guard<std::mutex> g(mutex);
    details::Async::instance().close_processor(handle);
}

}
