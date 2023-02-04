#include <include/plparser.h>
#include <include/plmem.h>
#include <include/plregister.h>
#include <include/plcodegen.h>

PL_API void
pl_parser_preprocess(plparser_t ctx)
{
    pl_mem_extend_stack(PL_ALGN_SYSR, 0);
    pl_reg_set_registerSmart(PL_REG_CS, *pl_mem_get_stack_count());
}

PL_API void
pl_parser_exec(plparser_t ctx)
{
    for (size_t i = 0; i < ctx.size_val; i++)
    {
        inst_t curr = ctx.vals[i];
        pcdg_t r;

        if (curr.type)
        {
            /* double argument instruction */
            inst_double_t d = curr.v.idbl;

            switch (d.meta.type)
            {
            case INST_MOV:
                r = pl_codegen_mov((pmov_t)d);
                break;
            case INST_ADD:
                r = pl_codegen_add((padd_t) d);
                break;
            case INST_SUB:
                /* r = pl_codegen_sub((psub_t) d); */
                break;

            default:
                break;
            }
        }
        else
        {
            /* single argument instruction */
            inst_single_t d = curr.v.isng;

            switch (d.meta.type)
            {
            case INST_SECTION:
            {
                r = pl_codegen_section((psection_t)d);

                if (!(d.val.lval + d.val.rval * d.val.step)) /* code section */
                {
                    pl_reg_set_registerSmart(PL_REG_CS, *pl_mem_get_stack_count());
                }
                else if (d.val.lval + d.val.rval * d.val.step == 1)
                {
                    pl_reg_set_registerSmart(PL_REG_DS, *pl_mem_get_stack_count());
                }
            }
            break;
            case INST_PUSH:
                /* r = pl_codegen_push((ppush_t) d); */
                break;
            case INST_POP:
                /* r = pl_codegen_pop((ppop_t) d); */
                break;
            case INST_DBG_HALT:
                r = pl_codegen_dbg_halt((p_dgb_halt_t)d);
                break;

            default:
                break;
            }
        }

        // pl_codegen_print(r);

        while (r.len_v--)
        {
            pl_mem_push_stack((mem_t){
                .v = *r.v++});
        }
    }

    pl_mem_extend_stack(PL_ALGN_STACK_WIDTH, 0);
}