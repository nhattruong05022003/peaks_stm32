#ifndef _STM32F1XXX_H_
#define _STM32F1XXX_H_

#include <stdint.h>
#include "cortex_m3.h"
/**********************************************************************************************************************
 *                                                      RCC
 **********************************************************************************************************************/
typedef struct RCC_Type_t
{   
    /* Clock control registe (CR) 0x00 */
    union
    {
        volatile uint32_t CR;
        struct
        {
            volatile uint32_t HSION : 1;
            volatile uint32_t HSIRDY : 1;
            volatile const uint32_t : 1;
            volatile uint32_t HSITRIM : 5;
            volatile uint32_t HSICAL : 8;
            volatile uint32_t HSEON : 1;
            volatile uint32_t HSERDY : 1;
            volatile uint32_t HSEBYP : 1;
            volatile uint32_t CSSON : 1;
            volatile const uint32_t : 4;
            volatile uint32_t PLLON : 1;
            volatile uint32_t PLLRDY : 1;
            volatile uint32_t PLL2ON : 1;
            volatile uint32_t PLL2RDY : 1;
            volatile uint32_t PLL3ON : 1;
            volatile uint32_t PLL3RDY : 1;
            volatile const uint32_t : 2;
        } CR_b;
    };

    /* Clock configuration registe (CFGR) 0x04 */
    union
    {
        volatile uint32_t CFGR;
        struct
        {
            volatile uint32_t SW : 2;
            volatile uint32_t SWS : 2;
            volatile uint32_t HPRE : 4;
            volatile uint32_t PPRE1 : 3;
            volatile uint32_t PPRE2 : 3;
            volatile uint32_t ADCPRE : 2;
            volatile uint32_t PLLSRC : 1;
            volatile uint32_t PLLXTPRE : 1;
            volatile uint32_t PLLMUL : 4;
            volatile uint32_t OTGFSPRE : 1;
            volatile const uint32_t : 1;
            volatile uint32_t MCO : 4;
            volatile const uint32_t : 4;
        } CFGR_b;
    };

    /* Clock interrupt register (CIR) 0x08 */
    union
    {
        volatile uint32_t CIR;
        struct
        {
            volatile uint32_t LSIRDYF : 1;
            volatile uint32_t LSERDYF : 1;
            volatile uint32_t HSIRDYF : 1;
            volatile uint32_t HSERDYF : 1;
            volatile uint32_t PLLRDYF : 1;
            volatile uint32_t PLL2RDYF : 1;
            volatile uint32_t PLL3RDYF : 1;
            volatile uint32_t CSSF : 1;
            volatile uint32_t LSIRDYIE : 1;
            volatile uint32_t LSERDYIE : 1;
            volatile uint32_t HSIRDYIE : 1;
            volatile uint32_t HSERDYIE : 1;
            volatile uint32_t PLLRDYIE : 1;
            volatile uint32_t PLL2RDYIE : 1;
            volatile uint32_t PLL3RDYIE : 1;
            volatile const uint32_t : 1;
            volatile uint32_t LSIRDYC : 1;
            volatile uint32_t LSERDYC : 1;
            volatile uint32_t HSIRDYC : 1;
            volatile uint32_t HSERDYC : 1;
            volatile uint32_t PLLRDYC : 1;
            volatile uint32_t PLL2RDYC : 1;
            volatile uint32_t PLL3RDYC : 1;
            volatile uint32_t CSSC : 1;
            volatile const uint32_t : 8;
        } CIR_b;
    };


    /* APB2 peripheral reset register (APB2RSTR) 0x0C */
    union
    {
        volatile uint32_t APB2RSTR;
        struct
        {
            volatile uint32_t AFIORST : 1;
            volatile const uint32_t  : 1;
            volatile uint32_t IOPARST : 1;
            volatile uint32_t IOPBRST : 1;
            volatile uint32_t IOPCRST : 1;
            volatile uint32_t IOPDRST : 1;
            volatile uint32_t IOPERST : 1;
            volatile const uint32_t : 2;
            volatile uint32_t ADC1RST : 1;
            volatile uint32_t ADC2RST : 1;
            volatile uint32_t TIM1RST : 1;
            volatile uint32_t SPI1RST : 1;
            volatile const uint32_t REVERSED2 : 1;
            volatile uint32_t USART1RST : 1;
            volatile const uint32_t : 17;
        } APB2RSTR_b;
    };

    /* APB1 peripheral reset register (APB1RSTR) 0x10 */
    union
    {
        volatile uint32_t APB1RSTR;
        struct
        {
            volatile uint32_t AFITIM2RSTORST : 1;
            volatile uint32_t TIM3RST : 1;
            volatile uint32_t TIM4RST : 1;
            volatile uint32_t TIM5RST : 1;
            volatile uint32_t TIM6RST : 1;
            volatile uint32_t TIM7RST : 1;
            volatile const uint32_t  : 5;
            volatile uint32_t WWDGRST : 1;
            volatile const uint32_t  : 2;
            volatile uint32_t SPI2RST : 1;
            volatile uint32_t SPI3RST : 1;
            volatile const uint32_t REVERSED2 : 1;
            volatile uint32_t USART2RST : 1;
            volatile uint32_t USART3RST : 1;
            volatile uint32_t UART4RST : 1;
            volatile uint32_t UART5RST : 1;
            volatile uint32_t I2C1RST : 1;
            volatile uint32_t I2C2RST : 1;
            volatile const uint32_t : 2;
            volatile uint32_t CAN1RST : 1;
            volatile uint32_t CAN2RST : 1;
            volatile uint32_t BKPRST : 1;
            volatile uint32_t PWRRST : 1;
            volatile uint32_t DACRST : 1;
            volatile const uint32_t : 2;
        } APB1RSTR_b;
    };

    /* AHB Peripheral Clock enable register (AHBENR) 0x14 */
    union
    {
        volatile uint32_t AHBENR;
        struct
        {
            volatile uint32_t DMA1EN : 1;
            volatile uint32_t DMA2EN : 1;
            volatile uint32_t SRAMEN : 1;
            volatile const uint32_t  : 1;
            volatile uint32_t FLITFEN : 1;
            volatile const uint32_t  : 1;
            volatile uint32_t CRCEN : 1;
            volatile const uint32_t REVERSED2 : 5;
            volatile uint32_t OTGFSEN : 1;
            volatile const uint32_t : 1;
            volatile uint32_t ETHMACEN : 1;
            volatile uint32_t ETHMACTXEN : 1;
            volatile uint32_t ETHMACRXEN : 1;
            volatile const uint32_t : 15;
        } AHBENR_b;
    };

    /* APB2 peripheral clock enable register (APB2ENR) 0x18 */
    union
    {
        volatile uint32_t APB2ENR;
        struct
        {
            volatile uint32_t AFIOEN : 1;
            volatile const uint32_t  : 1;
            volatile uint32_t IOPAEN : 1;
            volatile uint32_t IOPBEN : 1;
            volatile uint32_t IOPCEN : 1;
            volatile uint32_t IOPDEN : 1;
            volatile uint32_t IOPEEN : 1;
            volatile const uint32_t  : 2;
            volatile uint32_t ADC1EN : 1;
            volatile uint32_t ADC2EN : 1;
            volatile uint32_t TIM1EN : 1;
            volatile uint32_t SPI1EN : 1;
            volatile const uint32_t REVERSED2 : 1;
            volatile uint32_t USART1EN : 1;
            volatile const uint32_t : 17;
        } APB2ENR_b;
    };

    /* APB1 peripheral clock enable register (APB1ENR) 0x1C */
    union
    {
        volatile uint32_t APB1ENR;
        struct
        {
            volatile uint32_t TIM2EN : 1;
            volatile uint32_t TIM3EN : 1;
            volatile uint32_t TIM4EN : 1;
            volatile uint32_t TIM5EN : 1;
            volatile uint32_t TIM6EN : 1;
            volatile uint32_t TIM7EN : 1;
            volatile const uint32_t  : 5;
            volatile uint32_t WWDGEN : 1;
            volatile const uint32_t  : 2;
            volatile uint32_t SPI2EN : 1;
            volatile uint32_t SPI3EN : 1;
            volatile const uint32_t REVERSED2 : 1;
            volatile uint32_t USART2EN : 1;
            volatile uint32_t USART3EN : 1;
            volatile uint32_t UART4EN : 1;
            volatile uint32_t UART5EN : 1;
            volatile uint32_t I2C1EN : 1;
            volatile uint32_t I2C2EN : 1;
            volatile const uint32_t : 2;
            volatile uint32_t CAN1EN : 1;
            volatile uint32_t CAN2EN : 1;
            volatile uint32_t BKPEN : 1;
            volatile uint32_t PWREN : 1;
            volatile uint32_t DACEN : 1;
            volatile const uint32_t : 2;
        } APB1ENR_b;
    };

    /* Backup domain control register (BDCR) 0x20 */
    union
    {
        volatile uint32_t BDCR;
        struct
        {
            volatile uint32_t LSEON : 1;
            volatile uint32_t LSERDY : 1;
            volatile uint32_t LSEBYP : 1;
            volatile const uint32_t  : 5;
            volatile uint32_t RTCSEL : 2;
            volatile const uint32_t  : 5;
            volatile uint32_t RTCEN : 1;
            volatile uint32_t BDRST : 1;
            volatile const uint32_t REVERSED2 : 15;
        } BDCR_b;
    };

    /* Control/status register (CSR) 0x24 */
    union
    {
        volatile uint32_t CSR;
        struct
        {
            volatile uint32_t LSION : 1;
            volatile uint32_t LSIRDY : 1;
            volatile const uint32_t  : 22;
            volatile uint32_t RMVF : 1;
            volatile const uint32_t  : 1;
            volatile uint32_t PINRSTF : 1;
            volatile uint32_t PORRSTF : 1;
            volatile uint32_t SFTRSTF : 1;
            volatile uint32_t IWDGRSTF : 1;
            volatile uint32_t WWDGRSTF : 1;
            volatile uint32_t LPWRRSTF : 1;
            volatile const uint32_t REVERSED2 : 15;
        } CSR_b;
    };

    /* AHB peripheral clock reset register (AHBRSTR) 0x28 */
    union
    {
        volatile uint32_t AHBRSTR;
        struct
        {
            volatile uint32_t LSION : 1;
            volatile uint32_t LSIRDY : 1;
            volatile const uint32_t  : 22;
            volatile uint32_t RMVF : 1;
            volatile const uint32_t  : 1;
            volatile uint32_t PINRSTF : 1;
            volatile uint32_t PORRSTF : 1;
            volatile uint32_t SFTRSTF : 1;
            volatile uint32_t IWDGRSTF : 1;
            volatile uint32_t WWDGRSTF : 1;
            volatile uint32_t LPWRRSTF : 1;
            volatile const uint32_t REVERSED2 : 15;
        } AHBRSTR_b;
    };

    /* Clock configuration register2 (CFGR2) 0x2C */
    union
    {
        volatile uint32_t CFGR2;
        struct
        {
            volatile uint32_t PREDIV1 : 4;
            volatile uint32_t PREDIV2 : 4;
            volatile uint32_t PLL2MUL : 4;
            volatile uint32_t PLL3MUL : 4;
            volatile uint32_t PREDIV1SRC : 1;
            volatile uint32_t I2S2SRC : 1;
            volatile uint32_t I2S3SRC : 4;
            volatile const uint32_t  : 13;
        } CFGR2_b;
    };
} RCC_Type;

