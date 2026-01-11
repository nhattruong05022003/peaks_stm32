#ifndef _BSP_MPU_H_
#define _BSP_MPU_H_

#include "bsp_api.h"

#if (BSP_FEATURE_MPU_IS_AVAILABLE)

/**
 * @brief Struct contains infor of MPU region's attribute.
 * Please refer the Cortex M3 document for more detail 
 * about these element in this struct.
 */
typedef struct st_bsp_mpu_attr
{
    union
    {
        uint16_t attr_value;
        struct
        {
            uint16_t b_bit : 1;
            uint16_t c_bit : 1;
            uint16_t s_bit : 1;
            uint16_t tex : 3;
            const uint16_t : 2;
            uint16_t access_permision : 3;
            const uint16_t : 1;
            uint16_t xn_bit : 1;
            const uint16_t : 1;
        } attr_value_b;
    };
} bsp_mpu_attr_t;

/**
 * @brief Struct contains infor of MPU region
 */
typedef struct st_bsp_mpu_region
{
    uint32_t base_address; /* base address must align with size */
    bsp_mpu_attr_t attr;
    uint8_t size; /* Size of region = 2 ^ (size + 1) 
                     (min = 5, max = 32) -> (min size = 4, max size = 31) */
    uint8_t enable;
    uint8_t no_region;
} bsp_mpu_region_t;

/**********************************************************************************************************************
 * @brief Enable MPU
 *
 * @param priv_defend_enable: Param specific whether privileged software access is allowed to
 *                            a location that is not covered by any enabled region.
 * @param hf_nmi_enable: Param specific whether the operation of MPU during hard fault, NMI, and 
 *                       FAULTMASK handlers wil be enabled
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_MPU_Enable(uint8_t priv_defend_enable, uint8_t hf_nmi_enable)
{
    MPU->MPU_CR_b.HFNMIENA = (hf_nmi_enable & 0x01U);
    MPU->MPU_CR_b.PRIVDEFENA = (priv_defend_enable & 0x01U);
    MPU->MPU_CR_b.ENABLE = 1U;
}

/**********************************************************************************************************************
 * @brief Disbale MPU
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_MPU_Disable(void)
{
    MPU->MPU_CR_b.HFNMIENA = 0U;
    MPU->MPU_CR_b.PRIVDEFENA = 0U;
    MPU->MPU_CR_b.ENABLE = 0U;
}

void BSP_MPU_RegionSet(const bsp_mpu_region_t *p_region);
void BSP_MPU_RegionGet(uint8_t no_region, bsp_mpu_region_t *p_region);
void BSP_MPU_RegionEnable(bsp_mpu_region_t *p_region);
void BSP_MPU_RegionDisable(bsp_mpu_region_t *p_region);

#endif

#endif
