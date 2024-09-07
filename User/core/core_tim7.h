/**
  ******************************************************************************
  *
  * @file    core_tim7.h
  * @author  GarMing
  * @brief   Header file of core_tim7 module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_TIM7_H
#define _CORE_TIM7_H


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
void core_tim7_init(void);
void core_tim7_irq_handler(void);
uint32_t core_tim7_get_ticks(void);
void core_tim7_delay_us(uint32_t us); 
void core_tim7_delay_ms(uint32_t ms);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_TIM7_H*/


/******************************* (END OF FILE) *********************************/
