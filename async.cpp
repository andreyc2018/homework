#include "async.h"
#include "async_internal.h"
#include "logger.h"

namespace async {

details::AsyncLibraryUPtr library;

handle_t connect(std::size_t bulk)
{
    if (bulk < 1) {
        return details::InvalidHandle;
    }
    if (!library) {
        library = std::make_unique<details::AsyncLibrary>();
    }

    return library->open_processor(bulk);
}

void receive(handle_t handle, const char *data, std::size_t size)
{
    gLogger->info("h = {}, invalid = {}", handle, details::InvalidHandle);
    if (!library || handle == details::InvalidHandle || data == nullptr || size == 0) {
        return;
    }
    std::string token(data, size);
    library->process_input(handle, token);
}

void disconnect(handle_t handle)
{
    if (!library || handle == details::InvalidHandle) {
        return;
    }
    library->close_processor(handle);
}

}
