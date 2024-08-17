/**
  ******************************************************************************
  *
  * @file    core_gpio.h
  * @author  GarMing
  * @brief   Header file of core_gpio module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_GPIO_H
#define _CORE_GPIO_H


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
int8_t core_gpio_blue_led_init(void);
int8_t core_gpio_blue_led_deinit(void);
int8_t core_gpio_blue_led_on(void);
int8_t core_gpio_blue_led_off(void);

int8_t core_gpio_yellow_led_init(void);
int8_t core_gpio_yellow_led_deinit(void);
int8_t core_gpio_yellow_led_on(void);
int8_t core_gpio_yellow_led_off(void);

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_GPIO_H*/


/******************************* (END OF FILE) *********************************/
