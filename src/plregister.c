#include <include/plregister.h>
#include <include/plmem.h>

PL_API void
pl_reg_init(void)
{
    /* Index of last register + 32 to accomodate
        last register
     */
    pl_mem_extend_stack(PL_REG_R7 + 32, 0);
}

PL_API void
pl_reg_set_register(
    size_t reg,
    int32_t val,
    size_t size)
{
    /* size must be a multiple of 8 */
    PL_ASSERT(!(size % 8));

    /*
     * We need to fill (size / 8) blocks.
     * Loop till size is 0 and reduce size by 8
     *  at each iteration.
     */
    while (size > 0)
    {
        /* take 8 bits from val */
        char byte1 = val & 0xFF;

        /* set cuttent char block (capacity 8) bits to byte1 */
        pl_mem_set_block(reg, byte1);

        /* get the next 8 bits */
        val >>= 8;
        /* Size reduces by 8 */
        size -= 8;
        /* New val will be assigned to next 8 bits (next char block) */
        reg++;
    }
}

PL_API void
pl_reg_set_registerSmart(size_t reg, size_t val)
{
    int32_t sz = 0;

    if ((reg >= PL_REG_EAX && reg <= (PL_REG_EDI + 32)) ||
        (reg >= PL_REG_R0 && reg <= (PL_REG_R7 + 32)))
        sz = 32;

    else if ((reg >= PL_REG_CS && reg <= (PL_REG_SS + 16)) ||
             (reg >= PL_REG_AX && reg <= (PL_REG_DI + 16)))
        sz = 16;

    else if ((reg >= PL_REG_AL && reg <= (PL_REG_DH + 8)))
        sz = 8;
    
    PL_ASSERT(sz);
    pl_reg_set_register(reg, val, sz);
}

PL_API int32_t 
pl_reg_get_register(size_t reg)
{
    /* Determines the size of register by comparing it with offsets */
    int32_t sz = 0;

    if ((reg >= PL_REG_EAX && reg <= (PL_REG_EDI + 32)) ||
        (reg >= PL_REG_R0 && reg <= (PL_REG_R7 + 32)))
        sz = 32;

    else if ((reg >= PL_REG_CS && reg <= (PL_REG_SS + 16)) ||
             (reg >= PL_REG_AX && reg <= (PL_REG_DI + 16)))
        sz = 16;

    else if ((reg >= PL_REG_AL && reg <= (PL_REG_DH + 8)))
        sz = 8;
    
    /* sz must be a natural multiple of 8 */
    PL_ASSERT(sz && !(sz % 8) && sz <= 32);

    /* value to return */
    int32_t vl = 0;
    /* maximum 4 blocks (32 bits) for value
       value builder */
    unsigned char v_comps[4] = {0, 0, 0, 0};
    /* reverse filler */
    int r = 4;

    /* will execute sz/8 times */
    while (sz)
    {
        /* reverse add to value builder */
        v_comps[--r] = pl_mem_get_block(reg);
        /* next block */
        reg++;
        /* 8 bits received */
        sz -= 8;
    }

    /* convert value builder to 32 bit value */
    for (size_t i = 0; i < 4; i++)
        vl |= ((int32_t)v_comps[i] << (8 * (3 - i)));

    return vl;
}

PL_API rao_t 
pl_reg_make_rao(
    int16_t lval, 
    int16_t rval, 
    int8_t step)
{
    /* constructor for rao_t */
    rao_t r;
    r.lval = lval;
    r.rval = rval;
    r.step = abs(step);

    r.meta.sign_bit = step < 0;
    r.meta.deref = false;

    return r;
}

PL_API char *
pl_reg_rao_stdout_repr(rao_t v)
{
    char *res = MALLOC(64 * sizeof(char)); /* arbitrary buffer */

    sprintf(res, "%d + %d * %d", v.lval, v.rval, v.meta.sign_bit ? -v.step: v.step);

    return res;
}

PL_API rao_t 
pl_reg_rao_i32_to_rao(int32_t v)
{
    rao_t r;
    r.lval = 0;
    r.meta.sign_bit = (v >> 31) & 0x1;
    r.meta.deref = (v >> 30) & 0x1;
    r.rval = 0;
    r.step = 0;

    r.step = v & 0x1F;
    r.rval = (v >> 5) & 0x3FF;
    r.lval = (v >> 15) & 0x3FF;

    return r;
}