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

/**********************************************************************************************************************
 *                                                      PWR
 **********************************************************************************************************************/
typedef struct PWR_Type_t
{
    /* Power control register (PWR_CR) 0x00 */
    union
    {
        volatile uint32_t CR;
        struct
        {
            volatile uint32_t LPDS : 1; /* Low-power deepsleep.
                                        This bit is set and cleared by software. 
                                        It works together with the PDDS bit.
                                        0: Voltage regulator on during Stop mode
                                        1: Voltage regulator in low-power mode during Stop mode */
            volatile uint32_t PDDS : 1; /* Power down deepsleep.
                                        This bit is set and cleared by software. 
                                        It works together with the LPDS bit.
                                        0: Enter Stop mode when the CPU enters Deepsleep. 
                                        The regulator status depends on the
                                        LPDS bit.
                                        1: Enter Standby mode when the CPU enters Deepsleep. */
            volatile uint32_t CWUF : 1; /* Clear wakeup flag.
                                        This bit is always read as 0.
                                        0: No effect
                                        1: Clear the WUF Wakeup Flag after 
                                        2 System clock cycles. (write) */
            volatile uint32_t CSBF : 1; /* Clear standby flag.
                                        This bit is always read as 0.
                                        0: No effect
                                        1: Clear the SBF Standby Flag (write) */
            volatile uint32_t PVDE : 1; /* programmable voltage detector enable.
                                        This bit is set and cleared by software.
                                        0: PVD disabled
                                        1: PVD enabled */
            volatile uint32_t PLS : 3; /* PVD level selection.
                                        These bits are written by software to select the voltage threshold detected by the
                                        programmable voltage detector */
            volatile uint32_t DBP : 1; /* Disable backup domain write protection.
                                        In reset state, the RTC and backup registers 
                                        are protected against parasitic write access.
                                        This bit must be set to enable write access to 
                                        these registers.
                                        0: Access to RTC and Backup registers disabled
                                        1: Access to RTC and Backup registers enabled */
            const volatile uint32_t : 23;
        } CR_b;
    };

    /* Power control/status register (PWR_CSR) 0x04. */
    union
    {
        volatile uint32_t CSR;
        struct
        {
            const volatile uint32_t WUF : 1; /* This bit is set by hardware and cleared by hardware, 
                                        by a system reset or by setting the
                                        CWUF bit in the Power control register (PWR_CR)
                                        0: No wakeup event occurred
                                        1: A wakeup event was received from the WKUP pin or 
                                        from the RTC alarm */
            const volatile uint32_t SBF : 1; /* This bit is set by hardware and cleared only 
                                                by a POR/PDR (power on reset/power down reset)
                                                or by setting the CSBF bit in the Power control 
                                                register (PWR_CR)
                                                0: Device has not been in Standby mode
                                                1: Device has been in Standby mode */
            volatile uint32_t PVDO : 1; /* This bit is set and cleared by hardware. 
                                        It is valid only if PVD is enabled by the PVDE bit.
                                        0: VDD/VDDA is higher than the PVD threshold 
                                        selected with the PLS[2:0] bits.
                                        1: VDD/VDDA is lower than the PVD threshold 
                                        selected with the PLS[2:0] bits. */
            volatile uint32_t : 5;
            volatile uint32_t EWUP : 1; /* This bit is set and cleared by software.
                                        0: WKUP pin is used for general purpose I/O. 
                                        An event on the WKUP pin does not wakeup
                                        the device from Standby mode.
                                        1: WKUP pin is used for wakeup from Standby mode and 
                                        forced in input pull down
                                        configuration (rising edge on WKUP pin wakes-up 
                                        the system from Standby mode). */
            volatile uint32_t : 23;
        } CSR_b;
    };
} PWR_Type;

#define PWR_BASE        (0x40007000U)

#define PWR ((PWR_Type *)PWR_BASE)

/**********************************************************************************************************************
 *                                                      DMA
 **********************************************************************************************************************/

typedef struct DMAx_Config_t
{
    /* DMA channel x configuration register (DMA_CCRx) */
    union
    {
        volatile uint32_t CCRx;
        struct
        {
            volatile uint32_t EN : 1; /*  Channel enable */
            volatile uint32_t TCIE : 1; /* Transfer complete interrupt enable */
            volatile uint32_t HTIE : 1; /* Half transfer interrupt enable */
            volatile uint32_t TEIE : 1; /* Transfer error interrupt enable */
            volatile uint32_t DIR : 1; /* Data transfer direction 
                                        0: Read from peripheral
                                        1: Read from memory*/
            volatile uint32_t CIRC : 1; /* Circular mode */
            volatile uint32_t PINC : 1; /* Peripheral increment mode */
            volatile uint32_t MINC : 1; /* Memory increment mode */
            volatile uint32_t PSIZE : 2; /* Peripheral size 
                                            00: 8-bits
                                            01: 16-bits
                                            10: 32-bits
                                            11: Reserved */
            volatile uint32_t MSIZE : 2; /* Memory size
                                            00: 8-bits
                                            01: 16-bits
                                            10: 32-bits
                                            11: Reserved */
            volatile uint32_t PL : 2;   /*  Channel priority level 
                                            00: Low
                                            01: Medium
                                            10: High
                                            11: Very high */
            volatile uint32_t MEM2MEM : 1; /* Memory to memory mode */
            const volatile uint32_t : 17;
        } CCRx_b;
    };

    /* DMA channel x number of data register (DMA_CNDTRx) */
    union
    {
        /* This register can only be 
        written when the channel is disabled. Once the channel is enabled, 
        this register is read-only, indicating the remaining bytes to be transmitted. 
        This register decrements after each DMA transfer.
        Once the transfer is completed, this register can either stay at zero or be reloaded
        automatically by the value previously programmed if the channel is configured in autoreload mode.
        If this register is zero, no transaction can be served whether the channel is enabled or not.*/
        volatile uint32_t CNDTRx;
        struct
        {
            volatile uint32_t NDT : 16; /* Number of data to transfer. */
            const volatile uint32_t : 16;
        } CNDTRx_b;
    };

    /* DMA channel x peripheral address register (DMA_CPARx) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CPARx;
        struct
        {
            volatile uint32_t PA : 32; /* Peripheral address. Base address of the peripheral data register 
                                          from/to which the data will be read/written. */
        } CPARx_b;
    };

    /* DMA channel x memory address register (DMA_CMARx) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CMARx;
        struct
        {
            volatile uint32_t MA : 32; /* Memory address. Base address of the memory address register 
                                          from/to which the data will be read/written. */
        } CMARx_b;
    };

    const uint32_t RESERVED;
} DMAx_Config;

