#pragma once

#include <header.h>
#include <util/mem.h>
#include "plregister.h"

#define INST_MOV 1
#define INST_ADD 2
#define INST_SUB 3
#define INST_PUSH 4
#define INST_POP 5
#define INST_SECTION 6
#define INST_DBG_HALT 7

struct _pl_inst_single_arg
{
    rao_t val;

    struct
    {
        int type;
    } meta;
};

struct _pl_inst_double_arg
{
    /*
     If in future, an instruction is to be 
     implemented such that it's first argument 
     is not an RaO, then members of rao_t can be 
     used as metadata to store values.
     By convention: 
     * step is for type metadata.
     * If value to store is a 32 bit value then 
     * lval and rval can be used for upper and lower 
     * bits of the number respectively.
     */
    rao_t lval, rval;

    struct
    {
        int type;
    } meta;
};

struct _pl_inst_cmb_str
{
    /*
     * 0: Single operand register
     * 1: Double operand register
    */
    bool type;

    union
    {
        struct _pl_inst_single_arg isng;
        struct _pl_inst_double_arg idbl;
    } v;
};

typedef struct _pl_inst_single_arg inst_single_t;
typedef struct _pl_inst_double_arg inst_double_t;
typedef struct _pl_inst_cmb_str inst_t;

typedef inst_double_t pmov_t, padd_t;
typedef inst_single_t psection_t, p_dgb_halt_t;

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Create a new mov instruction
     * 
     * @param lval
     * @param rval
     * @param n_args Number of extra args
     * @param deref_lval
     * @param deref_rval
     * @return PL_API 
     */
    PL_API pmov_t pl_inst_mov_new(rao_t, rao_t, int, ...);

    /**
     * @brief Create a new add instruction
     * 
     * @param lval
     * @param rval
     * @param n_args Number of extra args
     * @param deref_lval
     * @param deref_rval
     * @return PL_API 
     */
    PL_API padd_t pl_inst_add_new(rao_t, rao_t, int, ...);

    /**
     * @brief Create a new section instruction
     * 
     * @param v
     * @return PL_API 
     */
    PL_API psection_t pl_inst_section_new(rao_t);

    /**
     * @brief Create a halt instrution (for debug)
     * 
     * @param v
     * @return PL_API 
     */
    PL_API p_dgb_halt_t pl_inst_dbg_halt_new(rao_t);

#ifdef __cplusplus
}
#endif
