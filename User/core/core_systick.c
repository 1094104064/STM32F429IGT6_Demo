/**
  ******************************************************************************
  *
  * @file    core_systick.c
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
#include "core_systick.h"
/**********************
 *      MACROS
 **********************/
#define SYSCLK  SystemCoreClock
/*********************
 *      DEFINES
 *********************/
typedef enum {
    STK_PERIOD_1MS      = 1000,
    STK_PERIOD_1US      = 1000000
}SystickPeriod_TypeDef_E;
/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static uint8_t s_Initialized = 0;
static volatile uint32_t s_ElapsTicks; 
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

/**
  * @brief  System tick timer clock initialized
  * @param  None
  * @retval NULL
  */
void core_systick_init(void)
{
    if(!s_Initialized) {
        SysTick_Config(SYSCLK / STK_PERIOD_1MS);
        s_Initialized = 1;
    }
}

/**
  * @brief  Get timer beat
  * @param  None
  * @retval timer beat
  */
uint32_t core_systick_get_ticks(void)
{
    return s_ElapsTicks;
}

/**
  * @brief  Delay, in milliseconds
  * @param  nms: delay time
  * @retval NULL
  */
void core_systick_delay_ms(uint32_t nms)
{
    uint32_t act_time = core_systick_get_ticks();
    
    while((core_systick_get_ticks() - act_time) < nms);
}

/**
  * @brief  Delay, in microseconds
  * @param  nus: delay time
  * @retval NULL
  */
void core_systick_delay_us(uint32_t nus)
{

}

/**
  * @brief  System timer beat
  * @param  nms: beat period
  * @retval NULL
  */
void core_systick_inc(uint32_t nms)
{
    s_ElapsTicks += nms;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
