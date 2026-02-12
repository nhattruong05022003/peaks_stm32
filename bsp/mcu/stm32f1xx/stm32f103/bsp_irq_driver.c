#include "bsp_irq.h"

/* Table contains pointer to control struct of module */
void *bsp_irq_context_table[BSP_TOTAL_IRQ];

/* Array contains exception priority registers' address */
uint8_t* bsp_exception_priority_regs[] =
{
    (uint8_t*)&(SCB->SHPR1),
    (uint8_t*)&(SCB->SHPR1) + 1U,
    (uint8_t*)&(SCB->SHPR1) + 2U,
    (uint8_t*)&(SCB->SHPR3),
    (uint8_t*)&(SCB->SHPR2) + 3U,
    (uint8_t*)&(SCB->SHPR3) + 2U,
    (uint8_t*)&(SCB->SHPR3) + 3U
};
