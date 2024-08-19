/**
  ******************************************************************************
  *
  * @file    core_systick.h
  * @author  GarMing
  * @brief   Header file of template module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_SYSTICK_H
#define _CORE_SYSTICK_H


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
void        core_systick_init(void);
uint32_t    core_systick_get_ticks(void);
void        core_systick_delay_ms(uint32_t nms);
void        core_systick_delay_us(uint32_t nus);
void        core_systick_inc(uint32_t nms);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_SYSTICK_H*/


/******************************* (END OF FILE) *********************************/
