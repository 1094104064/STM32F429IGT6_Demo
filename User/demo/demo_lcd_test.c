/**
  ******************************************************************************
  *
  * @file    demo_lcd_test.c
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
void demo_lcd_test(void)
{
    bsp_lcd_t lcd_driver;

    bsp_lcd_init( &lcd_driver, 
    
                  core_fmc_sdram_init,
                  core_fmc_sdram_deinit,

                  core_ltdc_init,
                  NULL,
                  
                  core_gpio_lcd_backlight_init,
                  core_gpio_lcd_backlight_deinit,
                  core_gpio_lcd_backlight_on,
                  core_gpio_lcd_backlight_off, 
                  NULL,
                  
                  core_systick_init,
                  core_systick_delay_ms,
                  core_systick_delay_us,
    
                  NULL,
                  core_dma2d_fill_rect);
                
    lcd_driver.delay_interface.delay_init();           
    lcd_driver.fill_rect(0, 0, LCD_WIDTH, LCD_HEIGHT, core_ltdc_color_hex(LCD_RGB565, 0xFFFFFF));
    lcd_driver.backlight_interface.on();
    
    lcd_driver.delay_interface.delay_ms(1000);
    
    for(;;) {
        
        lcd_driver.fill_rect(0, 0, LCD_WIDTH, LCD_HEIGHT, core_ltdc_color_hex(LCD_RGB565, 0xFF0000));
        lcd_driver.delay_interface.delay_ms(1000);
        
        lcd_driver.fill_rect(0, 0, LCD_WIDTH, LCD_HEIGHT, core_ltdc_color_hex(LCD_RGB565, 0x00FF00));
        lcd_driver.delay_interface.delay_ms(1000);
        
        lcd_driver.fill_rect(0, 0, LCD_WIDTH, LCD_HEIGHT, core_ltdc_color_hex(LCD_RGB565, 0x0000FF));
        lcd_driver.delay_interface.delay_ms(1000);
    }
        
}
/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
