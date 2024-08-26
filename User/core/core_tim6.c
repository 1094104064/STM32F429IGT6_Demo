/**
  ******************************************************************************
  *
  * @file    core_tim6.c
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
#include "core_tim6.h"
/**********************
 *      MACROS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void core_tim6_init(void)
{
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;          
    TIM_TimeBaseStructure.TIM_Prescaler = 90 - 1;     
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);    
}

void core_tim6_delay_ms(uint32_t ms)
{
    for(uint32_t i = 0;i < ms; i++) {
        core_tim6_delay_us(1000);
    }
}


void core_tim6_delay_us(uint32_t us)
{
	TIM_Cmd(TIM6, ENABLE); 
    
	while(TIM6->CNT < us);
	TIM6->CNT = 0;
    
	TIM_Cmd(TIM6, DISABLE); 
}


/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