typedef struct DMAx_Type_t
{   
    /* DMA interrupt status register (DMA_ISR) 0x00 */
    union
    {
        const volatile uint32_t ISR;
        struct
        {
            const volatile uint32_t GIF1 : 1; /* Channel 1 global interrupt flag */
            const volatile uint32_t TCIF1 : 1; /* Channel 1 transfer complete flag */
            const volatile uint32_t HTIF1 : 1; /* Channel 1 half transfer flag */
            const volatile uint32_t TEIF1 : 1; /* Channel 1 transfer error flag */
            const volatile uint32_t GIF2 : 1; /* Channel 2 global interrupt flag */
            const volatile uint32_t TCIF2 : 1; /* Channel 2 transfer complete flag */
            const volatile uint32_t HTIF2 : 1; /* Channel 2 half transfer flag */
            const volatile uint32_t TEIF2 : 1; /* Channel 2 transfer error flag */
            const volatile uint32_t GIF3 : 1; /* Channel 3 global interrupt flag */
            const volatile uint32_t TCIF3 : 1; /* Channel 3 transfer complete flag */
            const volatile uint32_t HTIF3 : 1; /* Channel 3 half transfer flag */
            const volatile uint32_t TEIF3 : 1; /* Channel 3 transfer error flag */
            const volatile uint32_t GIF4 : 1; /* Channel 4 global interrupt flag */
            const volatile uint32_t TCIF4 : 1; /* Channel 4 transfer complete flag */
            const volatile uint32_t HTIF4 : 1; /* Channel 4 half transfer flag */
            const volatile uint32_t TEIF4 : 1; /* Channel 4 transfer error flag */
            const volatile uint32_t GIF5 : 1; /* Channel 5 global interrupt flag */
            const volatile uint32_t TCIF5 : 1; /* Channel 5 transfer complete flag */
            const volatile uint32_t HTIF5 : 1; /* Channel 5 half transfer flag */
            const volatile uint32_t TEIF5 : 1; /* Channel 5 transfer error flag */
            const volatile uint32_t GIF6 : 1; /* Channel 6 global interrupt flag */
            const volatile uint32_t TCIF6 : 1; /* Channel 6 transfer complete flag */
            const volatile uint32_t HTIF6: 1; /* Channel 6 half transfer flag */
            const volatile uint32_t TEIF6 : 1; /* Channel 6 transfer error flag */
            const volatile uint32_t GIF7 : 1; /* Channel 7 global interrupt flag */
            const volatile uint32_t TCIF7 : 1; /* Channel 7 transfer complete flag */
            const volatile uint32_t HTIF7 : 1; /* Channel 7 half transfer flag */
            const volatile uint32_t TEIF7 : 1; /* Channel 7 transfer error flag */
            const volatile uint32_t : 4;
        } ISR_b;
    };

    /* DMA interrupt flag clear register (DMA_IFCR) 0x04. Write 1 to clear */
    union
    {
        volatile uint32_t IFCR;
        struct
        {
            volatile uint32_t CGIF1 : 1; /* Channel 1 global interrupt clear */
            volatile uint32_t CTCIF1 : 1; /* Channel 1 transfer complete clear */
            volatile uint32_t CHTIF1 : 1; /* Channel 1 half transfer clear */
            volatile uint32_t CTEIF1 : 1; /* Channel 1 transfer error clear */
            volatile uint32_t CGIF2 : 1; /* Channel 2 global interrupt clear */
            volatile uint32_t CTCIF2 : 1; /* Channel 2 transfer complete clear */
            volatile uint32_t CHTIF2 : 1; /* Channel 2 half transfer clear */
            volatile uint32_t CTEIF2 : 1; /* Channel 2 transfer error clear */
            volatile uint32_t CGIF3 : 1; /* Channel 3 global interrupt clear */
            volatile uint32_t CTCIF3 : 1; /* Channel 3 transfer complete clear */
            volatile uint32_t CHTIF3 : 1; /* Channel 3 half transfer clear */
            volatile uint32_t CTEIF3 : 1; /* Channel 3 transfer error clear */
            volatile uint32_t CGIF4 : 1; /* Channel 4 global interrupt clear */
            volatile uint32_t CTCIF4 : 1; /* Channel 4 transfer complete clear */
            volatile uint32_t CHTIF4 : 1; /* Channel 4 half transfer clear */
            volatile uint32_t CTEIF4 : 1; /* Channel 4 transfer error clear */
            volatile uint32_t CGIF5 : 1; /* Channel 5 global interrupt clear */
            volatile uint32_t CTCIF5 : 1; /* Channel 5 transfer complete clear */
            volatile uint32_t CHTIF5 : 1; /* Channel 5 half transfer clear */
            volatile uint32_t CTEIF5 : 1; /* Channel 5 transfer error clear */
            volatile uint32_t CGIF6 : 1; /* Channel 6 global interrupt clear */
            volatile uint32_t CTCIF6 : 1; /* Channel 6 transfer complete clear */
            volatile uint32_t CHTIF6: 1; /* Channel 6 half transfer clear */
            volatile uint32_t CTEIF6 : 1; /* Channel 6 transfer error clear */
            volatile uint32_t CGIF7 : 1; /* Channel 7 global interrupt clear */
            volatile uint32_t CTCIF7 : 1; /* Channel 7 transfer complete clear */
            volatile uint32_t CHTIF7 : 1; /* Channel 7 half transfer clear */
            volatile uint32_t CTEIF7 : 1; /* Channel 7 transfer error clear */
            const volatile uint32_t : 4;
        } IFCR_b;
    };

    /* DMA channel x configuration register */
    DMAx_Config DMA_Channelx_Reg[7U];

} DMAx_Type;