#define RCC_BASE        (0x40021000U)
#define RCC ((RCC_Type *)RCC_BASE)

/**********************************************************************************************************************
 *                                                      GPIO
 **********************************************************************************************************************/
typedef struct GPIOx_Type_t
{   
    /* Port configuration register low (CRL) 0x00 */
    union
    {
        volatile uint32_t CRL;
        struct
        {
            volatile uint32_t MODE0 : 2;
            volatile uint32_t CNF0 : 2;
            volatile uint32_t MODE1 : 2;
            volatile uint32_t CNF1 : 2;
            volatile uint32_t MODE2 : 2;
            volatile uint32_t CNF2 : 2;
            volatile uint32_t MODE3 : 2;
            volatile uint32_t CNF3 : 2;
            volatile uint32_t MODE4 : 2;
            volatile uint32_t CNF4 : 2;
            volatile uint32_t MODE5 : 2;
            volatile uint32_t CNF5 : 2;
            volatile uint32_t MODE6 : 2;
            volatile uint32_t CNF6 : 2;
            volatile uint32_t MODE7 : 2;
            volatile uint32_t CNF7 : 2;
        } CRL_b;
    };

    /* Port configuration register high (CRH) 0x04 */
    union
    {
        volatile uint32_t CRH;
        struct
        {
            volatile uint32_t MODE8 : 2;
            volatile uint32_t CNF8 : 2;
            volatile uint32_t MODE9 : 2;
            volatile uint32_t CNF9 : 2;
            volatile uint32_t MODE10 : 2;
            volatile uint32_t CNF10 : 2;
            volatile uint32_t MODE11 : 2;
            volatile uint32_t CNF11 : 2;
            volatile uint32_t MODE12 : 2;
            volatile uint32_t CNF12 : 2;
            volatile uint32_t MODE13 : 2;
            volatile uint32_t CNF13 : 2;
            volatile uint32_t MODE14 : 2;
            volatile uint32_t CNF14 : 2;
            volatile uint32_t MODE15 : 2;
            volatile uint32_t CNF15 : 2;
        } CRH_b;
    };

    /* Port input data register (IDR) 0x08 */
    union
    {
        volatile uint32_t IDR;
        struct
        {
            volatile const uint32_t IDR0 : 1;
            volatile const uint32_t IDR1 : 1;
            volatile const uint32_t IDR2 : 1;
            volatile const uint32_t IDR3 : 1;
            volatile const uint32_t IDR4 : 1;
            volatile const uint32_t IDR5 : 1;
            volatile const uint32_t IDR6 : 1;
            volatile const uint32_t IDR7 : 1;
            volatile const uint32_t IDR8 : 1;
            volatile const uint32_t IDR9 : 1;
            volatile const uint32_t IDR10 : 1;
            volatile const uint32_t IDR11 : 1;
            volatile const uint32_t IDR12 : 1;
            volatile const uint32_t IDR13 : 1;
            volatile const uint32_t IDR14 : 1;
            volatile const uint32_t IDR15 : 1;
            volatile const uint32_t  : 16;
        } IDR_b;
    };

    /* Port output data register (ODR) 0x0C */
    union
    {
        volatile uint32_t ODR;
        struct
        {
            volatile uint32_t ODR0 : 1;
            volatile uint32_t ODR1 : 1;
            volatile uint32_t ODR2 : 1;
            volatile uint32_t ODR3 : 1;
            volatile uint32_t ODR4 : 1;
            volatile uint32_t ODR5 : 1;
            volatile uint32_t ODR6 : 1;
            volatile uint32_t ODR7 : 1;
            volatile uint32_t ODR8 : 1;
            volatile uint32_t ODR9 : 1;
            volatile uint32_t ODR10 : 1;
            volatile uint32_t ODR11 : 1;
            volatile uint32_t ODR12 : 1;
            volatile uint32_t ODR13 : 1;
            volatile uint32_t ODR14 : 1;
            volatile uint32_t ODR15 : 1;
            volatile const uint32_t  : 16;
        } ODR_b;
    };

    /* Port bit set/reset register (BSRR) 0x10 */
    union
    {
        volatile uint32_t BSRR;
        struct
        {
            volatile uint32_t BS0 : 1;
            volatile uint32_t BS1 : 1;
            volatile uint32_t BS2 : 1;
            volatile uint32_t BS3 : 1;
            volatile uint32_t BS4 : 1;
            volatile uint32_t BS5 : 1;
            volatile uint32_t BS6 : 1;
            volatile uint32_t BS7 : 1;
            volatile uint32_t BS8 : 1;
            volatile uint32_t BS9 : 1;
            volatile uint32_t BS10 : 1;
            volatile uint32_t BS11 : 1;
            volatile uint32_t BS12 : 1;
            volatile uint32_t BS13 : 1;
            volatile uint32_t BS14 : 1;
            volatile uint32_t BS15 : 1;
            volatile uint32_t BR0 : 1;
            volatile uint32_t BR1 : 1;
            volatile uint32_t BR2 : 1;
            volatile uint32_t BR3 : 1;
            volatile uint32_t BR4 : 1;
            volatile uint32_t BR5 : 1;
            volatile uint32_t BR6 : 1;
            volatile uint32_t BR7 : 1;
            volatile uint32_t BR8 : 1;
            volatile uint32_t BR9 : 1;
            volatile uint32_t BR10 : 1;
            volatile uint32_t BR11 : 1;
            volatile uint32_t BR12 : 1;
            volatile uint32_t BR13 : 1;
            volatile uint32_t BR14 : 1;
            volatile uint32_t BR15 : 1;
        } BSRR_b;
    };

    /* Port bit reset register (BRR) 0x14 */
    union
    {
        volatile uint32_t BRR;
        struct
        {
            volatile uint32_t BR0 : 1;
            volatile uint32_t BR1 : 1;
            volatile uint32_t BR2 : 1;
            volatile uint32_t BR3 : 1;
            volatile uint32_t BR4 : 1;
            volatile uint32_t BR5 : 1;
            volatile uint32_t BR6 : 1;
            volatile uint32_t BR7 : 1;
            volatile uint32_t BR8 : 1;
            volatile uint32_t BR9 : 1;
            volatile uint32_t BR10 : 1;
            volatile uint32_t BR11 : 1;
            volatile uint32_t BR12 : 1;
            volatile uint32_t BR13 : 1;
            volatile uint32_t BR14 : 1;
            volatile uint32_t BR15 : 1;
            volatile const uint32_t  : 16;
        } BRR_b;
    };

    /* Port configuration lock register (LCKR) 0x18 */
    /*
        This register is used to lock the configuration of the port bits when a correct write sequence
        is applied to bit 16 (LCKK). The value of bits [15:0] is used to lock the configuration of the
        GPIO. During the write sequence, the value of LCKR[15:0] must not change. When the
        LOCK sequence has been applied on a port bit it is no longer possible to modify the value of
        the port bit until the next reset.
        Each lock bit freezes the corresponding 4 bits of the control register (CRL, CRH).
    */
    union
    {
        volatile uint32_t LCKR;
        struct
        {
            volatile uint32_t LCK0 : 1;
            volatile uint32_t LCK1 : 1;
            volatile uint32_t LCK2 : 1;
            volatile uint32_t LCK3 : 1;
            volatile uint32_t LCK4 : 1;
            volatile uint32_t LCK5 : 1;
            volatile uint32_t LCK6 : 1;
            volatile uint32_t LCK7 : 1;
            volatile uint32_t LCK8 : 1;
            volatile uint32_t LCK9 : 1;
            volatile uint32_t LCK10 : 1;
            volatile uint32_t LCK11 : 1;
            volatile uint32_t LCK12 : 1;
            volatile uint32_t LCK13 : 1;
            volatile uint32_t LCK14 : 1;
            volatile uint32_t LCK15 : 1;
            volatile uint32_t LCKK : 1;
            /*
            LOCK key writing sequence:
            Write 1
            Write 0
            Write 1
            Read 0
            Read 1 (this read is optional but confirms that the lock is active)
            */
           volatile const uint32_t  : 15;
        } LCKR_b;
    };
} GPIOx_Type;

