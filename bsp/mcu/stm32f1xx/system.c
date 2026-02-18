#include "bsp_api.h"
#include "bsp_feature.h"

#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _sbss;
extern uint32_t _edata;
extern uint32_t _ebss;
extern uint32_t _la_data;
extern uint32_t _sheap;
extern uint32_t _eheap;

extern uint32_t SystemClockHz;

/* Stack region */
uint32_t bsp_main_stack[BSP_STACK_SIZE >> 2] __attribute__((section(".stack")));

#if (BSP_HEAP_SIZE > 0)
/* Heap heap */
uint32_t bsp_main_heap[BSP_STACK_SIZE >> 2] __attribute__((section(".heap")));
#endif

static void clock_init(void);

void System_Init(void);

/* Core exception handlers */ 
void Reset_Handler(void);
void NMI_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)        __attribute__((weak, alias("Default_Handler")));

/* External interrupt handlers (IRQ0 to IRQ66) */ 
void WWDG_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 0
void PVD_IRQHandler(void)                  __attribute__((weak, alias("Default_Handler")));  // 1
void TAMPER_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));  // 2
void RTC_IRQHandler(void)                  __attribute__((weak, alias("Default_Handler")));  // 3
void FLASH_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));  // 4
void RCC_IRQHandler(void)                  __attribute__((weak, alias("Default_Handler")));  // 5
void EXTI0_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));  // 6
void EXTI1_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));  // 7
void EXTI2_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));  // 8
void EXTI3_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));  // 9
void EXTI4_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));  // 10
void DMA_IRQHandler(void)                  __attribute__((weak, alias("Default_Handler")));  // 11,12,13,14,15,16,17,56,57,58,59
void ADC1_2_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));  // 18
void USB_HP_CAN_TX_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));  // 19
void USB_LP_CAN_RX0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));  // 20
void CAN_RX1_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 21
void CAN_SCE_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 22
void EXTI9_5_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 23
void TIM1_BRK_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));  // 24
void TIM1_UP_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 25
void TIM1_TRG_COM_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));  // 26
void TIM1_CC_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 27
void TIM2_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 28
void TIM3_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 29
void TIM4_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 30
void I2C1_EV_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 31
void I2C1_ER_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 32
void I2C2_EV_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 33
void I2C2_ER_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 34
void SPI_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));   // 35
void SPI_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));   // 36
void USART1_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));  // 37
void USART2_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));  // 38
void USART3_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));  // 39
void EXTI15_10_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));  // 40
void RTCAlarm_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));  // 41
void USBWakeup_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));  // 42
void TIM8_BRK_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));  // 43
void TIM8_UP_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 44
void TIM8_TRG_COM_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));  // 45
void TIM8_CC_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));  // 46
void ADC3_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 47
void FSMC_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 48
void SDIO_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 49
void TIM5_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 50
void SPI3_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 51
void UART4_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));  // 52
void UART5_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));  // 53
void TIM6_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 54
void TIM7_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));  // 55

uint32_t exception_vectors[] __attribute__((section(".exception_vector"))) = 
{
    STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,   // MemManage Handler
    (uint32_t)&BusFault_Handler,    // Bus Fault Handler
    (uint32_t)&UsageFault_Handler,  // Usage Fault Handler
    0u, 0u, 0u, 0u,                 // Reserved (0x1C to 0x28)
    (uint32_t)&SVC_Handler,         // SVCall
    (uint32_t)&DebugMon_Handler,    // Debug Monitor
    0u,                             // Reserved
    (uint32_t)&PendSV_Handler,      // PendSV
    (uint32_t)&SysTick_Handler,     // SysTick
};
uint32_t irq_vectors[] __attribute__((section(".irq_vector"))) =
{
    // External Interrupts (IRQ0 - IRQ66)
    (uint32_t)&WWDG_IRQHandler,         // 0
    (uint32_t)&PVD_IRQHandler,          // 1
    (uint32_t)&TAMPER_IRQHandler,       // 2
    (uint32_t)&RTC_IRQHandler,          // 3
    (uint32_t)&FLASH_IRQHandler,        // 4
    (uint32_t)&RCC_IRQHandler,          // 5
    (uint32_t)&EXTI0_IRQHandler,        // 6
    (uint32_t)&EXTI1_IRQHandler,        // 7
    (uint32_t)&EXTI2_IRQHandler,        // 8
    (uint32_t)&EXTI3_IRQHandler,        // 9
    (uint32_t)&EXTI4_IRQHandler,        // 10
    (uint32_t)&DMA_IRQHandler,          // 11
    (uint32_t)&DMA_IRQHandler,          // 12
    (uint32_t)&DMA_IRQHandler,          // 13
    (uint32_t)&DMA_IRQHandler,          // 14
    (uint32_t)&DMA_IRQHandler,          // 15
    (uint32_t)&DMA_IRQHandler,          // 16
    (uint32_t)&DMA_IRQHandler,          // 17
    (uint32_t)&ADC1_2_IRQHandler,       // 18
    (uint32_t)&USB_HP_CAN_TX_IRQHandler,// 19
    (uint32_t)&USB_LP_CAN_RX0_IRQHandler,// 20
    (uint32_t)&CAN_RX1_IRQHandler,      // 21
    (uint32_t)&CAN_SCE_IRQHandler,      // 22
    (uint32_t)&EXTI9_5_IRQHandler,      // 23
    (uint32_t)&TIM1_BRK_IRQHandler,     // 24
    (uint32_t)&TIM1_UP_IRQHandler,      // 25
    (uint32_t)&TIM1_TRG_COM_IRQHandler, // 26
    (uint32_t)&TIM1_CC_IRQHandler,      // 27
    (uint32_t)&TIM2_IRQHandler,         // 28
    (uint32_t)&TIM3_IRQHandler,         // 29
    (uint32_t)&TIM4_IRQHandler,         // 30
    (uint32_t)&I2C1_EV_IRQHandler,      // 31
    (uint32_t)&I2C1_ER_IRQHandler,      // 32
    (uint32_t)&I2C2_EV_IRQHandler,      // 33
    (uint32_t)&I2C2_ER_IRQHandler,      // 34
    (uint32_t)&SPI_IRQHandler,          // 35
    (uint32_t)&SPI_IRQHandler,          // 36
    (uint32_t)&USART1_IRQHandler,       // 37
    (uint32_t)&USART2_IRQHandler,       // 38
    (uint32_t)&USART3_IRQHandler,       // 39
    (uint32_t)&EXTI15_10_IRQHandler,    // 40
    (uint32_t)&RTCAlarm_IRQHandler,     // 41
    (uint32_t)&USBWakeup_IRQHandler,    // 42
    (uint32_t)&TIM8_BRK_IRQHandler,     // 43
    (uint32_t)&TIM8_UP_IRQHandler,      // 44
    (uint32_t)&TIM8_TRG_COM_IRQHandler, // 45
    (uint32_t)&TIM8_CC_IRQHandler,      // 46
    (uint32_t)&ADC3_IRQHandler,         // 47
    (uint32_t)&FSMC_IRQHandler,         // 48
    (uint32_t)&SDIO_IRQHandler,         // 49
    (uint32_t)&TIM5_IRQHandler,         // 50
    (uint32_t)&SPI3_IRQHandler,         // 51
    (uint32_t)&UART4_IRQHandler,        // 52
    (uint32_t)&UART5_IRQHandler,        // 53
    (uint32_t)&TIM6_IRQHandler,         // 54
    (uint32_t)&TIM7_IRQHandler,         // 55
#if (BSP_FEATURE_DMA2_IS_AVAILABLE)
    (uint32_t)&DMA_IRQHandler,          // 56
    (uint32_t)&DMA_IRQHandler,          // 57
    (uint32_t)&DMA_IRQHandler,          // 58
    (uint32_t)&DMA_IRQHandler           // 59
#endif
};

