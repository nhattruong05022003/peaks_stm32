#ifndef _CORTEX_M3_H_
#define _CORTEX_M3_H_

#include <stdint.h>

/**********************************************************************************************************************
 *                                                      SCB
 **********************************************************************************************************************/

typedef struct SCB_Type_t
{
    /* CPUID base register (CPUID) 0x00 */
    union
    {
        volatile uint32_t CPUID;
        struct
        {
            volatile const uint32_t Revision : 4;
            volatile const uint32_t PartNo : 12; /* 0xC23: = Cortex-M3 */
            volatile const uint32_t : 4;
            volatile const uint32_t Variant : 4;
            volatile const uint32_t Implementer : 8; /* 0x41: ARM */
        } CPUID_b;
    };

    /* Interrupt control and state register (ICSR) 0x04 */
    /*
    The ICSR:
    • Provides:
    – A set-pending bit for the Non-Maskable Interrupt (NMI) exception
    – Set-pending and clear-pending bits for the PendSV and SysTick exceptions
    • Indicates:
    – The exception number of the exception being processed
    – Whether there are preempted active exceptions
    – The exception number of the highest priority pending exception
    – Whether any interrupts are pending
    */
    union
    {
        volatile uint32_t ICSR;
        struct
        {
            volatile uint32_t VECTACTIVE : 9;           /* Contains the active exception number:
                                                        0: Thread mode
                                                        Other values: 
                                                        The exception number(1) of the currently active exception.
                                                        */
            volatile const uint32_t : 2;
            volatile const uint32_t RETOBASE : 1;       /* Indicates whether there are preempted active exceptions:
                                                        0: There are preempted active exceptions to execute
                                                        1: There are no active exceptions,
                                                        or the currently-executing exception is the only active
                                                        exception.
                                                        */
            volatile const uint32_t VECTPENDING : 10;   /* Indicates the exception number of the highest priority 
                                                        pending enabled exception.
                                                        0: No pending exceptions
                                                        Other values: The exception number of 
                                                        the highest priority pending enabled exception.
                                                        The value indicated by this field includes 
                                                        the effect of the BASEPRI and FAULTMASK
                                                        registers, but not any effect of the PRIMASK register
                                                        */
            volatile const uint32_t ISRPENDING : 1;     /*  Interrupt pending flag, excluding NMI and Faults
                                                        0: Interrupt not pending
                                                        1: Interrupt pending
                                                        */
            volatile const uint32_t : 2;
            volatile uint32_t PENDSTCLR : 1;            /* SysTick exception clear-pending bit.
                                                        Write:
                                                        0: No effect
                                                        1: Removes the pending state from the SysTick exception.
                                                        */
            volatile uint32_t PENDSTSET : 1;            /* SysTick exception set-pending bit.
                                                        Write:
                                                        0: No effect
                                                        1: Change SysTick exception state to pending
                                                        Read:
                                                        0: SysTick exception is not pending
                                                        1: SysTick exception is pending
                                                        */
            volatile uint32_t PENDSVCLR : 1;            /* PendSV clear-pending bit.
                                                        Write:
                                                        0: No effect
                                                        1: Removes the pending state from the PendSV exception
                                                        */
            volatile uint32_t PENDSVSET : 1;            /* PendSV set-pending bit.
                                                        Write:
                                                        0: No effect
                                                        1: Change PendSV exception state to pending.
                                                        Read:
                                                        0: PendSV exception is not pending
                                                        1: PendSV exception is pending
                                                        Writing 1 to this bit is the only way to set the PendSV 
                                                        exception state to pending
                                                        */
            volatile const uint32_t : 2;
            volatile uint32_t NMIPENDSET : 1;           /* NMI set-pending bit.
                                                        Write:
                                                        0: No effect
                                                        1: Change NMI exception state to pending.
                                                        Read:
                                                        0: NMI exception is not pending
                                                        1: NMI exception is pending
                                                        Because NMI is the highest-priority exception, 
                                                        normally the processor enter the NMI
                                                        exception handler as soon as it registers a write of 1 to this bit, 
                                                        and entering the handler clears
                                                        this bit to 0. A read of this bit by the NMI exception handler returns 
                                                        1 only if the NMI signal is
                                                        reasserted while the processor is executing that handler.
                                                        */
        } ICSR_b;
    };

    /* Vector table offset register (VTOR) 0x08 */
    union
    {
        volatile uint32_t VTOR;
        struct
        {
            volatile const uint32_t : 9;
            volatile uint32_t TBLOFF : 21;  /* Vector table base offset field.
                                            It contains bits [29:9] of the offset of the table base from memory address 0x00000000. When
                                            setting TBLOFF, you must align the offset to the number of exception entries in the vector
                                            table. The minimum alignment is 128 words. Table alignment requirements mean that bits[8:0]
                                            of the table offset are always zero.
                                            Bit 29 determines whether the vector table is in the code or SRAM memory region.
                                            0: Code
                                            1: SRAM
                                            */
            volatile const uint32_t : 2;
        } VTOR_b;
    };

    /* Application interrupt and reset control register (AIRCR) 0x0C */
    union
    {
        volatile uint32_t AIRCR;
        struct
        {
            volatile const uint32_t : 2;
            volatile uint32_t SYSRESETREQ : 1;  /* Vector table base offset field.
                                                This is intended to force a large system reset of 
                                                all major components except for debug.
                                                This bit reads as 0.
                                                0: No system reset request
                                                1: Asserts a signal to the outer system that requests a reset.
                                                */
            volatile const uint32_t : 5;
            volatile uint32_t PRIGROUP : 3;     /* Interrupt priority grouping field
                                                This field determines the split of group priority from subpriority
                                                */
            volatile const uint32_t : 4;
            volatile uint32_t ENDIANESS : 1;    /* Data endianness bit
                                                Reads as 0.
                                                0: Little-endian
                                                */
            volatile uint32_t VECTKEY : 16;     /* Register key
                                                Reads as 0xFA05
                                                On writes, write 0x5FA to VECTKEY, otherwise the write is ignored.
                                                */
        } AIRCR_b;
    };

    /* System control register (SCR) 0x10 */
    union
    {
        volatile uint32_t SCR;
        struct
        {
            volatile const uint32_t : 1;
            volatile uint32_t SLEEPONEXIT : 1;  /* Configures sleep-on-exit when returning from Handler mode to Thread mode. 
                                                Setting this bit to
                                                1 enables an interrupt-driven application to avoid returning 
                                                to an empty main application.
                                                0: Do not sleep when returning to Thread mode.
                                                1: Enter sleep, or deep sleep, on return from an interrupt service routine.
                                                */
            volatile uint32_t SLEEPDEEP : 1;    /* Controls whether the processor uses sleep or deep sleep as its low power mode:
                                                0: Sleep
                                                1: Deep sleep.
                                                */
            volatile const uint32_t : 1;
            volatile uint32_t SEVEONPEND : 1;   /* When an event or interrupt enters pending state, 
                                                the event signal wakes up the processor from
                                                WFE. If the processor is not waiting for an event, 
                                                the event is registered and affects the next WFE.
                                                The processor also wakes up on execution of an SEV instruction or an external event
                                                0: Only enabled interrupts or events can wakeup the processor, disabled interrupts are
                                                excluded
                                                1: Enabled events and all interrupts, including disabled interrupts, can wakeup the
                                                processor
                                                */
            volatile const uint32_t : 27;
        } SCR_b;
    };

    /* Configuration and control register (CCR) 0x14 */
    union
    {
        volatile uint32_t CCR;
        struct
        {
            volatile const uint32_t : 1;
            volatile uint32_t NONBASETHRDENA : 1;   /* Configures how the processor enters Thread mode.
                                                    0: Processor can enter Thread mode only when no exception is active.
                                                    1: Processor can enter Thread mode from any level under the control of an EXC_RETURN
                                                    */
            volatile uint32_t USERSETMPEND : 1;     /* Enables unprivileged software access to the STIR
                                                    0: Disable
                                                    1: Enable
                                                    */
            volatile const uint32_t : 1;
            volatile uint32_t UNALIGN_TRP : 1;      /* Enables unaligned access traps:
                                                    0: Do not trap unaligned halfword and word accesses
                                                    1: Trap unaligned halfword and word accesses
                                                    */
            volatile uint32_t DIV_0_TRP : 1;        /* Enables faulting or halting when the processor executes 
                                                    an SDIV or UDIV instruction with a
                                                    divisor of 0:
                                                    0: Do not trap divide by 0
                                                    1: Trap divide by 0
                                                    */
            volatile const uint32_t : 3;
            volatile uint32_t BFHFNMIGN : 1;        /* Enables handlers with priority -1 or -2 to ignore data bus faults caused by 
                                                    load and store instructions. This applies to the hard fault, 
                                                    NMI, and FAULTMASK escalated handlers. Set this bit to 1 only when the handler 
                                                    and its data are in absolutely safe memory. The normal use of this bit is to probe 
                                                    system devices and bridges to detect control path problems and fix them.
                                                    0: Data bus faults caused by load and store instructions cause a lock-up
                                                    1: Handlers running at priority -1 and -2 ignore data bus faults caused by load and store
                                                    instructions.
                                                    */
            volatile const uint32_t : 12;
        } CCR_b;
    };

    /* System handler priority register 1 (SHPR1) 0x18 */
    union
    {
        volatile uint32_t SHPR1;
        struct
        {
            volatile uint32_t PRI_4 : 8;   /* Priority of system handler 4, memory management fault. */
            volatile uint32_t PRI_5 : 8;   /* Priority of system handler 5, bus fault */
            volatile uint32_t PRI_6 : 8;   /* Priority of system handler 6, usage fault */
            volatile const uint32_t : 8;
        } SHPR1_b;
    };

    /* System handler priority register 2 (SHPR2) 0x1C */
    union
    {
        volatile uint32_t SHPR2;
        struct
        {
            volatile const uint32_t : 24;
            volatile uint32_t PRI_11 : 8;   /* Priority of system handler 11, SVCall */            
        } SHPR2_b;
    };

    /* System handler priority register 3 (SHPR3) 0x20 */
    union
    {
        volatile uint32_t SHPR3;
        struct
        {
            volatile const uint32_t : 16;
            volatile uint32_t PRI_14 : 8;   /* Priority of system handler 14, PendSV */
            volatile uint32_t PRI_15 : 8;   /* Priority of system handler 15, SysTick exception */
        } SHPR3_b;
    };

    /* System handler control and state register (SHCSR) 0x24 */
    /*
    The SHCSR enables the system handlers, and indicates:
    • The pending status of the bus fault, memory management fault, and SVC exceptions
    • The active status of the system handlers.
    If you disable a system handler and the corresponding fault occurs, the processor treats the
    fault as a hard fault.
    You can write to this register to change the pending or active status of system exceptions.
    An OS kernel can write to the active bits to perform a context switch that changes the
    current exception type.
    • Software that changes the value of an active bit in this register without correct
    adjustment to the stacked content can cause the processor to generate a fault
    exception. Ensure software that writes to this register retains and subsequently
    restores the current active status.
    • After you have enabled the system handlers, if you have to change the value of a bit in
    this register you must use a read-modify-write procedure to ensure that you change
    only the required bit.
    */
    union
    {
        volatile uint32_t SHCSR;
        struct
        {
            volatile uint32_t MEMFAULTACT : 1;       /* Memory management fault exception active bit, reads as 1 if exception is active */
            volatile uint32_t BUSFAULTACT : 1;       /* Bus fault exception active bit, reads as 1 if exception is active */
            volatile const uint32_t : 1;
            volatile uint32_t USGFAULTACT : 1;       /* Usage fault exception active bit, reads as 1 if exception is active */
            volatile const uint32_t : 3;
            volatile uint32_t SVCALLACT : 1;         /* SVC call active bit, reads as 1 if SVC call is active */
            volatile uint32_t MONITORACT : 1;        /* Debug monitor active bit, reads as 1 if Debug monitor is active */
            volatile const uint32_t : 1;
            volatile uint32_t PENDSVACT : 1;         /* PendSV exception active bit, reads as 1 if exception is active */
            volatile uint32_t SYSTICKACT : 1;        /* SysTick exception active bit, reads as 1 if exception is active */
            volatile uint32_t USGFAULTPENDED : 1;    /* Usage fault exception pending bit, reads as 1 if exception is pending */
            volatile uint32_t MEMFAULTPENDED : 1;    /* Memory management fault exception pending bit, reads as 1 if exception is pending */
            volatile uint32_t BUSFAULTPENDED : 1;    /* Bus fault exception pending bit, reads as 1 if exception is pending */
            volatile uint32_t SVCALLPENDED : 1;      /* SVC call pending bit, reads as 1 if exception is pending */
            volatile uint32_t MEMFAULTENA : 1;       /* Memory management fault enable bit, set to 1 to enable */
            volatile uint32_t BUSFAULTENA : 1;       /* Bus fault enable bit, set to 1 to enable */
            volatile uint32_t USGFAULTENA : 1;       /*  Usage fault enable bit, set to 1 to enable */
            volatile const uint32_t : 13;
        } SHCSR_b;
    };

    /* Configurable fault status register (CFSR) 0x28 */
    union
    {
        volatile uint32_t CFSR;
        struct
        {
            volatile uint32_t IACCVIOL : 1;          /* Instruction access violation flag */
            volatile uint32_t DACCVIOL : 1;          /* Data access violation flag */
            volatile const uint32_t : 1;
            volatile uint32_t MUNSTKERR : 1;         /* Memory manager fault on unstacking for a return from exception */
            volatile uint32_t MSTKERR : 1;           /* Memory manager fault on stacking for exception entry */
            volatile const uint32_t : 2;
            volatile uint32_t MMARVALID : 1;         /* Memory Management Fault Address Register (MMAR) valid flag */
            volatile uint32_t IBUSERR : 1;           /* Instruction bus error */
            volatile uint32_t PRECISERR : 1;         /* Precise data bus error */
            volatile uint32_t IMPRECISERR : 1;       /* Imprecise data bus error */
            volatile uint32_t UNSTKERR : 1;          /* Bus fault on unstacking for a return from exception */
            volatile uint32_t STKERR : 1;            /* Bus fault on stacking for exception entry */
            volatile const uint32_t : 2;
            volatile uint32_t BFARVALID : 1;         /* Bus Fault Address Register (BFAR) valid flag */
            volatile uint32_t UNDEFINSTR : 1;        /* Undefined instruction usage fault */
            volatile uint32_t INVSTATE : 1;          /* Invalid state usage fault */
            volatile uint32_t INVPC : 1;             /* Invalid PC load usage fault, caused by an invalid PC load by EXC_RETURN */
            volatile uint32_t NOCP : 1;              /* No coprocessor usage fault. The processor does not support coprocessor instructions */
            volatile const uint32_t : 4;
            volatile uint32_t UNALIGNED : 1;         /* Unaligned access usage fault */
            volatile uint32_t DIVBYZERO : 1;         /* Divide by zero usage fault */
            volatile const uint32_t : 6;
        } CFSR_b;
    };

    /* Hard fault status register (HFSR) 0x2C */
    union
    {
        volatile uint32_t HFSR;
        struct
        {
            volatile const uint32_t : 1;
            volatile uint32_t VECTTBL : 1;           /* Vector table hard fault */
            volatile const uint32_t : 28;
            volatile uint32_t FORCED : 1;            /* Forced hard fault */
            volatile uint32_t DEBUG_VT : 1;          /* Reserved for Debug use. When writing to the register you 
                                                     must write 0 to this bit, otherwise behavior is unpredictable. */
        } HFSR_b;
    };

    volatile const uint32_t RESERVED0; /* 0x30 */

    /* Memory management fault address register (MMFAR) 0x34 */
    /*
    When the MMARVALID bit of the MMFSR is set to 1, this field holds the address of the
    location that generated the memory management fault.
    When an unaligned access faults, the address is the actual address that faulted. Because a
    single read or write instruction can be split into multiple aligned accesses, the fault address
    can be any address in the range of the requested access size
    */
    union
    {
        volatile uint32_t MMFAR;
        struct
        {
            volatile uint32_t MMFAR : 32;
        } MMFAR_b;
    };

    /* Bus fault address register (BFAR) 0x38 */
    /*
    When the BFARVALID bit of the BFSR is set to 1, this field holds the address of the location
    that generated the bus fault.
    When an unaligned access faults the address in the BFAR is the one requested by the
    instruction, even if it is not the address of the fault.
    */
    union
    {
        volatile uint32_t BFAR;
        struct
        {
            volatile uint32_t BFAR : 32;
        } BFAR_b;
    };
} SCB_Type;

