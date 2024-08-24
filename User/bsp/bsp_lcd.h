/**
  ******************************************************************************
  *
  * @file    template.h
  * @author  GarMing
  * @brief   Header file of template module.
  *
  ******************************************************************************
  **/
  
#ifndef _TEMPLATE_H
#define _TEMPLATE_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _lcd_disp_info_t {
    uint16_t hor_res;
    uint16_t ver_res;
    uint32_t draw_color;
}lcd_disp_info_t;


typedef struct _lcd_ltdc_interface_t {
    int8_t (* init)(void);
    int8_t (* deinit)(void);
}lcd_ltdc_interface_t;

typedef struct _lcd_fmc_interface_t {
    int8_t (* sdram_init)(void);
    int8_t (* sdram_deinit)(void);
}lcd_fmc_interface_t;



typedef struct _lcd_backlight_interface_t {
    int8_t (* init)(void);
    int8_t (* deinit)(void);
    int8_t (* on)(void);
    int8_t (* off)(void);
    int8_t (* set_bright)(uint32_t val);
}lcd_backlight_interface_t;



typedef struct _bsp_lcd_t {
    lcd_disp_info_t                  disp_info;
    lcd_ltdc_interface_t             ltdc_interface;
    lcd_fmc_interface_t              fmc_interface;
    lcd_backlight_interface_t        backlight_interface;


    int8_t      (* draw_pixel)       (uint16_t x, uint16_t y, uint16_t color);
    int8_t      (* fill_rect)        (uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    int8_t      (* draw_line)        (struct _bsp_lcd_t * self, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);
    int8_t      (* draw_rect)        (struct _bsp_lcd_t * self, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    int8_t      (* draw_circle)      (struct _bsp_lcd_t * self, uint16_t x, uint16_t y, uint16_t r);
    int8_t      (* draw_ellipse)     (struct _bsp_lcd_t * self, int32_t x, int32_t y, int32_t r1, int32_t r2);

    uint32_t    (* get_pixel_color)  (uint16_t x, uint16_t y);

}bsp_lcd_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_TEMPLATE_H*/


/******************************* (END OF FILE) *********************************/
