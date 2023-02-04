#pragma once

#include "../header.h"

#define MALLOC(X) pl_util_malloc(X)
#define REALLOC(X, Y) pl_util_realloc(X, Y)
#define FREE(X) pl_util_free(X)

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief malloc(...)
     * 
     * @param sz
     * @return PL_API* 
     */
    PL_API void *pl_util_malloc(size_t);

    /**
     * @brief realloc(...)
     * 
     * @param ptr
     * @param sz
     * @return PL_API* 
     */
    PL_API void *pl_util_realloc(void *, size_t);

    /**
     * @brief free(...)
     * 
     * @param ptr
     * @return PL_API 
     */
    PL_API void pl_util_free(void *);

#ifdef __cplusplus
}
#endif
