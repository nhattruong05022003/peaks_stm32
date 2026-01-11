#include "bsp_mpu.h"

#if (BSP_FEATURE_MPU_IS_AVAILABLE)

void BSP_MPU_RegionSet(const bsp_mpu_region_t *p_region)
{
    /* Check valid size */
    if((p_region->size >= 4U) && (p_region->size <= 32U))
    {
        MPU->MPU_RNR = p_region->no_region;
        MPU->MPU_RBAR |= (p_region->base_address);
        MPU->MPU_RASR_b.SIZE = p_region->size;
        MPU->MPU_RASR |= (p_region->attr.attr_value) << 16U;
        MPU->MPU_RASR_b.ENABLE = p_region->enable;
    }
}

void BSP_MPU_RegionGet(uint8_t no_region, bsp_mpu_region_t *p_region)
{
    p_region->base_address = MPU->MPU_RBAR & (0xFFFFFFE0U);
    p_region->size = MPU->MPU_RASR_b.SIZE;
    p_region->attr.attr_value = (MPU->MPU_RASR >> 16U);
    p_region->enable = MPU->MPU_RASR_b.ENABLE;
    p_region->no_region = no_region;
}

void BSP_MPU_RegionEnable(bsp_mpu_region_t *p_region)
{
    MPU->MPU_RASR_b.ENABLE = 1U;
    p_region->enable = 1U;
}

void BSP_MPU_RegionDisable(bsp_mpu_region_t *p_region)
{
    MPU->MPU_RASR_b.ENABLE = 0U;
    p_region->enable = 0U;
}

#endif
