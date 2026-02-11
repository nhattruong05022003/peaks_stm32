#ifndef _BSP_FEATURE_H_
#define _BSP_FEATURE_H_

/* SRAM start address*/
#define SRAM_START 0x20000000U

/* SRAM size */
#define SRAM_SIZE (20U * 1024U) // 20 KB

/* Stack region size */
#define BSP_STACK_SIZE (0x400U)

/* Heap region size */
#define BSP_HEAP_SIZE (0x400U)

#define BSP_FEATURE_MPU_IS_AVAILABLE (0x00U)

#endif
