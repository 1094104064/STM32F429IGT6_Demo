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
int8_t core_hwiic_init(void);
int8_t core_hwiic_deinit(void);
int8_t core_hwiic_start(void);    
int8_t core_hwiic_stop(void);
int8_t core_hwiic_send_byte(uint8_t byte);
uint8_t core_hwiic_read_byte(uint8_t byte);
uint8_t core_hwiic_wait_ack(void);
int8_t core_hwiic_generate_ack(void);
int8_t core_hwiic_generate_nack(void);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_HWIIC_H*/


/******************************* (END OF FILE) *********************************/
