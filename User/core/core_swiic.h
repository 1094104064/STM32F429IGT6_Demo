/**
  ******************************************************************************
  *
  * @file    core_swiic.h
  * @author  GarMing
  * @brief   Header file of core_swiic module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_SWIIC_H
#define _CORE_SWIIC_H


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
int8_t  core_swiic_init(void);
int8_t  core_swiic_deinit(void);
void    core_swiic_delay_test(void);
int8_t  core_swiic_start(void);
int8_t  core_swiic_stop(void);
int8_t  core_swiic_send_byte(uint8_t byte);
uint8_t core_swiic_read_byte(void);
uint8_t core_swiic_wait_ack(void);
int8_t  core_swiic_generate_ack(void);
int8_t  core_swiic_generate_nack(void);

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_SWIIC_H*/


/******************************* (END OF FILE) *********************************/
