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
void core_systick_init(void)
{
    if(!s_Initialized) {
        SysTick_Config(SYSCLK / STK_PERIOD_1MS);
        s_Initialized = 1;
    }
}

uint32_t core_systick_get_ticks(void)
{
    return s_ElapsTicks;
}

void core_systick_delay_ms(uint32_t nms)
{
    uint32_t act_time = core_systick_get_ticks();
    
    while((core_systick_get_ticks() - act_time) < nms);
}

void core_systick_inc(uint32_t nms)
{
    s_ElapsTicks += nms;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
