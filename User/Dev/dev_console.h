/**
  ******************************************************************************
  *
  * @file    dev_console.h
  * @author  GarMing
  * @brief   Header file of dev_console module.
  *
  ******************************************************************************
  **/
  
#ifndef _DEV_CONSOLE_H
#define _DEV_CONSOLE_H

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
/*********************
 *      DEFINES
 *********************/
#define	 DEV_CONSOLE_REC_SIZE	1024	 
 
#define  DEV_CONSOLE_TX_PIN          GPIO_Pin_9					
#define  DEV_CONSOLE_TX_PORT         GPIOA							
#define  DEV_CONSOLE_TX_CLK          RCC_AHB1Periph_GPIOA		
#define  DEV_CONSOLE_TX_PinSource    GPIO_PinSource9			

#define  DEV_CONSOLE_RX_PIN          GPIO_Pin_10             
#define  DEV_CONSOLE_RX_PORT         GPIOA                   
#define  DEV_CONSOLE_RX_CLK          RCC_AHB1Periph_GPIOA    
#define  DEV_CONSOLE_RX_PinSource    GPIO_PinSource10 
/**********************
 *      TYPEDEFS
 **********************/
 
/**
* @brief  Usart receive info structure definition
*/
typedef struct _dev_console_t{
    
    uint8_t  rec_buf[DEV_CONSOLE_REC_SIZE];
    uint8_t  rec_flg;
    uint16_t rec_cnt;

}dev_console_t;

enum {
    DEV_CONSOLE_BAUD_LOW        = 9600,
    DEV_CONSOLE_BAUD_MID        = 115200,
    DEV_CONSOLE_BAUD_HIGH       = 230400,
};

/**********************
* GLOBAL PROTOTYPES
**********************/
void dev_console_init(uint32_t baud);
/**********************
 *      MACROS
 **********************/


#endif /*_DEV_CONSOLE_H*/


/******************************* (END OF FILE) *********************************/
