#include <include/pldump.h>

PL_API pldump_t
pl_dump_code_single(char *v)
{
    pldump_t r;
    int8_t opcode = v[0];

    r.type = opcode;
    switch (r.type)
    {
    case INST_MOV:
    {
        r.v.imov.meta.type = INST_MOV;
        int32_t lval = 0, rval = 0;

        for (size_t i = 1; i <= 4; i++)
        {
            lval |= (v[i] & 0xFF) << (8 * (i - 1));
        }

        for (size_t i = 5; i <= 8; i++)
        {
            rval |= (v[i] & 0xFF) << (8 * (i - 1));
        }

        r.v.imov.lval.meta.sign_bit = (lval >> 31) & 0x1;
        r.v.imov.rval.meta.sign_bit = (rval >> 31) & 0x1;

        r.v.imov.lval.lval = (lval >> 15) & 0x3FF;
        r.v.imov.lval.rval = (lval >> 5) & 0x3FF;
        r.v.imov.lval.step = lval & 0x1F;

        r.v.imov.rval.lval = (rval >> 15) & 0x3FF;
        r.v.imov.rval.rval = (rval >> 5) & 0x3FF;
        r.v.imov.rval.step = rval & 0x1F;
    }
    break;
    case INST_ADD:
    {
        r.v.iadd.meta.type = INST_ADD;
        int32_t lval = 0, rval = 0;

        for (size_t i = 1; i <= 4; i++)
        {
            lval |= (v[i] & 0xFF) << (8 * (i - 1));
        }

        for (size_t i = 5; i <= 8; i++)
        {
            rval |= (v[i] & 0xFF) << (8 * (i - 1));
        }

        r.v.iadd.lval.meta.sign_bit = (lval >> 31) & 0x1;
        r.v.iadd.rval.meta.sign_bit = (rval >> 31) & 0x1;

        r.v.iadd.lval.lval = (lval >> 15) & 0x3FF;
        r.v.iadd.lval.rval = (lval >> 5) & 0x3FF;
        r.v.iadd.lval.step = lval & 0x1F;

        r.v.iadd.rval.lval = (rval >> 15) & 0x3FF;
        r.v.iadd.rval.rval = (rval >> 5) & 0x3FF;
        r.v.iadd.rval.step = rval & 0x1F;
    }
    break;

    default:
        break;
    }

    return r;
}