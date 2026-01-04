#include "bsp_common.h"

#define SRAM_START 0x20000000U
#define SRAM_SIZE (20U * 1024U) // 20 KB

extern uint32_t _estack;

extern int main(void);
extern void System_Init(void);

void RAM_Init (void) __attribute__((naked));

/**********************************************************************************************************************
 * @brief Init RAM area for MCU.
 *
 * @return None
 *********************************************************************************************************************/
void RAM_Init (void)
{
	/* Set stack pointer */
    __asm volatile("MSR MSP, %0"::"r"(&_estack));

    /* Init SRAM */
    __asm volatile("MOV R1, %0"::"r"(SRAM_SIZE-4U));
    __asm volatile("MOV R2, %0"::"r"(SRAM_START));
    __asm volatile("ADD R1, R1, R2");
    __asm volatile("MOVS R3, #0xAA");
    __asm volatile("             \
    .L_loop_data:           \n\t \
        CMP R2, R1          \n\t \
        BGE _exit           \n\t \
        STR R3, [R2]        \n\t \
        ADD R2, R2, #1      \n\t \
        B .L_loop_data      \n\t \
    _exit:                  \n\t \
        ");

    /* End the state stackless (naked attribute)*/
    __asm volatile("POP {R4-R11}");
    __asm volatile("BX LR");
}

/**********************************************************************************************************************
 * @brief The start function of MCU.
 *
 * @return None
 *********************************************************************************************************************/
void Reset_Handler(void)
{
    RAM_Init();

    System_Init();

    /* Call main() */
    main();
}
