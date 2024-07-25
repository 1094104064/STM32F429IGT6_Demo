/**
  ******************************************************************************
  *
  * @file    ex_console_1.c
  * @author  GarMing
  * @brief   
  *
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  **/
  
  
/*********************
 *      INCLUDES
 *********************/
#include "proj.h"
/**********************
 *      MACROS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 
extern dev_console_t g_ConsoleRecInfo;
/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void ex_console_1(void)
{
    /*!< Data reception completed */
    if(g_ConsoleRecInfo.rec_flg == 1) {	
		
        printf("[ %s ]:  ", __func__);
        /*!< Send the received data */
        for(uint16_t i = 0; i <= g_ConsoleRecInfo.rec_cnt; i++) {
            
            /*!< Send single byte */
            USART_SendData(USART1, g_ConsoleRecInfo.rec_buf[i]);  
            
            /*!< Waiting for sending to complete */
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);			
        }		
        
        /*!< Completion of sending */
        g_ConsoleRecInfo.rec_flg = 0;
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
