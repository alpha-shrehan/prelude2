#include "mem.h"

PL_API void *
pl_util_malloc(size_t sz)
{
    if (!sz)
        return NULL;
    
    void *ptr = malloc(sz);
    PL_ASSERT(ptr != NULL);

    return ptr;
}

PL_API void *
pl_util_realloc(void *ptr, size_t sz)
{
    void *np = realloc(ptr, sz);

    return np;
}

PL_API void
pl_util_free(void *ptr)
{
    free(ptr);
}