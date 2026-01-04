#ifndef _BSP_COMMON_H_
#define _BSP_COMMON_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/* Device register */
#include "stm32f1xxx.h"

/* Macro definition */
#define IRQn_t int
#define __STATIC_INLINE         static inline
#define __STATIC_ALWAYS_INLINE  __attribute__((always_inline)) static inline

#endif
