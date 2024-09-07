/**
  ******************************************************************************
  *
  * @file    core_hwiic.h
  * @author  GarMing
  * @brief   Header file of core_hwiic module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_HWIIC_H
#define _CORE_HWIIC_H


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
int8_t  core_hwiic_init(void);
int8_t  core_hwiic_deinit(void);
int8_t  core_hwiic_buf_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len);
int8_t  core_hwiic_buf_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_HWIIC_H*/


/******************************* (END OF FILE) *********************************/