#define DMA1_BASE        (0x40020000U)
#define DMA2_BASE        (0x40020400U)

#define DMA1 ((DMAx_Type *)DMA1_BASE)
#define DMA2 ((DMAx_Type *)DMA2_BASE)

/**********************************************************************************************************************
 *                                                      SPI
 **********************************************************************************************************************/

typedef struct SPIx_Type_t
{
    /* SPI control register 1 (SPI_CR1) (not used in I2S mode) */
    union
    {
        volatile uint32_t SPI_CR1;
        struct
        {
            volatile uint32_t CPHA : 1; /* Clock phase
                                        0: The first clock transition is the first data capture edge
                                        1: The second clock transition is the first data capture edge */
            volatile uint32_t CPOL : 1; /* Clock polarity
                                        0: CK to 0 when idle
                                        1: CK to 1 when idle */
            volatile uint32_t MSTR : 1; /* Master selection
                                        0: Slave configuration
                                        1: Master configuration */
            volatile uint32_t BR : 3; /* Baud rate control */
            volatile uint32_t SPE : 1; /* SPI enable 
                                        0: Peripheral disabled
                                        1: Peripheral enabled */
            volatile uint32_t LSBFIRST : 1; /* Frame format
                                            0: MSB transmitted first
                                            1: LSB transmitted first */
            volatile uint32_t SSI : 1; /* Internal slave select
                                        This bit has an effect only when the SSM bit is set. 
                                        The value of this bit is forced onto the
                                        NSS pin and the IO value of the NSS pin is ignored. */
            volatile uint32_t SSM : 1; /* Software slave management
                                        When the SSM bit is set, the NSS pin input is
                                        replaced with the value from the SSI bit.
                                        0: Software slave management disabled
                                        1: Software slave management enabled */
            volatile uint32_t RXONLY : 1; /* Receive only
                                            This bit combined with the BIDImode bit selects the 
                                            direction of transfer in 2-line
                                            unidirectional mode. This bit is also useful in a 
                                            multislave system in which this particular
                                            slave is not accessed, the output from the accessed 
                                            slave is not corrupted.
                                            0: Full duplex (Transmit and receive)
                                            1: Output disabled (Receive-only mode) */
            volatile uint32_t DFF : 1; /* Data frame format
                                        0: 8-bit data frame format is 
                                        selected for transmission/reception
                                        1: 16-bit data frame format is 
                                        selected for transmission/reception 
                                        This bit should be written only when SPI is 
                                        disabled (SPE = ‘0’) for correct operation */
            volatile uint32_t CRCNEXT : 1; /* CRC transfer next 
                                            0: Data phase (no CRC phase)
                                            1: Next transfer is CRC (CRC phase) 
                                            When the SPI is configured in full duplex or transmitter 
                                            only modes, CRCNEXT must be written as soon as the last 
                                            data is written to the SPI_DR register.
                                            When the SPI is configured in receiver only mode, CRCNEXT 
                                            must be set after the second last data reception. */
            volatile uint32_t CRCEN : 1; /* Hardware CRC calculation enable
                                            0: CRC calculation disabled
                                            1: CRC calculation enabled 
                                            This bit should be written only when SPI is disabled 
                                            (SPE = ‘0’) for correct operation */
            volatile uint32_t BIDIOE : 1; /* Output enable in bidirectional mode
                                            This bit combined with the BIDImode bit selects the 
                                            direction of transfer in bidirectional mode
                                            0: Output disabled (receive-only mode)
                                            1: Output enabled (transmit-only mode) 
                                            In master mode, the MOSI pin is used while the 
                                            MISO pin is used in slave mode.*/
            volatile uint32_t BIDIMODE : 1; /* Bidirectional data mode enable
                                            0: 2-line unidirectional data mode selected
                                            1: 1-line bidirectional data mode selected */
            const volatile uint32_t : 16;
        }SPI_CR1_b;
    };

    /* SPI control register 2 (SPI_CR2) */
    union
    {
        volatile uint32_t SPI_CR2;
        struct
        {
            volatile uint32_t RXDMAEN : 1; /* Rx buffer DMA enable 
                                            When this bit is set, the DMA request is made 
                                            whenever the RXNE flag is set.
                                            0: Rx buffer DMA disabled
                                            1: Rx buffer DMA enabled */
            volatile uint32_t TXDMAEN : 1; /* Tx buffer DMA enable 
                                            When this bit is set, the DMA request is made 
                                            whenever the RXNE flag is set.
                                            0: Rx buffer DMA disabled
                                            1: Rx buffer DMA enabled */
            volatile uint32_t SSOE : 1; /*  SS output enable
                                            0: SS output is disabled in master mode and the cell 
                                            can work in multimaster configuration
                                            1: SS output is enabled in master mode and when the cell is enabled. 
                                            The cell cannot work in a multimaster environment */
            const volatile uint32_t : 2;
            volatile uint32_t ERRIE : 1; /* Error interrupt enable
                                            This bit controls the generation of an interrupt when an 
                                            error condition occurs (CRCERR, OVR, MODF in SPI mode and UDR, 
                                            OVR in I2S mode).
                                            0: Error interrupt is masked
                                            1: Error interrupt is enabled */
            volatile uint32_t RXNEIE : 1; /* RX buffer not empty interrupt enable
                                            0: RXNE interrupt masked
                                            1: RXNE interrupt not masked. Used to generate 
                                            an interrupt request when the RXNE flag is
                                            set. */
            volatile uint32_t TXEIE : 1; /* Tx buffer empty interrupt enable
                                            0: TXE interrupt masked
                                            1: TXE interrupt not masked. Used to generate 
                                            an interrupt request when the TXE flag is set. */
            const volatile uint32_t : 24;
        } SPI_CR2_b;
    };

    /* SPI status register (SPI_SR) */
    union
    {
        volatile uint32_t SPI_SR;
        struct
        {
            const volatile uint32_t RXNE : 1; /* Receive buffer not empty */
            const volatile uint32_t TXE : 1; /* Transmit buffer empty */
            const volatile uint32_t CHSIDE : 1; /* CHSIDE: Channel side
                                                0: Channel Left has to be transmitted or has been received
                                                1: Channel Right has to be transmitted or has been received
                                                Note: This bit is not used for SPI mode and is 
                                                meaningless in PCM mode */
            const volatile uint32_t UDR : 1; /* Underrun flag
                                                0: No underrun occurred
                                                1: Underrun occurred
                                                This flag is set by hardware and reset by a software sequence.
                                                Note: This bit is not used in SPI mode. */
            volatile uint32_t CRCERR : 1; /* CRC error flag
                                                0: CRC value received matches the SPI_RXCRCR value
                                                1: CRC value received does not match the SPI_RXCRCR value */
            const volatile uint32_t MODF : 1; /* Mode fault
                                                0: No mode fault occurred
                                                1: Mode fault occurred
                                                This flag is set by hardware and reset by a software sequence.  */
            const volatile uint32_t OVR : 1; /* Overrun flag
                                                0: No overrun occurred
                                                1: Overrun occurred
                                                This flag is set by hardware and reset by a software sequence */
            const volatile uint32_t BSY : 1; /* Busy flag
                                                0: SPI (or I2S) not busy
                                                1: SPI (or I2S) is busy in communication or Tx buffer is not empty
                                                This flag is set and cleared by hardware. */
            const volatile uint32_t : 24;
        } SPI_SR_b;
    };

    /* SPI data register (SPI_DR) */
    union
    {
        volatile uint32_t SPI_DR;
        struct
        {
            volatile uint32_t DR : 16; /* Data register
                                        Data received or to be transmitted.
                                        The data register is split into 2 buffers - one for writing 
                                        (Transmit Buffer) and another one for reading (Receive buffer). 
                                        A write to the data register will write into the Tx buffer and a read
                                        from the data register will return the value held in the Rx buffer. */
            const volatile uint32_t : 16;
        } SPI_DR_b;
    };

    /* SPI CRC polynomial register (SPI_CRCPR) (not used in I2S mode) */
    union
    {
        volatile uint32_t SPI_CRCPR;
        struct
        {
            volatile uint32_t CRCPOLY : 16;  /* CRC polynomial register
                                                This register contains the polynomial for the CRC calculation.
                                                The CRC polynomial (0007h) is the reset value of this register. Another polynomial can be
                                                configured as required */
            const volatile uint32_t : 16;
        } SPI_CRCPR_b;
    };

    /* SPI RX CRC register (SPI_RXCRCR) (not used in I2S mode) */
    union
    {
        const volatile uint32_t SPI_RXCRCR;
        struct
        {
            const volatile uint32_t RXCRC : 16;  /* Rx CRC register
                                            When CRC calculation is enabled, the RxCRC[15:0] bits contain 
                                            the computed CRC value of the subsequently received bytes. This 
                                            register is reset when the CRCEN bit in SPI_CR1 register is written 
                                            to 1. The CRC is calculated serially using the polynomial programmed in
                                            the SPI_CRCPR register.
                                            Only the 8 LSB bits are considered when the data frame format is 
                                            set to be 8-bit data (DFF bit of SPI_CR1 is cleared). CRC calculation 
                                            is done based on any CRC8 standard.
                                            The entire 16-bits of this register are considered when a 16-bit data 
                                            frame format is selected (DFF bit of the SPI_CR1 register is set). 
                                            CRC calculation is done based on any CRC16 standard.
                                            Note: A read to this register when the BSY Flag is set could return 
                                            an incorrect value. */
            const volatile uint32_t : 16;
        } SPI_RXCRCR_b;
    };

    /* SPI TX CRC register (SPI_TXCRCR) (not used in I2S mode) */
    union
    {
        const volatile uint32_t SPI_TXCRCR;
        struct
        {
            const volatile uint32_t TXCRC : 16;    /* Tx CRC register
                                                When CRC calculation is enabled, the TxCRC[7:0] bits contain 
                                                the computed CRC value of the subsequently transmitted bytes. 
                                                This register is reset when the CRCEN bit of SPI_CR1 is written 
                                                to 1. The CRC is calculated serially using the polynomial programmed 
                                                in the SPI_CRCPR register.
                                                Only the 8 LSB bits are considered when the data frame format is set 
                                                to be 8-bit data (DFF bit of SPI_CR1 is cleared). CRC calculation is 
                                                done based on any CRC8 standard.
                                                The entire 16-bits of this register are considered when a 16-bit data 
                                                frame format is selected (DFF bit of the SPI_CR1 register is set). 
                                                CRC calculation is done based on any CRC16 standard.
                                                Note: A read to this register when the BSY flag is set could return 
                                                an incorrect value. */
            const volatile uint32_t : 16;
        } SPI_TXCRCR_b;
    };

    /* SPI_I2S configuration register (SPI_I2SCFGR) */
    union
    {
        volatile uint32_t SPI_I2SCFGR;
        struct
        {
            volatile uint32_t CHLEN : 1; /* Channel length (number of bits per audio channel)
                                            0: 16-bit wide
                                            1: 32-bit wide
                                            The bit write operation has a meaning only if DATLEN = 00 
                                            otherwise the channel length is fixed to
                                            32-bit by hardware whatever the value filled in. */
            volatile uint32_t DATLEN : 2; /* Data length to be transferred
                                            00: 16-bit data length
                                            01: 24-bit data length
                                            10: 32-bit data length
                                            11: Not allowed */
            volatile uint32_t CKPOL : 1; /* Steady state clock polarity
                                            0: I2S clock steady state is low level
                                            1: I2S clock steady state is high level */
            volatile uint32_t I2SSTD : 2; /* I2S standard selection
                                            00: I2S Philips standard.
                                            01: MSB justified standard (left justified)
                                            10: LSB justified standard (right justified)
                                            11: PCM standard */
            const volatile uint32_t : 1;
            volatile uint32_t PCMSYNC : 1; /* PCM frame synchronization
                                            0: Short frame synchronization
                                            1: Long frame synchronization
                                            Note: This bit has a meaning only if I2SSTD = 11 (PCM standard is used) */
            volatile uint32_t I2SCFG : 2; /* I2S configuration mode
                                            00: Slave - transmit
                                            01: Slave - receive
                                            10: Master - transmit
                                            11: Master - receive */
            volatile uint32_t I2SE : 1; /* I2S Enable
                                            0: I2S peripheral is disabled
                                            1: I2S peripheral is enabled */
            volatile uint32_t I2SMOD : 1; /* I2SMOD: I2S mode selection
                                            0: SPI mode is selected
                                            1: I2S mode is selecte */
            const volatile uint32_t : 20;
        }SPI_I2SCFGR_b;
    };

    /*  SPI_I2S prescaler register (SPI_I2SPR) */
    union
    {
        volatile uint32_t SPI_I2SPR;
        struct
        {
            volatile uint32_t I2SDIV : 8; /*  I2S Linear prescaler */
            volatile uint32_t ODD : 1; /* Odd factor for the prescaler
                                        0: real divider value is = I2SDIV *2
                                        1: real divider value is = (I2SDIV * 2)+1 */
            volatile uint32_t MCKOE : 1; /* Master clock output enable
                                            0: Master clock output is disabled
                                            1: Master clock output is enabled */
            const volatile uint32_t : 12;
        }SPI_I2SPR_b;
    };
} SPIx_Type;

