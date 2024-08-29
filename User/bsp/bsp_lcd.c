/**
  ******************************************************************************
  *
  * @file    bsp_lcd.c
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
#include "bsp_lcd.h"
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

/**
  * @brief  Draw a line between two points
  * @param  self: object
  * @param  sx: The x-coordinate of the first point
  * @param  sy: The y-coordinate of the first point
  * @param  ex: The x-coordinate of the second point
  * @param  ey: The y-coordinate of the second point
  * @retval 0
  */
int8_t bsp_lcd_draw_line(bsp_lcd_t * self, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
    yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
    curpixel = 0;

    /*!< The difference between the x's */
    deltax = abs(ex - sx);

    /*!< The difference between the y's */
    deltay = abs(ey - sy); 

    /*!< Start x off at the first pixel */
    x = sx; 

    /*!< Start y off at the first pixel */
    y = sy; 

    
    if (ex >= sx) {                /**< The x-values are increasing*/
        xinc1 = 1;
        xinc2 = 1;
    }
    else {                         /**< The x-values are decreasing*/
        xinc1 = -1;
        xinc2 = -1;
    }

    if (ey >= sy) {                /**< The y-values are increasing*/
        yinc1 = 1;
        yinc2 = 1;
    }
    else {                         /**< The y-values are decreasing*/
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay) {        /**< There is at least one x-value for every y-value*/

        /*!< Don't change the x when numerator >= denominator */
        xinc1 = 0;

        /*!< Don't change the y for every iteration */
        yinc2 = 0;  

        den = deltax;
        num = deltax / 2;
        numadd = deltay;

        /*!< There are more x-values than y-values */
        numpixels = deltax;
    }
    else {                         /**< There is at least one y-value for every x-value */

        /*!< Don't change the x for every iteration */
        xinc2 = 0;  

        /*!< Don't change the y when numerator >= denominator */
        yinc1 = 0;       

        den = deltay;
        num = deltay / 2;
        numadd = deltax;

        /*!< There are more y-values than x-values */
        numpixels = deltay;   
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++) {

        /*!< Draw the current pixel */    
        self->draw_pixel(x, y, self->disp_info.draw_color); 

        /*!< Increase the numerator by the top of the fraction */
        num += numadd; 

        if (num >= den) {             /**< Check if numerator >= denominator*/  
        
            /*!< Calculate the new numerator value */
            num -= den; 

            /*!< Change the x as appropriate */
            x += xinc1;   

            /*!< Change the y as appropriate */
            y += yinc1;  
        }

        /*!< Change the x as appropriate */
        x += xinc2;    

        /*!< Change the y as appropriate */
        y += yinc2;          
    }


    return 0;
}

/**
  * @brief  Draw a rectangle
  * @param  self: object
  * @param  x: Origin x coordinate
  * @param  y: Origin y coordinate
  * @param  width: Rectangular width
  * @param  height: Rectangular height
  * @retval 0
  */
int8_t bsp_lcd_draw_rect(bsp_lcd_t * self, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    /*!< draw horizontal lines */
    self->draw_line(self, x, y, x + width, y);
    self->draw_line(self, x, y + height, x + width, y + height);

    /*!< draw vertical lines */
    self->draw_line(self, x, y, x, y + height);
    self->draw_line(self, x + width, y, x + width, y + height);

    return 0;
}

/**
  * @brief  Draw a circle
  * @param  self: object
  * @param  x: The x-coordinate of the center of the circle
  * @param  y: The y-coordinate of the center of the circle
  * @param  r: Radius of circle
  * @retval 0
  */
int8_t bsp_lcd_draw_circle(bsp_lcd_t * self, uint16_t x, uint16_t y, uint16_t r)
{
	int Xadd = -r, Yadd = 0, err = 2-2*r, e2;
	do {   

		self->draw_pixel(x - Xadd, y + Yadd, self->disp_info.draw_color);
		self->draw_pixel(x + Xadd, y + Yadd, self->disp_info.draw_color);
		self->draw_pixel(x + Xadd, y - Yadd, self->disp_info.draw_color);
		self->draw_pixel(x - Xadd, y - Yadd, self->disp_info.draw_color);
		
		e2 = err;
		if (e2 <= Yadd) {
			err += ++Yadd*2+1;
			if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
		}
		if (e2 > Xadd) err += ++Xadd*2+1;
    }
    while (Xadd <= 0);

    return 0;
}