#define SCB_BASE (0xE000ED00U)

#define SCB ((SCB_Type *)SCB_BASE)

/**********************************************************************************************************************
 *                                                      SysTick
 **********************************************************************************************************************/

typedef struct SysTick_Type_t
{
    /* SysTick control and status register (STK_CTRL) 0x00 */
    union
    {
        volatile uint32_t STK_CTRL;
        struct
        {
            volatile uint32_t ENABLE : 1; /*  Enables the counter. When ENABLE is set to 1, the counter loads 
                                                    the RELOAD value from the LOAD register and then counts down. 
                                                    On reaching 0, it sets the COUNTFLAG to 1 and
                                                    optionally asserts the SysTick depending on the value of TICKINT. 
                                                    It then loads the RELOAD
                                                    value again, and begins counting.
                                                    0: Counter disabled
                                                    1: Counter enabled
                                                */
            volatile uint32_t TICKINT : 1; /*   0: Counting down to zero does not assert the SysTick exception request
                                                1: Counting down to zero to asserts the SysTick exception request.*/
            volatile uint32_t CLKSOURCE : 1;    /*  Selects the clock source.
                                                    0: AHB/8
                                                    1: Processor clock (AHB)
                                                */
            volatile const uint32_t : 13;
            
            volatile uint32_t COUNTFLAG : 1; /* Returns 1 if timer counted to 0 since last time this was read */
            volatile const uint32_t : 15;
        } STK_CTRL_b;
    };

    /* SysTick reload value register (STK_LOAD) 0x04 */
    union
    {
        volatile uint32_t STK_LOAD;
        struct
        {
            volatile uint32_t RELOAD : 24;  /*  The LOAD register specifies the start value to load into the VAL register 
                                                when the counter is enabled and when it reaches 0.
                                                Calculating the RELOAD value
                                                The RELOAD value can be any value in the range 0x00000001-0x00FFFFFF. A start value of
                                                0 is possible, but has no effect because the SysTick exception request and COUNTFLAG are
                                                activated when counting from 1 to 0.
                                                The RELOAD value is calculated according to its use:
                                                - To generate a multi-shot timer with a period of N processor clock cycles, use a RELOAD
                                                value of N-1. For example, if the SysTick interrupt is required every 100 clock pulses, set
                                                RELOAD to 99.
                                                - To deliver a single SysTick interrupt after a delay of N processor clock cycles, use a
                                                RELOAD of value N. For example, if a SysTick interrupt is required after 400 clock
                                                pulses, set RELOAD to 400.
                                            */
            volatile const uint32_t : 8;
        } STK_LOAD_b;
    };

    /* SysTick current value register (STK_VAL) 0x08 */
    union
    {
        volatile uint32_t STK_VAL;
        struct
        {
            volatile uint32_t CURRENT : 24;  /*  The LOAD register specifies the start value to load into the VAL register 
                                                when the counter is enabled and when it reaches 0.
                                                Calculating the RELOAD value
                                                The RELOAD value can be any value in the range 0x00000001-0x00FFFFFF. A start value of
                                                0 is possible, but has no effect because the SysTick exception request and COUNTFLAG are
                                                activated when counting from 1 to 0.
                                                The RELOAD value is calculated according to its use:
                                                - To generate a multi-shot timer with a period of N processor clock cycles, use a RELOAD
                                                value of N-1. For example, if the SysTick interrupt is required every 100 clock pulses, set
                                                RELOAD to 99.
                                                - To deliver a single SysTick interrupt after a delay of N processor clock cycles, use a
                                                RELOAD of value N. For example, if a SysTick interrupt is required after 400 clock
                                                pulses, set RELOAD to 400.
                                            */
            volatile const uint32_t : 8;
        } STK_VAL_b;
    };

    /* SysTick calibration value register (STK_CALIB) 0x0C */
    union
    {
        volatile uint32_t STK_CALIB;
        struct
        {
            volatile uint32_t TENMS : 24;   /*  Indicates the calibration value when the SysTick counter runs on HCLK max/8 as external
                                                clock. The value is product dependent, please refer to the Product Reference Manual, SysTick
                                                Calibration Value section. When HCLK is programmed at the maximum frequency, the SysTick
                                                period is 1ms.
                                                If calibration information is not known, calculate the calibration value required from the
                                                frequency of the processor clock or external clock.
                                            */
            volatile const uint32_t : 6;
            volatile const uint32_t SKEW : 1; /*Reads as one. Calibration value for the 1 ms inexact timing is not known because TENMS is
                                                not known. This can affect the suitability of SysTick as a software real time clock.*/
            volatile const uint32_t NOREF : 1;  /* Reads as zero. Indicates that a separate reference clock is provided. The frequency of this
                                                clock is HCLK/8. */
        } STK_CALIB_b;
    };
} SysTick_Type;

