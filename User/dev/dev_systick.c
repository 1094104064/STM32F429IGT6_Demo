/**
  ******************************************************************************
  *
  * @file    dev_systick.c
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
#include "dev_systick.h"
/**********************
 *      MACROS
 **********************/

/*********************
 *      DEFINES
 *********************/
#define SYSCLK  SystemCoreClock
/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void _dev_systick_inc(uint32_t millis);
/**********************
 *  STATIC VARIABLES
 **********************/
static volatile uint32_t s_ElapsTicks; 
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void dev_systick_init(uint32_t period)
{
    SysTick_Config(SYSCLK / period);
}

uint32_t dev_systick_get_ticks(void)
{
    return s_ElapsTicks;
}

void dev_systick_delay_ms(uint32_t ms)
{
    uint32_t act_time = dev_systick_get_ticks();
    
    while((dev_systick_get_ticks() - act_time) < ms);
}

uint32_t dev_systick_count_sec(void)
{
    if(!(s_ElapsTicks % 1000)) {
        return s_ElapsTicks;
    }
    return 0;
}


void SysTick_Handler(void)
{
    _dev_systick_inc(1);
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _dev_systick_inc(uint32_t millis)
{
    s_ElapsTicks += millis;
}




/******************************* (END OF FILE) *********************************/
