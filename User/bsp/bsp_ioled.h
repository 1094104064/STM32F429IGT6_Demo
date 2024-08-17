/**
  ******************************************************************************
  *
  * @file    bsp_ioled.h
  * @author  GarMing
  * @brief   Header file of bsp_ioled module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_IOLED_H
#define _BSP_IOLED_H

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdio.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _ioled_delay_interface_t {
    void (* delay_init)(void);
    void (* delay_ms)(uint32_t nms);
    void (* delay_us)(uint32_t nus);
}ioled_delay_interface_t;


typedef struct _bsp_ioled_t {
    int8_t (* init)(void);
    int8_t (* deinit)(void);
    int8_t (* on)(void);
    int8_t (* off)(void);
    int8_t (* flash_light)(struct _bsp_ioled_t * self, uint32_t period);
    int8_t (* grad_light)(struct _bsp_ioled_t * self);
    ioled_delay_interface_t delay_interface;
}bsp_ioled_t;



/**********************
* GLOBAL PROTOTYPES
**********************/
int8_t bsp_ioled_init(bsp_ioled_t * self, 
                      int8_t (* pf_init)(void), 
                      int8_t (* pf_deinit)(void),
                      int8_t (* pf_on)(void),
                      int8_t (* pf_off)(void),
                      void   (* pf_delay_init)(void),
                      void   (* pf_delay_ms)(uint32_t nms),
                      void   (* pf_delay_us)(uint32_t nus));
/**********************
 *      MACROS
 **********************/

#endif /*_BSP_IOLED_H*/


/******************************* (END OF FILE) *********************************/
