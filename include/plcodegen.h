#pragma once

#include <header.h>
#include <util/mem.h>
#include "plinst.h"
#include "opcode.h"

typedef struct
{
    char *v;
    size_t len_v;
} pcdg_t;

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Generate mov instruction bytecode
     * 
     * @param v
     * @return pcdg_t
     */
    PL_API pcdg_t pl_codegen_mov(pmov_t);

    /**
     * @brief Generate add instruction bytecode
     * 
     * @param v
     * @return PL_API 
     */
    PL_API pcdg_t pl_codegen_add(padd_t);

    /**
     * @brief Generate section instruction bytecode
     * 
     * @param v
     * @return PL_API 
     */
    PL_API pcdg_t pl_codegen_section(psection_t);

    /**
     * @brief Print codegen
     * 
     * @param v
     * @return PL_API 
     */
    PL_API int pl_codegen_print(pcdg_t);

    /**
     * @brief Generate dbg_halt instruction bytecode
     * 
     * @param v
     * @return PL_API 
     */
    PL_API pcdg_t pl_codegen_dbg_halt(p_dgb_halt_t);

#ifdef __cplusplus
}
#endif
