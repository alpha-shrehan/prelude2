#include <include/plinst.h>

PL_API pmov_t 
pl_inst_mov_new(
    rao_t lval,
    rao_t rval,
    int n_args,
    ...)
{
    va_list vl;
    va_start(vl, n_args);

    pmov_t m;
    m.meta.type = INST_MOV;
    m.lval = lval;
    m.rval = rval;

    if (n_args)
    {
        m.lval.meta.deref = va_arg(vl, int);
        n_args--;
    }

    if (n_args)
    {
        m.rval.meta.deref = va_arg(vl, int);
        n_args--;
    }

    va_end(vl);
    return m;
}

PL_API padd_t 
pl_inst_add_new(
    rao_t lval,
    rao_t rval,
    int n_args,
    ...)
{
    va_list vl;
    va_start(vl, n_args);

    padd_t m;
    m.meta.type = INST_ADD;
    m.lval = lval;
    m.rval = rval;

    if (n_args)
    {
        m.lval.meta.deref = va_arg(vl, int);
        n_args--;
    }

    if (n_args)
    {
        m.rval.meta.deref = va_arg(vl, int);
        n_args--;
    }

    va_end(vl);
    return m;
}

PL_API psection_t 
pl_inst_section_new(rao_t v)
{
    psection_t r;
    r.meta.type = INST_SECTION;
    r.val = v;

    return r;
}

PL_API p_dgb_halt_t 
pl_inst_dbg_halt_new(rao_t v)
{
    p_dgb_halt_t r;
    r.meta.type = INST_DBG_HALT;
    r.val = v;

    return r;
}