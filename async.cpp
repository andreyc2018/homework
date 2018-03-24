#include "async.h"
#include "logger.h"

namespace async {

handle_t connect(std::size_t bulk)
{
    gLogger->debug("{}: size = {}", __func__, bulk);
    return nullptr;
}

void receive(handle_t handle, const char *data, std::size_t size)
{
    gLogger->debug("{}: handle = {}, data = {}, size = {}",
                   __func__, handle, data, size);
}

void disconnect(handle_t handle)
{
    gLogger->debug("{}: handle = {}", __func__, handle);
}

}