typedef struct AFIO_Type_t
{
    /* Event control register (EVCR) 0x00 */
    union
    {
        volatile uint32_t EVCR;
        struct
        {
            volatile uint32_t PIN : 4;
            volatile uint32_t PORT : 4;
            volatile uint32_t EVOE : 1;
            volatile const uint32_t : 23;
        } EVCR_b;
    };

    /* AF remap and debug I/O configuration register (MAPR) 0x04 */
    union
    {
        volatile uint32_t MAPR;
        struct
        {
            volatile uint32_t SPI1_REMAP : 1;
            volatile uint32_t I2C1_REMAP : 1;
            volatile uint32_t USART1_REMAP : 1;
            volatile uint32_t USART2_REMAP : 1;
            volatile uint32_t USART3_REMAP : 2;
            volatile uint32_t TIM1_REMAP : 2;
            volatile uint32_t TIM2_REMAP : 2;
            volatile uint32_t TIM3_REMAP : 2;
            volatile uint32_t TIM4_REMAP : 1;
            volatile uint32_t CAN_REMAP : 2;
            volatile uint32_t PD01_REMAP : 1;
            volatile uint32_t TIM5CH4_IREMAP : 1;
            volatile uint32_t ADC1_ETRGINJ_REMAP : 1;
            volatile uint32_t ADC1_ETRGREG_REMAP : 1;
            volatile uint32_t ADC2_ETRGINJ_REMAP : 1;
            volatile uint32_t ADC2_ETRGREG_REMAP : 1;
            volatile const uint32_t : 3;
            volatile uint32_t SWJ_CFG : 3;
            volatile const uint32_t : 5;
        } MAPR_b;
    };

    /* External interrupt configuration register 1 (EXTICR1) 0x08 */
    union
    {
        volatile uint32_t EXTICR1;
        struct
        {
            volatile uint32_t EXTI0 : 4;
            volatile uint32_t EXTI1 : 4;
            volatile uint32_t EXTI2 : 4;
            volatile uint32_t EXTI3 : 4;
            volatile const uint32_t : 16;
        } EXTICR1_b;
    };

    /* External interrupt configuration register 2 (EXTICR2) 0x0C */
    union
    {
        volatile uint32_t EXTICR2;
        struct
        {
            volatile uint32_t EXTI4 : 4;
            volatile uint32_t EXTI5 : 4;
            volatile uint32_t EXTI6 : 4;
            volatile uint32_t EXTI7 : 4;
            volatile const uint32_t : 16;
        } EXTICR2_b;
    };

    /* External interrupt configuration register 3 (EXTICR3) 0x10 */
    union
    {
        volatile uint32_t EXTICR3;
        struct
        {
            volatile uint32_t EXTI8 : 4;
            volatile uint32_t EXTI9 : 4;
            volatile uint32_t EXTI10 : 4;
            volatile uint32_t EXTI11 : 4;
            volatile const uint32_t : 16;
        } EXTICR3_b;
    };

    /* External interrupt configuration register 4 (EXTICR4) 0x14 */
    union
    {
        volatile uint32_t EXTICR4;
        struct
        {
            volatile uint32_t EXTI12 : 4;
            volatile uint32_t EXTI13 : 4;
            volatile uint32_t EXTI14 : 4;
            volatile uint32_t EXTI15 : 4;
            volatile const uint32_t : 16;
        } EXTICR4_b;
    };

    volatile const uint32_t RESERVED0; // 0x18

    /* AF remap and debug I/O configuration register2 (MAPR2) 0x1C */
    union
    {
        volatile uint32_t MAPR2;
        struct
        {
            volatile const uint32_t : 5;
            volatile uint32_t TIM9_REMAP : 1;
            volatile uint32_t TIM10_REMAP : 1;
            volatile uint32_t TIM11_REMAP : 1;
            volatile uint32_t TIM13_REMAP : 1;
            volatile uint32_t TIM14_REMAP : 1;
            volatile uint32_t FSMC_NADV : 1;
            volatile const uint32_t : 11;
        } MAPR2_b;
    };
} AFIO_Type;

#define GPIOA_BASE        (0x40010800U)
#define GPIOB_BASE        (0x40010C00U)
#define GPIOC_BASE        (0x40011000U)
#define GPIOD_BASE        (0x40011400U)
#define GPIOE_BASE        (0x40011800U)
#define GPIOF_BASE        (0x40011C00U)
#define GPIOG_BASE        (0x40012000U)
#define AFIO_BASE         (0x40010000U)

#define GPIOA ((GPIOx_Type *)GPIOA_BASE)
#define GPIOB ((GPIOx_Type *)GPIOB_BASE)
#define GPIOC ((GPIOx_Type *)GPIOC_BASE)
#define GPIOD ((GPIOx_Type *)GPIOD_BASE)
#define GPIOE ((GPIOx_Type *)GPIOE_BASE)
#define GPIOF ((GPIOx_Type *)GPIOF_BASE)
#define GPIOG ((GPIOx_Type *)GPIOG_BASE)
#define AFIO  ((AFIO_Type *)AFIO_BASE)

#endif