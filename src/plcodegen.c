#include <include/plcodegen.h>

int32_t rao_to_i32(rao_t);

PL_API pcdg_t
pl_codegen_mov(pmov_t v)
{
    /* size of 10 chars */
    pcdg_t r;
    r.v = MALLOC(
        (1 /* opcode */ +
         4 /* lval */ +
         4 /* rval */ +
         1 /* for \0 */) *
        sizeof(char));

    *r.v = OPCODE_MOV;

    /* convert RaO to 32 bit bytecode */

    int32_t lval_bc = 0, rval_bc = 0;

    lval_bc = rao_to_i32(v.lval);
    rval_bc = rao_to_i32(v.rval);

    /* add lval to bytecode */
    for (size_t i = 1; i < 5; i++)
    {
        r.v[i] = lval_bc & 0xFF; /* little endian */
        lval_bc >>= 8;
    }

    /* add rval to bytecode */
    for (size_t i = 5; i < 9; i++)
    {
        r.v[i] = rval_bc & 0xFF;
        rval_bc >>= 8;
    }

    /* Final \0 */
    r.v[9] = '\0';
    r.len_v = 9;

    return r;
}

PL_API pcdg_t 
pl_codegen_add(padd_t v)
{
    /* size of 10 chars */
    pcdg_t r;
    r.v = MALLOC(
        (1 /* opcode */ +
         4 /* lval */ +
         4 /* rval */ +
         1 /* for \0 */) *
        sizeof(char));

    *r.v = OPCODE_ADD;

    /* convert RaO to 32 bit bytecode */

    int32_t lval_bc = 0, rval_bc = 0;

    lval_bc = rao_to_i32(v.lval);
    rval_bc = rao_to_i32(v.rval);

    /* add lval to bytecode */
    for (size_t i = 1; i < 5; i++)
    {
        r.v[i] = lval_bc & 0xFF; /* little endian */
        lval_bc >>= 8;
    }

    /* add rval to bytecode */
    for (size_t i = 5; i < 9; i++)
    {
        r.v[i] = rval_bc & 0xFF;
        rval_bc >>= 8;
    }

    /* Final \0 */
    r.v[9] = '\0';
    r.len_v = 9;

    return r;
}

PL_API pcdg_t
pl_codegen_section(psection_t v)
{
    pcdg_t r;
    r.v = MALLOC((1 /* \0 */ + 1 /* opcode */ + 4 /* 32 bits */) * sizeof(char));
    *r.v = OPCODE_SECTION;

    int32_t val_bc = rao_to_i32(v.val);

    for (size_t i = 1; i <= 4; i++)
    {
        r.v[i] = val_bc & 0xFF;
        val_bc >>= 8;
    }

    r.v[5] = '\0';
    r.len_v = 5;
    
    return r;
}

int32_t
rao_to_i32(rao_t r)
{
    PL_ASSERT(r.step <= 32 &&
              r.lval <= 1024 &&
              r.rval <= 1024);

    int32_t v = 0;

    if (r.meta.sign_bit)
        v = 1 << 31;
    if (r.meta.deref)
        v |= 1 << 30;
    if (r.meta.imm[0])
        v |= 1 << 29;
    if (r.meta.imm[1])
        v |= 1 << 28;

    v |= r.step & 0x1F;
    v |= (r.rval & 0x3FF) << 5;
    v |= (r.lval & 0x3FF) << 15;

    return v;
}

PL_API int 
pl_codegen_print(pcdg_t v)
{
    for (size_t i = 0; i < v.len_v; i++)
    {
        printf("(%d) %c {%d}\t", i, v.v[i], v.v[i]);
    }
    printf("\n");

    return 0;
}

PL_API pcdg_t 
pl_codegen_dbg_halt(p_dgb_halt_t v)
{
    pcdg_t r;
    r.v = MALLOC((1 /* opcode */ + 4 /* ret code */ + 1 /* \0 */) * sizeof(char));
    *r.v = OPCODE_DBG_HALT;
    r.len_v = 5;

    int32_t val_bc = rao_to_i32(v.val);

    for (size_t i = 1; i <= 4; i++)
    {
        r.v[i] = val_bc & 0xFF;
        val_bc >>= 8;
    }

    r.v[5] = '\0';

    return r;
}
