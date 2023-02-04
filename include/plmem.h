#pragma once

#include <header.h>
#include <util/mem.h>

#define _PL_ALLOC_INTERVAL 64

typedef struct _pl_mem_blk
{
    char v;
} mem_t;

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Initialize prelude memory.
     * Initializes `mem_count' to 0 and `mem' to NULL
     * 
     * @return PL_API 
     */
    PL_API void pl_mem_init(void);

    /**
     * @brief Push memory block to stack
     * 
     * @param v
     * @return size_t Index in stack
     */
    PL_API size_t pl_mem_push_stack(mem_t);

    /**
     * @brief Remove last element from memory.
     * 
     * @return Return last element
     */
    PL_API char pl_mem_pop_stack(void);
    
    /**
     * @brief Add element to particular index (0-indexed)
     * 
     * @param v
     * @param idx
     * @return PL_API 
     */
    PL_API void pl_mem_add_stack(mem_t, size_t);

    /**
     * @brief Remove block at particular index. (0-indexed)
     * 
     * @param idx
     * @return PL_API 
     */
    PL_API void pl_mem_remove_stack(size_t);

    /**
     * @brief Extend stack by n elements and fill each with r.
     * 
     * @param n
     * @param r
     * @return PL_API 
     */
    PL_API void pl_mem_extend_stack(size_t, size_t);
    
    /**
     * @brief Set block.
     * 
     * @param idx
     * @param v
     * @return PL_API 
     */
    PL_API void pl_mem_set_block(size_t, char);

    /**
     * @brief Get block.
     * 
     * @param idx
     * @return char
     */
    PL_API char pl_mem_get_block(size_t);

    /**
     * @brief Get stack
     * 
     * @return PL_API** 
     */
    PL_API mem_t **pl_mem_get_stack(void);

    /**
     * @brief Get stack count
     * 
     * @return PL_API* 
     */
    PL_API size_t *pl_mem_get_stack_count(void);

#ifdef __cplusplus
}
#endif
