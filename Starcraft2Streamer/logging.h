#pragma once

#include <sstream>

#define _log(x) {{ std::stringstream ssl; ssl << __FUNCTION__ << ":" << __LINE__ << ": " << x << std::endl; std::cerr << ssl.str(); }}

#define log_error(x) {_log(x)}
#define log_info(x) {_log(x)}

#define LOG_LVL_DEBUG
#ifdef LOG_LVL_DEBUG
#define log_debug(x) {_log(x)}
#else
#define log_debug(x) {}
#endif //LOG_LVL_DEBUG

//#define LOG_LVL_TRACE
#ifdef LOG_LVL_TRACE
#define log_trace(x) {_log(x)}
#else
#define log_trace(x) {}
#endif //LOG_LVL_TRACE



const char* const LOG_FORMAT_TIME = "%Y-%m-%d %H:%M:%S";

constexpr char* last_n_chars(const char* str, const int n) {
	return "todo";
}