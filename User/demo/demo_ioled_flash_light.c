/**
  ******************************************************************************
  *
  * @file    demo_ioled_flash_light.c
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

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void demo_ioled_flash_light(void)
{
    bsp_ioled_t blue_led;
    bsp_ioled_t yellow_led;

    bsp_ioled_init( &blue_led, 
                    core_gpio_blue_led_init, 
                    core_gpio_blue_led_deinit,
                    core_gpio_blue_led_on,
                    core_gpio_blue_led_off,
                    core_systick_init,
                    core_systick_delay_ms,
                    core_systick_delay_ms );
    
    bsp_ioled_init( &yellow_led, 
                    core_gpio_yellow_led_init, 
                    core_gpio_yellow_led_deinit,
                    core_gpio_yellow_led_on,
                    core_gpio_yellow_led_off,
                    core_systick_init,
                    core_systick_delay_ms,
                    core_systick_delay_ms );
    
    blue_led.delay_interface.delay_init();

    for(;;) {
        blue_led.flash_light(&blue_led, 500);
        yellow_led.flash_light(&yellow_led, 500);
    }
}


/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
