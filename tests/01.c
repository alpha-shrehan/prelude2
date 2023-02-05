#include <prelude2.h>

#define TEST(X) test##X()

void test1()
{
    mem_t *m = *pl_mem_get_stack();
    size_t s = *pl_mem_get_stack_count();

    pl_reg_set_register(PL_REG_EAX, 100392, 32);
    pl_reg_set_register(PL_REG_EBX, 6118, 32);
    pl_reg_set_register(PL_REG_ECX, 2024, 32);

    // for (size_t i = 0; i < s; i++)
    // {
    //     printf("(%d) [%c] (%d)\n", i, m[i].v, m[i].v);
    // }

    printf("%d\n", pl_reg_get_register(PL_REG_EAX));
    printf("%d\n", pl_reg_get_register(PL_REG_EBX));
    printf("%d\n", pl_reg_get_register(PL_REG_ECX));
}

void test2()
{
    pmov_t p = pl_inst_mov_new(
        pl_reg_make_rao(PL_REG_EAX, 10, 5),
        pl_reg_make_rao(PL_REG_EBX, 20, 13),
        0);

    char *v = pl_codegen_mov(p).v;
    pldump_t pd = pl_dump_code_single(v);

    printf("%s\n%s\n", pl_reg_rao_stdout_repr(pd.v.imov.lval), pl_reg_rao_stdout_repr(pd.v.imov.rval));
}

void test3()
{
    pl_reg_set_registerSmart(PL_REG_EBX, 10);

    mem_t *m = *pl_mem_get_stack();
    size_t *s = pl_mem_get_stack_count();

    /**
     * section text
     * mov eax, ebx 
     */
    inst_t p[] = {
        (inst_t){
            0,
            .v = {
                .isng = 
                    pl_inst_section_new(
                        pl_reg_make_rao(0, 0, 0))}},
        (inst_t){
            1, 
            .v = {
                .idbl =
                    pl_inst_mov_new(
                        pl_reg_make_rao_withU(PL_REG_EAX, 0, 0, 8), 
                        pl_reg_make_rao_withU(PL_REG_EBX, 0, 0, 8), 0)}},
        (inst_t){
            1,
            .v = {
                .idbl =
                    pl_inst_add_new(
                        pl_reg_make_rao_withU(PL_REG_EAX, 0, 0, 8),
                        pl_reg_make_rao_withU(PL_REG_EBX, 0, 0, 8), 0)}},
        (inst_t) {
            1,
            .v = {
                .idbl = 
                    pl_inst_mov_new(
                        pl_reg_make_rao_withU(PL_REG_ECX, 0, 0, 8),
                        pl_reg_make_rao_withU(PL_REG_R7, 0, 0, 8), 0)}},
        (inst_t) {
            0,
            .v = {
                .isng = 
                    pl_inst_dbg_halt_new(
                        pl_reg_make_rao(0, 0, 0))}},
        (inst_t) {
            0,
            .v = {
                .isng = 
                    pl_inst_section_new(
                        pl_reg_make_rao(1, 0, 0))}}};
    
    plparser_t ctx;
    ctx.size_val = sizeof(p) / sizeof(inst_t);
    ctx.vals = p;

    // printf("%s\n", pl_reg_rao_stdout_repr(p[1].v.idbl.rval));

    // pl_parser_preprocess(ctx);
    pl_parser_exec(ctx);
    pl_engine_init();

    // for (size_t i = PL_REG_R7 + 32; i < *s; i++)
    // {
    //     printf("(%d) [%c] (%d)\n", i, m[i].v, m[i].v);
    // }

    printf("%d\n", pl_reg_get_register(PL_REG_EAX));
    printf("%d\n", pl_reg_get_register(PL_REG_ECX));
}

int main(int argc, char const *argv[])
{
    pl_mem_init();
    pl_reg_init();

    TEST(3);

    return printf("Program ended.\n") && 0;
}