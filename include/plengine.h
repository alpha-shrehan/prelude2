#pragma once

#include <header.h>
#include "opcode.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Use the global environment and 
     * execute instructions.
     * For alpha version, CS contains start of 
     * code section and ES marks the end of it
     * 
     * @return PL_API 
     */
    PL_API int pl_engine_init(void);

#ifdef __cplusplus
}
#endif
