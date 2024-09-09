/**
  ******************************************************************************
  *
  * @file    bsp.h
  * @author  GarMing
  * @brief   Header file of bsp module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_H
#define _BSP_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "core_gpio.h"
#include "core_systick.h"
#include "core_usart1.h"
#include "core_tim7.h"
#include "core_swiic.h"
#include "core_hwiic.h"
#include "core_spi1.h"
#include "core_ltdc.h"
#include "core_fmc.h"
#include "core_dma2d.h"
    
#include "bsp_ioled.h"
#include "bsp_console.h"
#include "bsp_beep.h"
#include "bsp_bmp180.h"
#include "bsp_w25qxx.h"
#include "bsp_st7735.h"
#include "bsp_lcd.h"

#include "ringBuffer.h"
#include "taskScher.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
*  GLOBAL PROTOTYPES
**********************/
int8_t bsp_init(void);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BSP_H*/


/******************************* (END OF FILE) *********************************/
