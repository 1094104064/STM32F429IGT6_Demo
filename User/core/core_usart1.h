/**
  ******************************************************************************
  *
  * @file    core_usart1.h
  * @author  GarMing
  * @brief   Header file of template module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_USART1_H
#define _CORE_USART1_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
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
int8_t  core_usart1_init(void);
int8_t  core_usart1_deinit(void);
void    core_usart1_receive_proc(void);
void    core_usart1_receive_cb(void);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_USART1_H*/


/******************************* (END OF FILE) *********************************/
