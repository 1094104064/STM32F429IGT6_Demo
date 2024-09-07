/**
  ******************************************************************************
  *
  * @file    core_tim7.c
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
#include "core_tim7.h"
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
static volatile uint32_t s_DelayTime; 
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void core_tim7_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
    NVIC_InitTypeDef        NVIC_InitStruct       = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 10 - 1;          
    TIM_TimeBaseStructure.TIM_Prescaler = 9 - 1;     
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);   

    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
    
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);   
    
    NVIC_InitStruct.NVIC_IRQChannel                     =   TIM7_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd                  =   ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority   =   2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority          =   2;

    NVIC_Init(&NVIC_InitStruct); 
    
    TIM_Cmd(TIM7, ENABLE); 

}

void core_tim7_irq_handler(void)
{
    if(s_DelayTime != 0) {
        s_DelayTime -= 1;
    }
} 

uint32_t core_tim7_get_ticks(void)
{
    return s_DelayTime;
}

void core_tim7_delay_us(uint32_t us)
{
    s_DelayTime = us;
    
    while(s_DelayTime != 0);
}

void core_tim7_delay_ms(uint32_t ms)
{
    for(uint32_t i = 0;i < ms; i++) {
        core_tim7_delay_us(1000);
    }
}




  


/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
