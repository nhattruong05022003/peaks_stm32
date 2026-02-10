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

    /* DMA channel 1 configuration register (DMA_CCR1) */
    union
    {
        volatile uint32_t CCR1;
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
        } CCR1_b;
    };

    /* DMA channel 1 number of data register (DMA_CNDTR1) */
    union
    {
        /* This register can only be 
        written when the channel is disabled. Once the channel is enabled, 
        this register is read-only, indicating the remaining bytes to be transmitted. 
        This register decrements after each DMA transfer.
        Once the transfer is completed, this register can either stay at zero or be reloaded
        automatically by the value previously programmed if the channel is configured in autoreload mode.
        If this register is zero, no transaction can be served whether the channel is enabled or not.*/
        volatile uint32_t CNDTR1;
        struct
        {
            volatile uint32_t NDT : 16; /* Number of data to transfer. */
            const volatile uint32_t : 16;
        } CNDTR1_b;
    };

    /* DMA channel 1 peripheral address register (DMA_CPAR1) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CPAR1;
        struct
        {
            volatile uint32_t PA : 32; /* Peripheral address. Base address of the peripheral data register 
                                          from/to which the data will be read/written. */
        } CPAR1_b;
    };

    /* DMA channel 1 memory address register (DMA_CMAR1) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CMAR1;
        struct
        {
            volatile uint32_t MA : 32; /* Memory address. Base address of the memory address register 
                                          from/to which the data will be read/written. */
        } CMAR1_b;
    };

    const uint32_t RESERVED0;

    /* DMA channel 2 configuration register (DMA_CCR2) */
    union
    {
        volatile uint32_t CCR2;
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
        } CCR2_b;
    };

    /* DMA channel 2 number of data register (DMA_CNDTR2) */
    union
    {
        /* This register can only be 
        written when the channel is disabled. Once the channel is enabled, 
        this register is read-only, indicating the remaining bytes to be transmitted. 
        This register decrements after each DMA transfer.
        Once the transfer is completed, this register can either stay at zero or be reloaded
        automatically by the value previously programmed if the channel is configured in autoreload mode.
        If this register is zero, no transaction can be served whether the channel is enabled or not.*/
        volatile uint32_t CNDTR2;
        struct
        {
            volatile uint32_t NDT : 16; /* Number of data to transfer. */
            const volatile uint32_t : 16;
        } CNDTR2_b;
    };

    /* DMA channel 2 peripheral address register (DMA_CPAR2) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CPAR2;
        struct
        {
            volatile uint32_t PA : 32; /* Peripheral address. Base address of the peripheral data register 
                                          from/to which the data will be read/written. */
        } CPAR2_b;
    };

    /* DMA channel 2 memory address register (DMA_CMAR2) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CMAR2;
        struct
        {
            volatile uint32_t MA : 32; /* Memory address. Base address of the memory address register 
                                          from/to which the data will be read/written. */
        } CMAR2_b;
    };

    const uint32_t RESERVED1;

    /* DMA channel 3 configuration register (DMA_CCR3) */
    union
    {
        volatile uint32_t CCR3;
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
        } CCR3_b;
    };

    /* DMA channel 3 number of data register (DMA_CNDTR3) */
    union
    {
        /* This register can only be 
        written when the channel is disabled. Once the channel is enabled, 
        this register is read-only, indicating the remaining bytes to be transmitted. 
        This register decrements after each DMA transfer.
        Once the transfer is completed, this register can either stay at zero or be reloaded
        automatically by the value previously programmed if the channel is configured in autoreload mode.
        If this register is zero, no transaction can be served whether the channel is enabled or not.*/
        volatile uint32_t CNDTR3;
        struct
        {
            volatile uint32_t NDT : 16; /* Number of data to transfer. */
            const volatile uint32_t : 16;
        } CNDTR3_b;
    };

    /* DMA channel 3 peripheral address register (DMA_CPAR3) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CPAR3;
        struct
        {
            volatile uint32_t PA : 32; /* Peripheral address. Base address of the peripheral data register 
                                          from/to which the data will be read/written. */
        } CPAR3_b;
    };

    /* DMA channel 3 memory address register (DMA_CMAR3) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CMAR3;
        struct
        {
            volatile uint32_t MA : 32; /* Memory address. Base address of the memory address register 
                                          from/to which the data will be read/written. */
        } CMAR3_b;
    };

    const uint32_t RESERVED2;

    /* DMA channel 4 configuration register (DMA_CCR4) */
    union
    {
        volatile uint32_t CCR4;
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
        } CCR4_b;
    };

    /* DMA channel 4 number of data register (DMA_CNDTR4) */
    union
    {
        /* This register can only be 
        written when the channel is disabled. Once the channel is enabled, 
        this register is read-only, indicating the remaining bytes to be transmitted. 
        This register decrements after each DMA transfer.
        Once the transfer is completed, this register can either stay at zero or be reloaded
        automatically by the value previously programmed if the channel is configured in autoreload mode.
        If this register is zero, no transaction can be served whether the channel is enabled or not.*/
        volatile uint32_t CNDTR4;
        struct
        {
            volatile uint32_t NDT : 16; /* Number of data to transfer. */
            const volatile uint32_t : 16;
        } CNDTR4_b;
    };

    /* DMA channel 4 peripheral address register (DMA_CPAR4) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CPAR4;
        struct
        {
            volatile uint32_t PA : 32; /* Peripheral address. Base address of the peripheral data register 
                                          from/to which the data will be read/written. */
        } CPAR4_b;
    };

    /* DMA channel 4 memory address register (DMA_CMAR4) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CMAR4;
        struct
        {
            volatile uint32_t MA : 32; /* Memory address. Base address of the memory address register 
                                          from/to which the data will be read/written. */
        } CMAR4_b;
    };

    const uint32_t RESERVED3;

    /* DMA channel 5 configuration register (DMA_CCR5) */
    union
    {
        volatile uint32_t CCR5;
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
        } CCR5_b;
    };

    /* DMA channel 5 number of data register (DMA_CNDTR5) */
    union
    {
        /* This register can only be 
        written when the channel is disabled. Once the channel is enabled, 
        this register is read-only, indicating the remaining bytes to be transmitted. 
        This register decrements after each DMA transfer.
        Once the transfer is completed, this register can either stay at zero or be reloaded
        automatically by the value previously programmed if the channel is configured in autoreload mode.
        If this register is zero, no transaction can be served whether the channel is enabled or not.*/
        volatile uint32_t CNDTR5;
        struct
        {
            volatile uint32_t NDT : 16; /* Number of data to transfer. */
            const volatile uint32_t : 16;
        } CNDTR5_b;
    };

    /* DMA channel 5 peripheral address register (DMA_CPAR5) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CPAR5;
        struct
        {
            volatile uint32_t PA : 32; /* Peripheral address. Base address of the peripheral data register 
                                          from/to which the data will be read/written. */
        } CPAR5_b;
    };

    /* DMA channel 5 memory address register (DMA_CMAR5) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CMAR5;
        struct
        {
            volatile uint32_t MA : 32; /* Memory address. Base address of the memory address register 
                                          from/to which the data will be read/written. */
        } CMAR5_b;
    };

    const uint32_t RESERVED4;

    /* DMA channel 6 configuration register (DMA_CCR6) */
    union
    {
        volatile uint32_t CCR6;
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
        } CCR6_b;
    };

    /* DMA channel 6 number of data register (DMA_CNDTR6) */
    union
    {
        /* This register can only be 
        written when the channel is disabled. Once the channel is enabled, 
        this register is read-only, indicating the remaining bytes to be transmitted. 
        This register decrements after each DMA transfer.
        Once the transfer is completed, this register can either stay at zero or be reloaded
        automatically by the value previously programmed if the channel is configured in autoreload mode.
        If this register is zero, no transaction can be served whether the channel is enabled or not.*/
        volatile uint32_t CNDTR6;
        struct
        {
            volatile uint32_t NDT : 16; /* Number of data to transfer. */
            const volatile uint32_t : 16;
        } CNDTR6_b;
    };

    /* DMA channel 6 peripheral address register (DMA_CPAR6) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CPAR6;
        struct
        {
            volatile uint32_t PA : 32; /* Peripheral address. Base address of the peripheral data register 
                                          from/to which the data will be read/written. */
        } CPAR6_b;
    };

    /* DMA channel 6 memory address register (DMA_CMAR6) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CMAR6;
        struct
        {
            volatile uint32_t MA : 32; /* Memory address. Base address of the memory address register 
                                          from/to which the data will be read/written. */
        } CMAR6_b;
    };

    const uint32_t RESERVED5;

    /* DMA channel 7 configuration register (DMA_CCR7) */
    union
    {
        volatile uint32_t CCR7;
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
        } CCR7_b;
    };

    /* DMA channel 7 number of data register (DMA_CNDTR7) */
    union
    {
        /* This register can only be 
        written when the channel is disabled. Once the channel is enabled, 
        this register is read-only, indicating the remaining bytes to be transmitted. 
        This register decrements after each DMA transfer.
        Once the transfer is completed, this register can either stay at zero or be reloaded
        automatically by the value previously programmed if the channel is configured in autoreload mode.
        If this register is zero, no transaction can be served whether the channel is enabled or not.*/
        volatile uint32_t CNDTR7;
        struct
        {
            volatile uint32_t NDT : 16; /* Number of data to transfer. */
            const volatile uint32_t : 16;
        } CNDTR7_b;
    };

    /* DMA channel 7 peripheral address register (DMA_CPAR7) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CPAR7;
        struct
        {
            volatile uint32_t PA : 32; /* Peripheral address. Base address of the peripheral data register 
                                          from/to which the data will be read/written. */
        } CPAR7_b;
    };

    /* DMA channel 7 memory address register (DMA_CMAR7) */
    union
    {
        /* This register must not be written when the channel is enabled */

        volatile uint32_t CMAR7;
        struct
        {
            volatile uint32_t MA : 32; /* Memory address. Base address of the memory address register 
                                          from/to which the data will be read/written. */
        } CMAR7_b;
    };

    const uint32_t RESERVED6;
} DMAx_Type;

#define DMA1_BASE        (0x40020000U)
#define DMA2_BASE        (0x40020400U)

#define DMA1 ((DMAx_Type *)DMA1_BASE)
#define DMA2 ((DMAx_Type *)DMA2_BASE)

#endif