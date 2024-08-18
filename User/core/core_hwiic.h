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
int8_t  core_hwiic_start(void);    
int8_t  core_hwiic_stop(void);
int8_t  core_hwiic_send_byte(uint8_t byte);
uint8_t core_hwiic_read_byte(void);
uint8_t core_hwiic_wait_ack(void);
int8_t  core_hwiic_generate_ack(void);
int8_t  core_hwiic_generate_nack(void);
int8_t  core_hwiic_is_busy(void);
int8_t  core_hwiic_buf_write(uint8_t dev_addr, uint8_t reg_addr,uint8_t * pbuf, uint16_t byte_num);
int8_t  core_hwiic_buf_read(uint8_t * pbuf, uint8_t dev_addr, uint8_t reg_addr, uint16_t byte_num);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_HWIIC_H*/


/******************************* (END OF FILE) *********************************/
