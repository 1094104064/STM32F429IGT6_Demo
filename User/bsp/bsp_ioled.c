/**
  ******************************************************************************
  *
  * @file    bsp_led.c
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
#include "bsp_ioled.h"
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
int8_t _bsp_ioled_flash_light(bsp_ioled_t * self, uint32_t period);
int8_t _bsp_ioled_grad_light(bsp_ioled_t * self);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

int8_t bsp_ioled_init(bsp_ioled_t * self, 
                      int8_t (* pf_init)(void), 
                      int8_t (* pf_deinit)(void),
                      int8_t (* pf_on)(void),
                      int8_t (* pf_off)(void),
                      void   (* pf_delay_init)(void),
                      void   (* pf_delay_ms)(uint32_t nms),
                      void   (* pf_delay_us)(uint32_t nus))
{
    self->init = pf_init;
    self->deinit = pf_deinit;
    self->on = pf_on;
    self->off = pf_off;
    self->delay_interface.delay_init = pf_delay_init;
    self->delay_interface.delay_ms = pf_delay_ms;
    self->delay_interface.delay_us = pf_delay_us;

    if( (self->init                         == NULL)  ||
        (self->deinit                       == NULL)  ||
        (self->on                           == NULL)  ||
        (self->off                          == NULL)  ||
        (self->delay_interface.delay_init   == NULL)  ||
        (self->delay_interface.delay_ms     == NULL)  ||
        (self->delay_interface.delay_us     == NULL) )
    {
        return -1;
    }

    if(0 != self->init()) {
        return -2;
    }

    self->flash_light = _bsp_ioled_flash_light;
    self->grad_light = _bsp_ioled_grad_light;



    return 0;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
  * @brief  Content
  * @param  self: object
  * @param  period: 
  * @retval 0
  */
int8_t _bsp_ioled_flash_light(bsp_ioled_t * self, uint32_t period)
{
    self->on();
    self->delay_interface.delay_ms(period);
    self->off();
    self->delay_interface.delay_ms(period);
    
    return 0;
}

/**
  * @brief  Content
  * @param  self: object
  * @retval 0
  */
int8_t _bsp_ioled_grad_light(bsp_ioled_t * self)
{
    static uint8_t pwmset;
    static uint16_t time;
    static uint8_t timeflag;
    static uint8_t timecount;

        /* 呼吸灯 */
    if(timeflag == 0) {
        time ++;
        if(time >= 1600) timeflag = 1;
    }
    else {
        time --;
        if(time == 0) timeflag = 0;
    }

    /* 占空比设置 */
    pwmset = time/80;

    /* 20ms 脉宽 */
    if(timecount > 20) {
        timecount = 0;
    }
    else {
        timecount ++;
    }

    if(timecount >= pwmset ) {
        self->on();
    }
    else {
        self->off();
    }

    return 0;
}



/******************************* (END OF FILE) *********************************/