#define SysTick_BASE (0xE000E010U)

#define SysTick ((SysTick_Type *)SysTick_BASE)

/**********************************************************************************************************************
 *                                                      NVIC
 **********************************************************************************************************************/

typedef struct NVIC_Type_t
{
    /* Interrupt set-enable registers (NVIC_ISERx) */
    volatile uint32_t ISER[3]; /* 0x00 - 0x0B */
    volatile const uint32_t REVERSED0[29]; /* 0x0C - 0x7C */

    /* Interrupt clear-enable registers (NVIC_ICERx) */
    volatile uint32_t ICER[3]; /* 0x80 - 0x8B */
    volatile const uint32_t REVERSED1[29]; /* 0x8C - 0xFC */

    /* Interrupt set-pending registers (NVIC_ISPRx) */
    volatile uint32_t ISPR[3]; /* 0x100 - 0x10B */
    volatile const uint32_t REVERSED2[29]; /* 0x10C - 0x17C */

    /* Interrupt clear-pending registers (NVIC_ICPRx) */
    volatile uint32_t ICPR[3]; /* 0x180 - 0x18B */
    volatile const uint32_t REVERSED3[29]; /* 0x18C - 0x1FC */

    /* Interrupt active bit registers (NVIC_IABRx) */
    volatile uint32_t IABR[3]; /* 0x200 - 0x20B */
    volatile const uint32_t REVERSED4[61]; /* 0x20C - 0x2FC */

    /* Interrupt priority registers (NVIC_IPRx) */
    volatile uint8_t IPR[68]; /* 0x300 - 0x343 */
    volatile const uint32_t REVERSED5[687]; /* 0x344 - 0xDFC */

    /* Software trigger interrupt register (NVIC_STIR) */
    volatile uint32_t STIR; /* 0xE00 */
} NVIC_Type;

#define NVIC_BASE (0xE000E100U)

#define NVIC ((NVIC_Type *)NVIC_BASE)

#endif
