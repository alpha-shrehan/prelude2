#pragma once

#include <header.h>

/* 32-bit register memory indexes */
#define PL_REG_EAX 0
#define PL_REG_EBX 32
#define PL_REG_ECX 64
#define PL_REG_EDX 96
#define PL_REG_ESP 128
#define PL_REG_EBP 160
#define PL_REG_ESI 192
#define PL_REG_EDI 224

/* 16-bit segment register memory indexes */
#define PL_REG_CS 256
#define PL_REG_DS 288
#define PL_REG_ES 320
#define PL_REG_FS 352
#define PL_REG_GS 384
#define PL_REG_SS 416

/* 32-bit R registers */
#define PL_REG_R0 448
#define PL_REG_R1 480
#define PL_REG_R2 512
#define PL_REG_R3 544
#define PL_REG_R4 576
#define PL_REG_R5 608
#define PL_REG_R6 640
#define PL_REG_R7 672

/* 16-bit storage registers */
#define PL_REG_AX 16
#define PL_REG_BX 48
#define PL_REG_CX 80
#define PL_REG_DX 112
#define PL_REG_SP 144
#define PL_REG_BP 176
#define PL_REG_SI 208
#define PL_REG_DI 240

/* 8-bit storage registers */
#define PL_REG_AL 24
#define PL_REG_AH 16
#define PL_REG_BL 56
#define PL_REG_BH 48
#define PL_REG_CL 88
#define PL_REG_CH 80
#define PL_REG_DL 120
#define PL_REG_DH 112

struct _pl_reg_operand_str
{
    int16_t lval, rval;
    int8_t step;

    struct
    {
        bool sign_bit;
        bool deref;
    } meta;
};

typedef struct _pl_reg_operand_str rao_t;

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Add registers to memory
     * 
     * @return PL_API 
     */
    PL_API void pl_reg_init(void);

    /**
     * @brief Set register to particular value
     * 
     * @param reg
     * @param val
     * @param size 
     * @return PL_API 
     */
    PL_API void pl_reg_set_register(size_t, int32_t, size_t);

    /**
     * @brief Use additional checks to determine size of value
     * 
     * @param reg
     * @param val
     * @return PL_API 
     */
    PL_API void pl_reg_set_registerSmart(size_t, size_t);

    /**
     * @brief Get register value
     * 
     * @param reg
     * @return PL_API 
     */
    PL_API int32_t pl_reg_get_register(size_t);

    /**
     * @brief Make RaO from data
     * 
     * @param lval
     * @param rval
     * @param step
     * @return rao_t
     */
    PL_API rao_t pl_reg_make_rao(int16_t, int16_t, int8_t);

    /**
     * @brief RaO.__str__()
     * 
     * @param v
     * @return char *
     */
    PL_API char *pl_reg_rao_stdout_repr(rao_t);

    /**
     * @brief rao codegen to rao_t
     * 
     * @param v
     * @return PL_API 
     */
    PL_API rao_t pl_reg_rao_i32_to_rao(int32_t);

#ifdef __cplusplus
}
#endif
