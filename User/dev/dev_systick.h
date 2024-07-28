/**
  ******************************************************************************
  *
  * @file    dev_systick.h
  * @author  GarMing
  * @brief   Header file of dev_systick module.
  *
  ******************************************************************************
  **/
  
#ifndef _DEV_SYSTICK_H
#define _DEV_SYSTICK_H

/*********************
 *      INCLUDES
 *********************/
 #include <stdint.h>
#include "stm32f4xx.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    DEV_SYSTICK_PERIOD_SLOW     = 1000,
    DEV_SYSTICK_PERIOD_FAST     = 1000000
};

/**********************
* GLOBAL PROTOTYPES
**********************/
void     dev_systick_init(uint32_t period);
uint32_t dev_systick_get_ticks(void);
void     dev_systick_delay_ms(uint32_t ms);
uint32_t dev_systick_count_sec(void);
void     dev_systick_inc(uint32_t millis);
/**********************
 *      MACROS
 **********************/

#endif /*_DEV_SYSTICK_H*/


/******************************* (END OF FILE) *********************************/