#define SPI1_BASE        (0x40013000U)
#define SPI2_BASE        (0x40003800U)
#define SPI3_BASE        (0x40003C00U)

#define SPI1 ((SPIx_Type *)SPI1_BASE)
#define SPI2 ((SPIx_Type *)SPI2_BASE)
#define SPI3 ((SPIx_Type *)SPI3_BASE)

/**********************************************************************************************************************
 *                                                      I2C
 **********************************************************************************************************************/

typedef struct I2Cx_Type_t
{
    /* I2C Control register 1 (I2C_CR1) */
    union
    {
        volatile uint16_t I2C_CR1;
        struct
        {
            volatile uint16_t PE : 1; /* PE: Peripheral enable
                                         0: Peripheral disable
                                         1: Peripheral enable */
            volatile uint16_t SMBUS : 1; /* SMBus mode
                                            0: I2C mode
                                            1: SMBus mode */
            const volatile uint16_t : 1;
            volatile uint16_t SMBTYPE : 1; /* SMBus type
                                              0: SMBus Device
                                              1: SMBus Host */
            volatile uint16_t ENARP : 1; /* ARP enable
                                            0: ARP disable
                                            1: ARP enable
                                            SMBus Device default address recognized if SMBTYPE=0
                                            SMBus Host address recognized if SMBTYPE=1 */
            volatile uint16_t ENPEC : 1; /* PEC enable
                                            0: PEC calculation disabled
                                            1: PEC calculation enabled */
            volatile uint16_t ENGC : 1;  /* General call enable
                                            0: General call disabled. Address 00h is NACKed.
                                            1: General call enabled. Address 00h is ACKed. */
            volatile uint16_t NOSTRETCH : 1; /* Clock stretching disable (Slave mode)
                                                This bit is used to disable clock stretching in 
                                                slave mode when ADDR or BTF flag is set, until
                                                it is reset by software.
                                                0: Clock stretching enabled
                                                1: Clock stretching disabled */
            volatile uint16_t START : 1; /* Start generation
                                            This bit is set and cleared by software and cleared 
                                            by hardware when start is sent or PE=0.
                                            In Master Mode:
                                            0: No Start generation
                                            1: Repeated start generation
                                            In Slave mode:
                                            0: No Start generation
                                            1: Start generation when the bus is free */
            volatile uint16_t STOP : 1;  /* The bit is set and cleared by software, cleared by hardware when a Stop condition is
                                            detected, set by hardware when a timeout error is detected.
                                            In Master Mode:
                                            0: No Stop generation.
                                            1: Stop generation after the current byte transfer 
                                            or after the current Start condition is sent.
                                            In Slave mode:
                                            0: No Stop generation.
                                            1: Release the SCL and SDA lines after the current byte transfer. */
            volatile uint16_t ACK : 1;   /* Acknowledge enable
                                            This bit is set and cleared by software and 
                                            cleared by hardware when PE=0.
                                            0: No acknowledge returned
                                            1: Acknowledge returned after a byte is 
                                            received (matched address or data) */
            volatile uint16_t POS : 1;   /* Acknowledge/PEC Position (for data reception)
                                            This bit is set and cleared by software and 
                                            cleared by hardware when PE=0.
                                            0: ACK bit controls the (N)ACK of the 
                                            current byte being received in the shift register. The
                                            PEC bit indicates that current byte in shift register 
                                            is a PEC.
                                            1: ACK bit controls the (N)ACK of the next 
                                            byte which will be received in the shift register.
                                            The PEC bit indicates that the next byte in the 
                                            shift register is a PEC */
            volatile uint16_t PEC : 1;   /* Packet error checking
                                            This bit is set and cleared by software, and cleared 
                                            by hardware when PEC is transferred or
                                            by a START or Stop condition or when PE=0.
                                            0: No PEC transfer
                                            1: PEC transfer (in Tx or Rx mode) */
            volatile uint16_t ALERT : 1; /* SMBus alert
                                            This bit is set and cleared by software, and 
                                            cleared by hardware when PE=0.
                                            0: Releases SMBA pin high. Alert Response 
                                            Address Header followed by NACK.
                                            1: Drives SMBA pin low. Alert Response 
                                            Address Header followed by ACK. */
            const volatile uint16_t : 1;
            volatile uint16_t SWRST : 1; /* Software reset
                                            When set, the I2C is under reset state. Before resetting this 
                                            bit, make sure the I2C lines are
                                            released and the bus is free.
                                            0: I2C Peripheral not under reset
                                            1: I2C Peripheral under reset state */
        } I2C_CR1_b;
    };

    const volatile uint16_t RESERVED0;

    /* I2C Control register 2 (I2C_CR2) */
    union
    {
        volatile uint16_t I2C_CR2;
        struct
        {
            volatile uint16_t FREQ : 6;  /* Peripheral clock frequency
                                            The FREQ bits must be configured with the APB clock 
                                            frequency value (I2C peripheral connected to APB). 
                                            The FREQ field is used by the peripheral to generate data setup and
                                            hold times compliant with the I2C specifications. 
                                            The minimum allowed frequency is 2 MHz, the maximum frequency is 
                                            limited by the maximum APB frequency and cannot exceed
                                            50 MHz (peripheral intrinsic maximum limit).*/
            const volatile uint16_t : 2;
            volatile uint16_t ITERREN : 1;   /* Error interrupt enable
                                                0: Error interrupt disabled
                                                1: Error interrupt enabled
                                                This interrupt is generated when:
                                                – BERR = 1
                                                – ARLO = 1
                                                – AF = 1
                                                – OVR = 1
                                                – PECERR = 1
                                                – TIMEOUT = 1
                                                – SMBALERT = 1 */
            volatile uint16_t ITEVTEN : 1;   /* Event interrupt enable
                                                0: Event interrupt disabled
                                                1: Event interrupt enabled
                                                This interrupt is generated when:
                                                – SB = 1 (Master)
                                                – ADDR = 1 (Master/Slave)
                                                – ADD10= 1 (Master)
                                                – STOPF = 1 (Slave)
                                                – BTF = 1 with no TxE or RxNE event
                                                – TxE event to 1 if ITBUFEN = 1
                                                – RxNE event to 1if ITBUFEN = 1 */
            volatile uint16_t ITBUFEN : 1;   /* Buffer interrupt enable
                                                0: TxE = 1 or RxNE = 1 does not 
                                                generate any interrupt.
                                                1: TxE = 1 or RxNE = 1 generates Event 
                                                Interrupt (whatever the state of DMAEN) */
            volatile uint16_t DMAEN : 1;     /* DMA requests enable
                                                0: DMA requests disabled
                                                1: DMA request enabled when TxE=1 or RxNE =1 */
            volatile uint16_t LAST : 1; /* DMA last transfer
                                            0: Next DMA EOT is not the last transfer
                                            1: Next DMA EOT is the last transfer
                                            Note: This bit is used in master receiver mode to permit 
                                            the generation of a NACK on the last
                                            received data */
            const volatile uint16_t : 3;
        } I2C_CR2_b;
    };

    const volatile uint16_t RESERVED1;

    /* I2C Own address register 1 (I2C_OAR1) */
    union
    {
        volatile uint16_t I2C_OAR1;
        struct
        {
            volatile uint16_t ADD : 10;  /* Address in slave mode
                                          [0]: bit 0 of 10-bit address
                                          [7-1]: bits 7:1 of address
                                          [9-8]: bits9:8 of address of 10-bit adress */
            const volatile uint16_t : 5;
            volatile uint16_t ADDMODE : 1;   /* Addressing mode (slave mode)
                                            0: 7-bit slave address 
                                            (10-bit address not acknowledged)
                                            1: 10-bit slave address 
                                            (7-bit address not acknowledged) */
        } I2C_OAR1_b;
    };

    const volatile uint16_t RESERVED2;

    /* I2C Own address register 2 (I2C_OAR2) */
    union
    {
        volatile uint16_t I2C_OAR2;
        struct
        {
            volatile uint16_t ENDUAL : 1;   /* Dual addressing mode enable
                                                0: Only OAR1 is recognized in 7-bit 
                                                addressing mode
                                                1: Both OAR1 and OAR2 are recognized in 
                                                7-bit addressing mode */
            
            volatile uint16_t ADD2 : 7;  /* Interface address
                                            bits 7:1 of address in dual addressing mode */
            const volatile uint16_t : 8;
        } I2C_OAR2_b;
    };

    const volatile uint16_t RESERVED3;

    /* I2C Status register 1 (I2C_SR1) */
    union
    {
        volatile uint16_t I2C_SR1;
        struct
        {
            const volatile uint16_t SB : 1;   /* Start bit (Master mode)
                                            0: No Start condition
                                            1: Start condition generated.
                                            – Set when a Start condition generated.
                                            – Cleared by software by reading the SR1 
                                            register followed by writing the DR register, or by
                                            hardware when PE=0 */
            
            const volatile uint16_t ADDR : 1;  /* Address sent (master mode)/matched (slave mode)
                                                This bit is cleared by software reading SR1 register 
                                                followed reading SR2, or by hardware when PE=0.
                                                Address matched (Slave)
                                                0: Address mismatched or not received.
                                                1: Received address matched.
                                                – Set by hardware as soon as the received 
                                                slave address matched with the OAR registers
                                                content or a general call or a SMBus 
                                                Device Default Address or SMBus Host or SMBus Alert
                                                is recognized. (when enabled depending on configuration). */
            const volatile uint16_t BTF : 1; /* Byte transfer finished
                                                0: Data byte transfer not done
                                                1: Data byte transfer succeeded
                                                – Set by hardware when NOSTRETCH=0 and:
                                                – In reception when a new byte is received 
                                                (including ACK pulse) and DR has not 
                                                been read yet (RxNE=1).
                                                – In transmission when a new byte should be sent and DR has 
                                                not been written yet (TxE=1).
                                                – Cleared by software reading SR1 followed by either
                                                a read or write in the DR register or by
                                                hardware after a start or a stop condition in 
                                                transmission or when PE=0. */
            const volatile uint16_t ADD10 : 1; /* 10-bit header sent (Master mode)
                                                0: No ADD10 event occurred.
                                                1: Master has sent first address byte (header).
                                                – Set by hardware when the master has sent the 
                                                first byte in 10-bit address mode.
                                                – Cleared by software reading the SR1 register followed 
                                                by a write in the DR register of the
                                                second address byte, or by hardware when PE=0 */
            const volatile uint16_t STOPF : 1; /* Stop detection (slave mode)
                                                0: No Stop condition detected
                                                1: Stop condition detected
                                                – Set by hardware when a Stop condition is detected 
                                                on the bus by the slave after an
                                                acknowledge (if ACK=1).
                                                – Cleared by software reading the SR1 register 
                                                followed by a write in the CR1 register, or by
                                                hardware when PE=0 */
            const volatile uint16_t : 1;
            const volatile uint16_t RxNE : 1; /* Data register not empty (receivers)
                                                0: Data register empty
                                                1: Data register not empty
                                                – Set when data register is not empty 
                                                in receiver mode. RxNE is not set during address phase.
                                                – Cleared by software reading or writing the DR register or 
                                                by hardware when PE=0. RxNE is not set in case of ARLO event. */
            const volatile uint16_t TxE : 1; /* Data register empty (transmitters)
                                                0: Data register not empty
                                                1: Data register empty
                                                – Set when DR is empty in transmission. 
                                                TxE is not set during address phase.
                                                – Cleared by software writing to the DR register or 
                                                by hardware after a start or a stop condition
                                                or when PE=0.
                                                TxE is not set if either a NACK is received, or 
                                                if next byte to be transmitted is PEC (PEC=1) */
            volatile uint16_t BERR : 1;     /* Bus error
                                                0: No misplaced Start or Stop condition
                                                1: Misplaced Start or Stop condition
                                                – Set by hardware when the interface detects an SDA rising or 
                                                falling edge while SCL is high,
                                                occurring in a non-valid position during a byte transfer.
                                                – Cleared by software writing 0, or by hardware when PE=0. */
            volatile uint16_t ARLO : 1;     /* Arbitration lost (master mode)
                                                0: No Arbitration Lost detected
                                                1: Arbitration Lost detected
                                                Set by hardware when the interface loses the arbitration 
                                                of the bus to another master
                                                – Cleared by software writing 0, or by hardware when PE=0.
                                                After an ARLO event the interface switches back 
                                                automatically to Slave mode (MSL=0). */
            volatile uint16_t AF : 1;       /* Acknowledge failure
                                                0: No acknowledge failure
                                                1: Acknowledge failure
                                                – Set by hardware when no acknowledge is returned.
                                                – Cleared by software writing 0, or by hardware 
                                                when PE=0. */
            volatile uint16_t OVR : 1;   /* Overrun/Underrun
                                            0: No overrun/underrun
                                            1: Overrun or underrun
                                            – Set by hardware in slave mode when NOSTRETCH=1 and:
                                            – In reception when a new byte is received (including 
                                            ACK pulse) and the DR register has not
                                            been read yet. New received byte is lost.
                                            – In transmission when a new byte should be sent and 
                                            the DR register has not been written
                                            yet. The same byte is sent twice.
                                            – Cleared by software writing 0, or by hardware when PE=0 */
            volatile uint16_t PECERR : 1; /* PEC Error in reception
                                            0: no PEC error: receiver returns ACK 
                                            after PEC reception (if ACK=1)
                                            1: PEC error: receiver returns NACK 
                                            after PEC reception (whatever ACK) */
            const volatile uint16_t : 1;
            volatile uint16_t TIMEOUT : 1;   /* Timeout or Tlow error
                                                0: No timeout error
                                                1: SCL remained LOW for 25 ms (Timeout)
                                                or
                                                Master cumulative clock low extend time 
                                                more than 10 ms (Tlow:mext)
                                                or
                                                Slave cumulative clock low extend time 
                                                more than 25 ms (Tlow:sext)
                                                – When set in slave mode: slave resets the 
                                                communication and lines are released by hardware
                                                – When set in master mode: Stop condition sent by hardware
                                                – Cleared by software writing 0, or by hardware when PE=0 */
            volatile uint16_t SMBALERT : 1;  /* SMBus alert
                                                In SMBus host mode:
                                                0: no SMBALERT
                                                1: SMBALERT event occurred on pin
                                                In SMBus slave mode:
                                                0: no SMBALERT response address header
                                                1: SMBALERT response address header to 
                                                SMBALERT LOW received
                                                – Cleared by software writing 0, or by 
                                                hardware when PE=0. */
        } I2C_SR1_b;
    };

    const volatile uint16_t RESERVED4;

    /* I2C Status register 2 (I2C_SR2) */
    union
    {
        const volatile uint16_t I2C_SR2;
        struct
        {
            const volatile uint16_t MSL : 1; /* Master/slave
                                                0: Slave Mode
                                                1: Master Mode
                                                – Set by hardware as soon as the 
                                                interface is in Master mode (SB=1).
                                                – Cleared by hardware after detecting a Stop 
                                                condition on the bus or a loss of arbitration
                                                (ARLO=1), or by hardware when PE=0 */
            
            const volatile uint16_t BUSY : 1;  /* Bus busy
                                                0: No communication on the bus
                                                1: Communication ongoing on the bus
                                                – Set by hardware on detection of SDA or SCL low
                                                – cleared by hardware on detection of a Stop condition. */
            const volatile uint16_t TRA : 1; /* Transmitter/receiver
                                                0: Data bytes received
                                                1: Data bytes transmitted
                                                This bit is set depending on the 
                                                R/W bit of the address byte, at the end of total address
                                                phase.
                                                It is also cleared by hardware after detection 
                                                of Stop condition (STOPF=1), repeated Start
                                                condition, loss of bus arbitration (ARLO=1), or when PE=0. */
            const volatile uint16_t : 1;
            const volatile uint16_t GENCALL : 1; /* General call address (Slave mode)
                                                    0: No General Call
                                                    1: General Call Address received when ENGC=1
                                                    – Cleared by hardware after a Stop condition 
                                                    or repeated Start condition, or when PE=0. */
            const volatile uint16_t SMBDEFAULT : 1; /* SMBus device default address (Slave mode)
                                                        0: No SMBus Device Default address
                                                        1: SMBus Device Default address received when ENARP=1
                                                        – Cleared by hardware after a Stop condition or repeated 
                                                        Start condition, or when PE=0. */
            const volatile uint16_t SMBHOST : 1; /* SMBus host header (Slave mode)
                                                    0: No SMBus Host address
                                                    1: SMBus Host address received when SMBTYPE=1 and ENARP=1.
                                                    – Cleared by hardware after a Stop condition or repeated 
                                                    Start condition, or when PE=0. */
            const volatile uint16_t DUALF : 1;   /* Dual flag (Slave mode)
                                                    0: Received address matched with OAR1
                                                    1: Received address matched with OAR2
                                                    – Cleared by hardware after a Stop condition 
                                                    or repeated Start condition, or when PE=0 */
            const volatile uint16_t PEC : 8; /* Packet error checking register
                                                This register contains the internal PEC when ENPEC=1 */
        } I2C_SR2_b;
    };

    const volatile uint16_t RESERVED5;

    /* I2C Clock control register (I2C_CCR) */
    /* fPCLK1 must be at least 2 MHz to achieve Sm mode I²C frequencies. It must be at least 4
    MHz to achieve Fm mode I²C frequencies. It must be a multiple of 10MHz to reach the
    400 kHz maximum I²C Fm mode clock.
    The CCR register must be configured only when the I2C is disabled (PE = 0). */
    union
    {
        volatile uint16_t I2C_CCR;
        struct
        {
            volatile uint16_t CCR : 12;   /* Clock control register in Fm/Sm mode (Master mode)
                                            Controls the SCL clock in master mode.
                                            Sm mode or SMBus:
                                            Thigh = CCR * TPCLK1
                                            Tlow = CCR * TPCLK1
                                            Fm mode:
                                            If DUTY = 0:
                                            Thigh = CCR * TPCLK1
                                            Tlow = 2 * CCR * TPCLK1
                                            If DUTY = 1:
                                            Thigh = 9 * CCR * TPCLK1
                                            Tlow = 16 * CCR * TPCLK1
                                            For instance: in Sm mode, to generate a 100 kHz SCL frequency:
                                            If FREQ = 08, TPCLK1 = 125 ns so CCR must be programmed with 0x28
                                            (0x28 <=> 40d x 125 ns = 5000 ns.) */
            const volatile uint16_t : 2;
            volatile uint16_t DUTY : 1;  /* Fm mode duty cycle
                                            0: Fm mode tlow/thigh = 2
                                            1: Fm mode tlow/thigh = 16/9 (see CCR) */
            volatile uint16_t FS : 1; /* I2C master mode selection
                                        0: Sm mode I2C
                                        1: Fm mode I2C */
        } I2C_CCR_b;
    };

    const volatile uint16_t RESERVED6;

    /* I2C TRISE register (I2C_TRISE) */
    /* TRISE[5:0] must be configured only when the I2C is disabled (PE = 0) */
    union
    {
        volatile uint16_t I2C_TRISE;
        struct
        {
            volatile uint16_t TRISE : 6;   /* Maximum rise time in Fm/Sm mode (Master mode)
                                            These bits should provide the maximum duration of the SCL feedback 
                                            loop in master mode.
                                            The purpose is to keep a stable SCL frequency whatever the 
                                            SCL rising edge duration.
                                            These bits must be programmed with the maximum SCL 
                                            rise time given in the I2C bus
                                            specification, incremented by 1.
                                            For instance: in Sm mode, the maximum allowed SCL 
                                            rise time is 1000 ns.
                                            If, in the I2C_CR2 register, the value of FREQ[5:0] bits 
                                            is equal to 0x08 and TPCLK1 = 125 ns
                                            therefore the TRISE[5:0] bits must be programmed with 09h.
                                            (1000 ns / 125 ns = 8 + 1)
                                            The filter value can also be added to TRISE[5:0].
                                            If the result is not an integer, TRISE[5:0] must be programmed 
                                            with the integer part, in order
                                            to respect the tHIGH parameter. */
            const volatile uint16_t : 10;
        } I2C_TRISE_b;
    };

    const volatile uint16_t RESERVED7;
} I2Cx_Type;

#define I2C1_BASE        (0x40005400U)
#define I2C2_BASE        (0x40005800U)

#define I2C1 ((I2Cx_Type *)I2C1_BASE)
#define I2C2 ((I2Cx_Type *)I2C2_BASE)

#endif