/**
  ******************************************************************************
  *
  * @file    template.c
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

int8_t bsp_lcd_draw_ascii_character(bsp_lcd_t * self, uint16_t x, uint16_t y, uint8_t character)
{
    // uint8_t c = character - 32;

    return 0;
}

int8_t bsp_lcd_draw_string(bsp_lcd_t * self, uint16_t x, uint16_t y, char * str)
{
    // char * ptr = str;
    // while((x < self->disp_info.ver_res) && (*ptr++)) {
    //     bsp_lcd_draw_ascii_character(x, y, *ptr);
    // }

    return 0;
}


int8_t bsp_lcd_draw_line(bsp_lcd_t * self, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
	curpixel = 0;

	deltax = abs(ex - sx);        /* The difference between the x's */
	deltay = abs(ey - sy);        /* The difference between the y's */
	x = sx;                       /* Start x off at the first pixel */
	y = sy;                       /* Start y off at the first pixel */

	if (ex >= sx)                 /* The x-values are increasing */
	{
	 xinc1 = 1;
	 xinc2 = 1;
	}
	else                          /* The x-values are decreasing */
	{
	 xinc1 = -1;
	 xinc2 = -1;
	}

	if (ey >= sy)                 /* The y-values are increasing */
	{
	 yinc1 = 1;
	 yinc2 = 1;
	}
	else                          /* The y-values are decreasing */
	{
	 yinc1 = -1;
	 yinc2 = -1;
	}

	if (deltax >= deltay)         /* There is at least one x-value for every y-value */
	{
	 xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
	 yinc2 = 0;                  /* Don't change the y for every iteration */
	 den = deltax;
	 num = deltax / 2;
	 numadd = deltay;
	 numpixels = deltax;         /* There are more x-values than y-values */
	}
	else                          /* There is at least one y-value for every x-value */
	{
	 xinc2 = 0;                  /* Don't change the x for every iteration */
	 yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
	 den = deltay;
	 num = deltay / 2;
	 numadd = deltax;
	 numpixels = deltay;         /* There are more y-values than x-values */
	}
	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
	 self->draw_pixel(x, y, self->disp_info.draw_color);             /* Draw the current pixel */
	 num += numadd;              /* Increase the numerator by the top of the fraction */
	 if (num >= den)             /* Check if numerator >= denominator */
	 {
		num -= den;               /* Calculate the new numerator value */
		x += xinc1;               /* Change the x as appropriate */
		y += yinc1;               /* Change the y as appropriate */
	 }
	 x += xinc2;                 /* Change the x as appropriate */
	 y += yinc2;                 /* Change the y as appropriate */
	}


    return 0;
}

int8_t bsp_lcd_draw_rect(bsp_lcd_t * self, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	/* draw horizontal lines */
	self->draw_line(self, x, y, x + width, y);
	self->draw_line(self, x, y + height, x + width, y + height);

	/* draw vertical lines */
	self->draw_line(self, x, y, x, y + height);
	self->draw_line(self, x + width, y, x + width, y + height);

    return 0;
}

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


int8_t bsp_lcd_draw_ellipse(bsp_lcd_t * self, int32_t x, int32_t y, int32_t r1, int32_t r2)
{
  int Xadd = -r1, Yadd = 0, err = 2-2*r1, e2;
  float K = 0, rad1 = 0, rad2 = 0;
   
  rad1 = r1;
  rad2 = r2;
  
  if (r1 > r2)
  { 
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
    }
    while (Xadd <= 0);
  }
  else
  {
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
    }
    while (Yadd <= 0);
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
                     
                     int8_t (* pf_draw_pixel)(uint16_t x, uint16_t y, uint16_t color),
                     int8_t (* pf_fill_rect)(uint16_t x, uint16_t y, uint16_t width, uint16_t height) )
{

	memset(self, 0, sizeof(bsp_lcd_t));

    self->fmc_interface.sdram_init = pf_sdram_init;
    self->fmc_interface.sdram_deinit = pf_sdram_deinit;

    self->fmc_interface.sdram_init();

    self->ltdc_interface.init = pf_ltdc_init;
    self->ltdc_interface.deinit = pf_ltdc_deinit;

    self->ltdc_interface.init();

    self->backlight_interface.init = pf_backlight_init;
    self->backlight_interface.deinit = pf_backlight_deinit;
    self->backlight_interface.on = pf_backlight_on;
    self->backlight_interface.off = pf_backlight_off;
    self->backlight_interface.set_bright = pf_backlight_set_bright;

    self->backlight_interface.init();

    self->draw_pixel = pf_draw_pixel;
    self->fill_rect = pf_fill_rect;


    return 0;
}




/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
