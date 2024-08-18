/**
  ******************************************************************************
  *
  * @file    core_spi1.h
  * @author  GarMing
  * @brief   Header file of core_spi1 module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_SPI1_H
#define _CORE_SPI1_H


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
int8_t  core_spi1_init(void);
int8_t  core_spi1_deinit(void);
void    core_spi1_chip_selection_pin_high(void);
void    core_spi1_chip_selection_pin_low(void);
uint8_t core_spi1_send_receive_byte(uint8_t byte);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_SPI1_H*/


/******************************* (END OF FILE) *********************************/
