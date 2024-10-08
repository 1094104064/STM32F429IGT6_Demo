/**
  ******************************************************************************
  *
  * @file    core_dma2d.h
  * @author  GarMing
  * @brief   Header file of core_dma2d module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_DMA2D_H
#define _CORE_DMA2D_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "stm32f4xx.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
*  GLOBAL PROTOTYPES
 **********************/
int8_t core_dma2d_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_DMA2D_H*/


/******************************* (END OF FILE) *********************************/
