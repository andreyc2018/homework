#pragma once

#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
#include <spdlog/spdlog.h>

using LoggerPtr = std::shared_ptr<spdlog::logger>;
