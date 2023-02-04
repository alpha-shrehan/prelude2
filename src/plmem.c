#include <include/plmem.h>

void _realloc_mem_plus1(void);

mem_t *mem;
size_t mem_count;

PL_API void
pl_mem_init(void)
{
    mem = NULL;
    mem_count = 0;
}

void _realloc_mem_plus1(void)
{
    mem = REALLOC(mem, (mem_count + 1) * sizeof(mem_t));
}

PL_API size_t
pl_mem_push_stack(mem_t v)
{
    _realloc_mem_plus1();
    mem[mem_count] = v;

    return mem_count++;
}

PL_API char
pl_mem_pop_stack(void)
{
    char c = mem[mem_count - 1].v;
    mem_count--;
    mem = REALLOC(mem, mem_count * sizeof(mem_t));

    return c;
}

PL_API void
pl_mem_add_stack(mem_t v, size_t idx)
{
    _realloc_mem_plus1();

    for (size_t i = idx; i < mem_count; i++)
        mem[i + 1] = mem[i];
    mem[idx] = v;
}

PL_API void
pl_mem_remove_stack(size_t idx)
{
    for (size_t i = idx; i < mem_count - 1; i++)
        mem[i] = mem[i + 1];
    mem = REALLOC(mem, (--mem_count) * sizeof(mem_t));
}

PL_API void
pl_mem_extend_stack(size_t n, size_t r)
{
    mem = REALLOC(mem, (mem_count + n) * sizeof(mem_t));

    while (n--)
        mem[mem_count++].v = r;
}

PL_API void
pl_mem_set_block(size_t idx, char v)
{
    mem[idx] = (mem_t){.v = v};
}

PL_API char
pl_mem_get_block(size_t idx)
{
    return mem[idx].v;
}

PL_API mem_t **
pl_mem_get_stack(void)
{
    return &mem;
}

PL_API size_t *
pl_mem_get_stack_count(void)
{
    return &mem_count;
}