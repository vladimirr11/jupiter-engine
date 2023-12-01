#pragma once

#include "Logger.h"

namespace jupiter {

// Jupiter assertions
#define JUPITER_ASSERTION_ENABLED

#ifdef JUPITER_ASSERTION_ENABLED

/// @brief Reports an assertion failure and halt execution of the program if _errorCode_ != 0
template <typename T>
inline void checkFuncError(T errorCode, const char* func, const char* fileName, const int line) {
    if (errorCode) {
        JLOG_ERROR("{} returned error code {} at file {}, line {}", func, errorCode, __FILE__,
                   __LINE__);
        exit(EXIT_FAILURE);
    }
}

/// @brief Asserts function's return code
#define jAssertFunc(func) checkFuncError((func), #func, __FILE__, __LINE__)

/// @brief Asserts the provided expression to be true, otherwise halts the program
#define jAssertExpr(expr)                                           \
    if (expr) {                                                     \
    } else {                                                        \
        JLOG_ERROR("{} at {}, line {}", #expr, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                         \
    }

/// @brief Asserts the provided expression to be true, otherwise log error message and halts the
/// program
#define jAssertExprMsg(expr, msg)                                                     \
    if (expr) {                                                                       \
    } else {                                                                          \
        JLOG_ERROR("{} at {}, line {}; Message: {}", #expr, __FILE__, __LINE__, msg); \
        exit(EXIT_FAILURE);                                                           \
    }

#else
#define jAssertFunc(func) (func)
#define jAssertExpr(expr) expr
#define jAssertExprMsg(expr, msg) expr
#endif

}  // namespace jupiter