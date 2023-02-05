#include <include/plengine.h>
#include <include/plinst.h>
#include <include/plmem.h>
#include <include/plparser.h>
#include <include/plregister.h>

PL_API int
pl_engine_init(void)
{
    int16_t cs = pl_reg_get_register(PL_REG_CS);
    bool state = true;
    int32_t ret_code = 0;

    pl_reg_set_registerSmart(PL_REG_R7, cs);

    while (state)
    {
        size_t curr_block = pl_reg_get_register(PL_REG_R7);
        char opcode = pl_mem_get_block(curr_block);

        switch (opcode)
        {
        case OPCODE_MOV:
        {
            /**
             * Get the next 8 blocks.
             * First 4 blocks are lval.
             * Last 4 blocks are rval
             *
             */

            char *blks = MALLOC(8 * sizeof(char));

            for (size_t j = 0; j < 8; j++)
                blks[j] = pl_mem_get_block(curr_block + j + 1);

            int32_t lval = 0, rval = 0;

            // for (size_t j = 0; j < 8; j++)
            // {
            //     printf("%d (0x%x)\n", blks[j], blks[j]);
            // }

            for (size_t j = 0; j < 4; j++)
                lval |= ((int32_t)blks[j] & 0xFF) << (8 * j);

            for (size_t j = 4; j < 8; j++)
                rval |= ((int32_t)blks[j] & 0xFF) << (8 * (j - 4));

            // printf("%d\n", rval);

            rao_t rao_lv = pl_reg_rao_i32_to_rao(lval),
                  rao_rv = pl_reg_rao_i32_to_rao(rval);

            if (rao_lv.meta.sign_bit)
                rao_lv.step = -rao_lv.step;

            if (rao_rv.meta.sign_bit)
                rao_rv.step = -rao_rv.step;

            // printf("%s\n%s\n",
            //        pl_reg_rao_stdout_repr(rao_lv),
            //        pl_reg_rao_stdout_repr(rao_rv));

            if (rao_lv.meta.imm[0])
                rao_lv.lval = pl_mem_get_block(rao_lv.lval);

            if (rao_lv.meta.imm[1])
                rao_lv.rval = pl_mem_get_block(rao_lv.rval);

            if (rao_rv.meta.imm[0])
                rao_rv.lval = pl_mem_get_block(rao_rv.lval);

            if (rao_rv.meta.imm[1])
                rao_rv.rval = pl_mem_get_block(rao_rv.rval);

            int32_t dest_offs = rao_lv.lval + (rao_lv.rval * rao_lv.step),
                    src_offs = rao_rv.lval + (rao_rv.rval * rao_rv.step);

            /* Mov instruction gets the memory value of arguments first and assigns accordingly. */
            /* get value */
            size_t pres_srcoffs = src_offs;
            src_offs = pl_mem_get_block(src_offs) & 0xFF;
            pres_srcoffs++;

            int32_t sz = 0;

            if (dest_offs < PL_REG_R7 + 32)
            {
                if ((dest_offs >= PL_REG_EAX && dest_offs <= (PL_REG_EDI + 32)) ||
                    (dest_offs >= PL_REG_R0 && dest_offs <= (PL_REG_R7 + 32)))
                    sz = 32;

                else if ((dest_offs >= PL_REG_CS && dest_offs <= (PL_REG_SS + 16)) ||
                         (dest_offs >= PL_REG_AX && dest_offs <= (PL_REG_DI + 16)))
                    sz = 16;

                else if ((dest_offs >= PL_REG_AL && dest_offs <= (PL_REG_DH + 8)))
                    sz = 8;
            }
            else
            {
                sz = (rao_rv.meta.sizes[0] * 32) +
                     (rao_rv.meta.sizes[1] * 16) +
                     (rao_rv.meta.sizes[2] * 8);
            }

            sz -= 8; /* one equivalent block is already stored */

            int _c = 1;
            while (sz > 0)
            {
                src_offs |= ((int32_t)pl_mem_get_block(pres_srcoffs) & 0xFF) << (8 * _c++);
                pres_srcoffs++;
                sz -= 8;
            }

            if (rao_lv.meta.deref)
                dest_offs = pl_mem_get_block(dest_offs);

            if (rao_rv.meta.deref)
                src_offs = pl_mem_get_block(src_offs);

            if (dest_offs < PL_REG_R7 + 32)
                pl_reg_set_registerSmart(dest_offs, src_offs);
            else
            {
                /* TODO: here */
            }

            FREE(blks);

            pl_reg_set_registerSmart(PL_REG_R7, curr_block + 8);
            goto end;
        }
        break;

        case OPCODE_ADD:
        {
            /**
             * Get the next 8 blocks.
             * First 4 blocks are lval.
             * Last 4 blocks are rval
             *
             */

            char *blks = MALLOC(8 * sizeof(char));

            for (size_t j = 0; j < 8; j++)
                blks[j] = pl_mem_get_block(curr_block + j + 1);

            int32_t lval = 0, rval = 0;

            // for (size_t j = 0; j < 8; j++)
            // {
            //     printf("%d (0x%x)\n", blks[j], blks[j]);
            // }

            for (size_t j = 0; j < 4; j++)
                lval |= ((int32_t)blks[j] & 0xFF) << (8 * j);

            for (size_t j = 4; j < 8; j++)
                rval |= ((int32_t)blks[j] & 0xFF) << (8 * (j - 4));

            // printf("%d\n", rval);

            rao_t rao_lv = pl_reg_rao_i32_to_rao(lval),
                  rao_rv = pl_reg_rao_i32_to_rao(rval);

            if (rao_lv.meta.sign_bit)
                rao_lv.step = -rao_lv.step;

            if (rao_rv.meta.sign_bit)
                rao_rv.step = -rao_rv.step;

            // printf("%s\n%s\n",
            //        pl_reg_rao_stdout_repr(rao_lv),
            //        pl_reg_rao_stdout_repr(rao_rv));

            if (rao_lv.meta.imm[0])
                rao_lv.lval = pl_mem_get_block(rao_lv.lval);

            if (rao_lv.meta.imm[1])
                rao_lv.rval = pl_mem_get_block(rao_lv.rval);

            if (rao_rv.meta.imm[0])
                rao_rv.lval = pl_mem_get_block(rao_rv.lval);

            if (rao_rv.meta.imm[1])
                rao_rv.rval = pl_mem_get_block(rao_rv.rval);

            int32_t dest_offs = rao_lv.lval + (rao_lv.rval * rao_lv.step),
                    src_offs = rao_rv.lval + (rao_rv.rval * rao_rv.step);

            /* Mov instruction gets the memory value of arguments first and assigns accordingly. */
            /* get value */
            size_t pres_srcoffs = src_offs;
            src_offs = pl_mem_get_block(src_offs) & 0xFF;
            pres_srcoffs++;

            int32_t sz = 0;

            if (dest_offs < PL_REG_R7 + 32)
            {
                if ((dest_offs >= PL_REG_EAX && dest_offs <= (PL_REG_EDI + 32)) ||
                    (dest_offs >= PL_REG_R0 && dest_offs <= (PL_REG_R7 + 32)))
                    sz = 32;

                else if ((dest_offs >= PL_REG_CS && dest_offs <= (PL_REG_SS + 16)) ||
                         (dest_offs >= PL_REG_AX && dest_offs <= (PL_REG_DI + 16)))
                    sz = 16;

                else if ((dest_offs >= PL_REG_AL && dest_offs <= (PL_REG_DH + 8)))
                    sz = 8;
            }
            else
            {
                sz = (rao_rv.meta.sizes[0] * 32) +
                     (rao_rv.meta.sizes[1] * 16) +
                     (rao_rv.meta.sizes[2] * 8);
            }

            sz -= 8; /* one equivalent block is already stored */

            int _c = 1;
            while (sz > 0)
            {
                src_offs |= ((int32_t)pl_mem_get_block(pres_srcoffs) & 0xFF) << (8 * _c++);
                pres_srcoffs++;
                sz -= 8;
            }

            if (rao_lv.meta.deref)
                dest_offs = pl_mem_get_block(dest_offs);

            if (rao_rv.meta.deref)
                src_offs = pl_mem_get_block(src_offs);

            if (dest_offs < PL_REG_R7 + 32)
                pl_reg_set_registerSmart(dest_offs, pl_mem_get_block(dest_offs) + src_offs);
            else
            {
                /* TODO: here */
            }

            FREE(blks);

            pl_reg_set_registerSmart(PL_REG_R7, curr_block + 8);
            goto end;
        }
        break;

        case OPCODE_DBG_HALT:
        {
            char *blks = MALLOC(4 * sizeof(char));

            for (size_t j = 0; j < 4; j++)
                blks[j] = pl_mem_get_block(curr_block + j + 1);

            int32_t rv = 0;

            for (size_t j = 0; j < 4; j++)
                rv |= ((int32_t)blks[j]) << (8 * j);
            ret_code = rv;

            FREE(blks);

            state = false;
        }
        break;

        default:
            break;
        }

        pl_reg_set_registerSmart(PL_REG_R7, curr_block + 1);

    end:;
    }

    return ret_code;
}