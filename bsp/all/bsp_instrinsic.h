#ifndef _BSP_INSTRINSIC_H_
#define _BSP_INSTRINSIC_H_

#include "bsp_common.h"

/* Intrinsic functions */
#define __enable_interrupt()    __asm volatile("CPSIE I") /* Enable interrupt */
#define __disable_interrupt()   __asm volatile("CPSID I") /* Disbale interrupt */
#define __enable_fault_irq()    __asm volatile("CPSIE F") /* Enable fault interrupt */
#define __disable_fault_irq()   __asm volatile("CPSID F") /* Disable fault interrupt */

#define __ISB()                 __asm volatile("ISB") /* Instruction Synchronization Barrier. Ensures Context. (CPU flushes its brain/pipeline and re-reads code). */
#define __DSB()                 __asm volatile("DSB") /* Data Synchronization Barrier. Ensures Completion. (CPU stops and waits until all memory is quiet). */
#define __DMB()                 __asm volatile("DMB") /* Data Memory Barrier. Ensures Order. (A must finish before B starts, but CPU keeps running).*/
#define __SEV()                 __asm volatile("SEV") /* Send Event */
#define __WFE()                 __asm volatile("WFE") /* Wait for Event */
#define __WFI()                 __asm volatile("WFI") /* Wait for Interrupt */

/**********************************************************************************************************************
 * @brief Get value of xPSR register.
 *
 * @return Value of xPSR register.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __get_xPSR (void)
{
    uint32_t result;
    __asm volatile("MRS %0, PSR":"=r"(result):);
    return result;
}

/**********************************************************************************************************************
 * @brief Write value to xPSR register.
 *
 * @param value: Value need to be written to xPSR register
 * 
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void __set_xPSR (uint32_t value)
{
    __asm volatile("MSR PSR, %0"::"r"(value));
}

/**********************************************************************************************************************
 * @brief Get value of PRIMASK register.
 *
 * @return Value of PRIMASK register.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __get_PRIMASK (void)
{
    uint32_t result;
    __asm volatile("MRS %0, PRIMASK":"=r"(result):);
    return result;
}

/**********************************************************************************************************************
 * @brief Write value to PRIMASK register.
 *
 * @param value: Value need to be written to PRIMASK register
 * 
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void __set_PRIMASK (uint32_t value)
{
    __asm volatile("MSR PRIMASK, %0"::"r"(value));
}

/**********************************************************************************************************************
 * @brief Get value of FAULTMASK register.
 *
 * @return Value of FAULTMASK register.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __get_FAULTMASK (void)
{
    uint32_t result;
    __asm volatile("MRS r0, FAULTMASK":"=r"(result):);
    return result;
}

/**********************************************************************************************************************
 * @brief Write value to FAULTMASK register.
 *
 * @param value: Value need to be written to FAULTMASK register
 * 
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void __set_FAULTMASK (uint32_t value)
{
    __asm volatile("MSR FAULTMASK, %0"::"r"(value));
}

/**********************************************************************************************************************
 * @brief Get value of BASEPRI register.
 *
 * @return Value of BASEPRI register.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __get_BASEPRI (void)
{
    uint32_t result;
    __asm volatile("MRS r0, PRIMASK":"=r"(result):);
    return result;
}

/**********************************************************************************************************************
 * @brief Write value to BASEPRI register.
 *
 * @param value: Value need to be written to BASEPRI register
 * 
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void __set_BASEPRI (uint32_t value)
{
    __asm volatile("MSR BASEPRI, %0"::"r"(value));
}

/**********************************************************************************************************************
 * @brief Get value of CONTROL register.
 *
 * @return Value of CONTROL register.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __get_CONTROL (void)
{
    uint32_t result;
    __asm volatile("MRS r0, CONTROL":"=r"(result):);
    return result;
}

/**********************************************************************************************************************
 * @brief Write value to CONTROL register.
 *
 * @param value: Value need to be written to CONTROL register
 * 
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void __set_CONTROL (uint32_t value)
{
    __asm volatile("MSR CONTROL, %0"::"r"(value));
}

/**********************************************************************************************************************
 * @brief Get value of MSP register.
 *
 * @return Value of MSP register.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __get_MSP (void)
{
    uint32_t result;
    __asm volatile("MRS r0, MSP":"=r"(result):);
    return result;
}

/**********************************************************************************************************************
 * @brief Write value to MSP register.
 *
 * @param value: Value need to be written to MSP register
 * 
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void  __set_MSP (uint32_t TopOfMainStack)
{
    __asm volatile("MSR MSP, %0"::"r"(TopOfMainStack));
}

/**********************************************************************************************************************
 * @brief Get value of PSP register.
 *
 * @return Value of PSP register.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __get_PSP (void)
{
    uint32_t result;
    __asm volatile("MRS r0, MSP":"=r"(result):);
    return result;
}

/**********************************************************************************************************************
 * @brief Write value to PSP register.
 *
 * @param value: Value need to be written to PSP register
 * 
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void  __set_PSP (uint32_t TopOfMainStack)
{
    __asm volatile("MSR PSP, %0"::"r"(TopOfMainStack));
}

/**********************************************************************************************************************
 * @brief Reverses the byte order in a 32-bit word. It swaps the position of all four bytes.
 *
 * @param value: Value need to be reversed.
 * 
 * @return Value after reversed.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __REV(uint32_t value)
{
  uint32_t result;
  __asm volatile ("rev %0, %1" : "=r" (result) : "r" (value));
  return result;
}

/**********************************************************************************************************************
 * @brief Reverses the byte order in each 16-bit halfword independently.
 *
 * @param value: Value need to be reversed.
 * 
 * @return Value after reversed.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __REV16(uint32_t value)
{
  uint32_t result;
  __asm volatile ("rev16 %0, %1" : "=r" (result) : "r" (value));
  return result;
}

/**********************************************************************************************************************
 * @brief Reverses the byte order in the lower 16 bits (a halfword) and then sign-extends the result to 32 bits.
 *
 * @param value: Value need to be reversed.
 * 
 * @return Value after reversed.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE int32_t __REVSH(int32_t value)
{
  int32_t result;
  __asm volatile ("revsh %0, %1" : "=r" (result) : "r" (value));
  return result;
}

/**********************************************************************************************************************
 * @brief Reverses the bit order of a 32-bit word. The bit at position 0 moves to 31, bit 1 to 30, and so on.
 *
 * @param value: Value need to be reversed.
 * 
 * @return Value after reversed.
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE uint32_t __RBIT(uint32_t value)
{
  uint32_t result;
  __asm volatile ("rbit %0, %1" : "=r" (result) : "r" (value));
  return result;
}

#endif
