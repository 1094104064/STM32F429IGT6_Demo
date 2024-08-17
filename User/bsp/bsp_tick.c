/**
  ******************************************************************************
  *
  * @file    bsp_tick.c
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
#include "bsp_tick.h"
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
int8_t bsp_tick_init( bsp_tick_t * self, 
                      void     (* pf_init)(void),
                      uint32_t (* pf_get)(void),
                      void     (* pf_delayms)(uint32_t nms),
                      void     (* pf_delayus)(uint32_t nus))
{
    self->init      = pf_init;
    self->get       = pf_get;
    self->delayms   = pf_delayms;
    self->delayus   = pf_delayus;

    self->init();

    return 0;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