/**
  * @brief  Draw a ellipse
  * @param  self: object
  * @param  x: The x-coordinate of a point on an ellipse
  * @param  y: The y-coordinate of a point on an ellipse
  * @param  r1: Left focal radius
  * @param  r2: Right focal radius
  * @retval 0
  */
int8_t bsp_lcd_draw_ellipse(bsp_lcd_t * self, int32_t x, int32_t y, int32_t r1, int32_t r2)
{
    int Xadd = -r1, Yadd = 0, err = 2-2*r1, e2;
    float K = 0, rad1 = 0, rad2 = 0;

    rad1 = r1;
    rad2 = r2;

    if (r1 > r2) { 
        do {
            K = (float)(rad1/rad2);
                
            self->draw_pixel(x - Xadd, y + (uint16_t)(Yadd / K), self->disp_info.draw_color);
            self->draw_pixel(x + Xadd, y + (uint16_t)(Yadd / K), self->disp_info.draw_color);
            self->draw_pixel(x + Xadd, y - (uint16_t)(Yadd / K), self->disp_info.draw_color);
            self->draw_pixel(x - Xadd, y - (uint16_t)(Yadd / K), self->disp_info.draw_color);     
                
            e2 = err;
            if (e2 <= Yadd) {
                err += ++Yadd*2+1;
                if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
            }
            if (e2 > Xadd) err += ++Xadd*2+1;
        } while (Xadd <= 0);
    }
    else {
        Yadd = -r2; 
        Xadd = 0;
        do { 
            K = (float)(rad2/rad1);

            self->draw_pixel(x - (uint16_t)(Xadd / K), y + Yadd, self->disp_info.draw_color);
            self->draw_pixel(x + (uint16_t)(Xadd / K), y + Yadd, self->disp_info.draw_color);
            self->draw_pixel(x + (uint16_t)(Xadd / K), y - Yadd, self->disp_info.draw_color);
            self->draw_pixel(x - (uint16_t)(Xadd / K), y - Yadd, self->disp_info.draw_color);  
                
            e2 = err;
            if (e2 <= Xadd) {
                err += ++Xadd*3+1;
                if (-Yadd == Xadd && e2 <= Yadd) e2 = 0;
            }
            if (e2 > Yadd) err += ++Yadd*3+1;     
        } while (Yadd <= 0);
    }
  
  return 0;
}



int8_t bsp_lcd_init( bsp_lcd_t * self, 

                     int8_t (* pf_sdram_init)(void),
                     int8_t (* pf_sdram_deinit)(void),
                     
                     int8_t (* pf_ltdc_init)(void),
                     int8_t (* pf_ltdc_deinit)(void),
                     
                     int8_t (* pf_backlight_init)(void),
                     int8_t (* pf_backlight_deinit)(void),
                     int8_t (* pf_backlight_on)(void),
                     int8_t (* pf_backlight_off)(void),
                     int8_t (* pf_backlight_set_bright)(uint32_t val),
                     
                     void (* pf_delay_init)(void),
                     void (* pf_delay_ms)(uint32_t ms),
                     void (* pf_delay_us)(uint32_t us),
                     
                     int8_t (* pf_draw_pixel)(uint16_t x, uint16_t y, uint32_t color),
                     int8_t (* pf_fill_rect)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) )
{

	memset(self, 0, sizeof(bsp_lcd_t));

    self->sdram_interface.init = pf_sdram_init;
    self->sdram_interface.deinit = pf_sdram_deinit;

    self->sdram_interface.init();

    self->ltdc_interface.init = pf_ltdc_init;
    self->ltdc_interface.deinit = pf_ltdc_deinit;

    self->ltdc_interface.init();

    self->backlight_interface.init = pf_backlight_init;
    self->backlight_interface.deinit = pf_backlight_deinit;
    self->backlight_interface.on = pf_backlight_on;
    self->backlight_interface.off = pf_backlight_off;
    self->backlight_interface.set_bright = pf_backlight_set_bright;

    self->backlight_interface.init();
    
    self->delay_interface.delay_init = pf_delay_init;
    self->delay_interface.delay_ms = pf_delay_ms;
    self->delay_interface.delay_us = pf_delay_us;


    self->draw_pixel = pf_draw_pixel;
    self->fill_rect = pf_fill_rect;


    return 0;
}




/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