/**********************************************************************************************************************
 * @brief Perform copying bss and data section for MCU, init function of std library and set up clock.
 *
 * @return None
 *********************************************************************************************************************/
void System_Init(void)
{
    /* Copy .data section to SRAM */
    uint32_t size = (uint32_t)(&_edata) - (uint32_t)(&_sdata);

    uint8_t *pDest = (uint8_t *)(&_sdata); // sram
    uint8_t *pSrc = (uint8_t *)(&_la_data); // flash

    for(uint32_t i = 0; i < size; i++)
    {
        *pDest++ = *pSrc++;
    }

    /* Init the .bss section to zero in SRAM */ 
    size = (uint32_t)(&_ebss) - (uint32_t)(&_sbss);
    pDest = (uint8_t *)(&_sbss);
    for(uint32_t i = 0; i < size; i++)
    {
        *pDest++ = 0;
    }

    /* Init the .heap section to zero in SRAM */ 
    size = (uint32_t)(&_eheap) - (uint32_t)(&_sheap);
    pDest = (uint8_t *)(&_sheap);
    for(uint32_t i = 0; i < size; i++)
    {
        *pDest++ = 0;
    }

    /* Call init function of std library */ 

    /* Set up clock */
    clock_init(); // Set up 72 MHz system clock
}

void Default_Handler(void)
{
    while(1)
    {
        __asm__ volatile ("nop");
    }
}

#define FLASH_BASE      0x40022000
#define FLASH_ACR       (*(volatile uint32_t*)(FLASH_BASE + 0x00))

/**********************************************************************************************************************
 * @brief Configurate clock (AHB) 72 MHz using PLL (HSE 8 MHz ×9)
 *
 * @return None
 *********************************************************************************************************************/
static void clock_init(void) {
    // Enable HSE
    RCC->CR_b.HSEON |= (1U);
    while (!(RCC->CR_b.HSERDY & (1U)));

    // Flash latency
    FLASH_ACR |= (1 << 4); // PRFTBE
    FLASH_ACR &= ~(0x7);
    FLASH_ACR |= 0x2; // 2 wait states

    // PLL config: source = HSE, multiplier = x9
    RCC->CFGR_b.PLLMUL &= ~(0x0FU);
    RCC->CFGR_b.PLLMUL |= (0x07U); // MUL9 = 72MHz
    RCC->CFGR_b.PLLSRC |= (0x01U); // HSE as source

    // AHB = 72MHz, APB1 = 36MHz, APB2 = 72MHz
    RCC->CFGR_b.HPRE &= ~(0x0FU);    // AHB = CLKPLL/1
    RCC->CFGR_b.PPRE1 |= (0x04U);    // APB1 = CLKPLL/2
    RCC->CFGR_b.PPRE2 &= ~(0x07U); // APB2 = CLKPLL/1

    // Enable PLL
    RCC->CR_b.PLLON |= 0x01U;
    while(!((RCC->CR_b.PLLRDY) & (0x01U)));

    // Select PLL as system clock
    RCC->CFGR_b.SW &= ~(0x03U);
    RCC->CFGR_b.SW |= (0x02U);
    while ((RCC->CFGR_b.SWS & (0x03U)) != (0x02U));

    SystemClockHz = 72000000U;

    /* Enable clock for modules */
    BSP_ModuleStandby_EnableAll();
}
