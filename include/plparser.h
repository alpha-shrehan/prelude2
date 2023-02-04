#pragma once

#include <header.h>
#include <util/mem.h>
#include "plinst.h"

/* blocks to leave for system routines */
#define PL_ALGN_SYSR 10
/* default stack width */
#define PL_ALGN_STACK_WIDTH 5

struct _pl_parser_str
{
    inst_t *vals;
    size_t size_val;
};

typedef struct _pl_parser_str plparser_t;

#ifdef __cplusplus
extern "C"
{
#endif

    PL_API void pl_parser_preprocess(plparser_t);

    PL_API void pl_parser_exec(plparser_t);

#ifdef __cplusplus
}
#endif
