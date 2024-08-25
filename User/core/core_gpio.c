/**
  ******************************************************************************
  *
  * @file    core_gpio.c
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
#include "core_gpio.h"
/**********************
 *      MACROS
 **********************/
#define BLUE_LED_CLK    RCC_AHB1Periph_GPIOD
#define BLUE_LED_PORT   GPIOD
#define BLUE_LED_PIN    GPIO_Pin_4

#define YELLOW_LED_CLK  RCC_AHB1Periph_GPIOI
#define YELLOW_LED_PORT GPIOI
#define YELLOW_LED_PIN  GPIO_Pin_3


#define LCD_BL_CLK      RCC_AHB1Periph_GPIOD    
#define LCD_BL_PORT     GPIOD
#define LCD_BL_PIN      GPIO_Pin_13



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


int8_t core_gpio_key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; 
    EXTI_InitTypeDef EXTI_InitStruct = {0};
    NVIC_InitTypeDef NVIC_InitStruct = {0};

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE); 		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;	 

    GPIO_Init(GPIOI, &GPIO_InitStructure);	

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOI, GPIO_PinSource8);

    EXTI_InitStruct.EXTI_Line               =   EXTI_Line8;
    EXTI_InitStruct.EXTI_LineCmd            =   ENABLE;
    EXTI_InitStruct.EXTI_Mode               =   EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger            =   EXTI_Trigger_Falling;

    EXTI_Init(&EXTI_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel                     =   EXTI9_5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd                  =   ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority   =   2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority          =   2;

    NVIC_Init(&NVIC_InitStruct);

    return 0;
}



int8_t core_gpio_blue_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; 
    
    /*!< Enable the LED1 GPIO clock */
    RCC_AHB1PeriphClockCmd(BLUE_LED_CLK, ENABLE); 	

    /*!< GPIO_InitStructure members configuration*/
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 

    /*!< LED1 pin configuration */
    GPIO_InitStructure.GPIO_Pin = BLUE_LED_PIN;	 
    GPIO_Init(BLUE_LED_PORT, &GPIO_InitStructure);	

    /*!< Sets LED1 port bits, off */
    GPIO_SetBits(BLUE_LED_PORT, BLUE_LED_PIN);  

    return 0;
}

int8_t core_gpio_blue_led_deinit(void)
{
    /*!< Disable the LED1 GPIO clock */
    RCC_AHB1PeriphClockCmd(BLUE_LED_CLK, DISABLE); 

    return 0;
}   

int8_t core_gpio_blue_led_on(void)
{
    GPIO_ResetBits(BLUE_LED_PORT, BLUE_LED_PIN);

    return 0;
}

int8_t core_gpio_blue_led_off(void)
{
    GPIO_SetBits(BLUE_LED_PORT, BLUE_LED_PIN);

    return 0;
}

int8_t core_gpio_yellow_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; 

    /*!< Enable the LED2 GPIO clock */
    RCC_AHB1PeriphClockCmd(YELLOW_LED_CLK, ENABLE); 	
    
    /*!< GPIO_InitStructure members configuration*/
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
                     
    /*!< LED2 pin configuration */
    GPIO_InitStructure.GPIO_Pin = YELLOW_LED_PIN;	
    GPIO_Init(YELLOW_LED_PORT, &GPIO_InitStructure);	

    /*!< Sets LED2 port bits, off */
    GPIO_SetBits(YELLOW_LED_PORT, YELLOW_LED_PIN); 

    return 0;
}

int8_t core_gpio_yellow_led_deinit(void)
{
    /*!< Disable the LED2 GPIO clock */
    RCC_AHB1PeriphClockCmd(YELLOW_LED_CLK, DISABLE); 	

    return 0;
}

int8_t core_gpio_yellow_led_on(void)
{
    GPIO_ResetBits(YELLOW_LED_PORT, YELLOW_LED_PIN);

    return 0;
}

int8_t core_gpio_yellow_led_off(void)
{
    GPIO_SetBits(YELLOW_LED_PORT, YELLOW_LED_PIN);

    return 0;
}


int8_t core_gpio_lcd_backlight_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; 

    /*!< Enable the LED2 GPIO clock */
    RCC_AHB1PeriphClockCmd(LCD_BL_CLK, ENABLE); 	
    
    /*!< GPIO_InitStructure members configuration*/
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
                     
    /*!< LED2 pin configuration */
    GPIO_InitStructure.GPIO_Pin = LCD_BL_PIN;	
    GPIO_Init(LCD_BL_PORT, &GPIO_InitStructure);	

    GPIO_ResetBits(LCD_BL_PORT, LCD_BL_PIN); 
    
    return 0;
}

int8_t core_gpio_lcd_backlight_deinit(void)
{
    RCC_AHB1PeriphClockCmd(LCD_BL_CLK, DISABLE); 

    return 0;
}

int8_t core_gpio_lcd_backlight_on(void)
{
    GPIO_SetBits(LCD_BL_PORT, LCD_BL_PIN); 

    return 0;
}

int8_t core_gpio_lcd_backlight_off(void)
{
    GPIO_ResetBits(LCD_BL_PORT, LCD_BL_PIN); 

    return 0;
}




/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/

