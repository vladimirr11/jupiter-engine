#pragma once

#include "Logger.h"

namespace jupiter {

// Jupiter assertions
#define JUPITER_ASSERTION_ENABLED

#ifdef JUPITER_ASSERTION_ENABLED

/// @brief Reports an assertion failure and halt execution of the program if _errorCode_ != 0
template <typename T>
inline void checkFuncReturnCode(T result, const char* func, const char* fileName, const int32 line) {
    if (result) {
    } else {
        JLOG_ERROR("{} returned error code {} at file {}, line {}", func, result, __FILE__,
                   __LINE__);
        exit(EXIT_FAILURE);
    }
}

/// @brief Asserts function's return code
#define jAssertFunc(func) checkFuncReturnCode((func), #func, __FILE__, __LINE__)

/// @brief Asserts the provided expression to be true, otherwise log error message and halts the
/// program
#define jAssertExpr(expr)                                           \
    if (expr) {                                                     \
    } else {                                                        \
        JLOG_ERROR("{} at {}, line {}", #expr, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                         \
    }

/// @brief Asserts that the provided pointer is not null
#define jAssertPtr(ptr)                                                       \
    if (ptr) {                                                                \
    } else {                                                                  \
        JLOG_ERROR("{} == nullptr at {}, line {}", #ptr, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                                   \
    }

#else
#define jAssertFunc(func) (func)
#define jAssertExpr(expr) expr
#define jAssertPtr(ptr) ptr
#endif

}  // namespace jupiter