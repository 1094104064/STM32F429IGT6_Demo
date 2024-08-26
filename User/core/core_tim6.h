/**
  ******************************************************************************
  *
  * @file    core_tim6.h
  * @author  GarMing
  * @brief   Header file of core_tim6 module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_TIM6_H
#define _CORE_TIM6_H


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
void core_tim6_init(void);
void core_tim6_delay_ms(uint32_t ms);
void core_tim6_delay_us(uint32_t us);    
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_TIM6_H*/


/******************************* (END OF FILE) *********************************/
