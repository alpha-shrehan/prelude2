#pragma once

#include <header.h>
#include "plregister.h"
#include "plinst.h"

struct _pl_dump_str
{
    int32_t byte_code;
    int type;

    union
    {
        pmov_t imov;
        padd_t iadd;
    } v;
    
};

typedef struct _pl_dump_str pldump_t;


#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Decompile byte code
     * 
     * @param v
     * @return PL_API 
     */
    PL_API pldump_t pl_dump_code_single(char *);

#ifdef __cplusplus
}
#endif
