/**
  ******************************************************************************
  *
  * @file    bsp_console.c
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
#include "bsp_console.h"
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
int8_t bsp_console_init( bsp_console_t * self,
                         int8_t (* pf_init)(void),
                         int8_t (* pf_deinit)(void),
                         void   (* pf_rec_cb)(void))
{
    self->init = pf_init;
    self->deinit = pf_deinit;
    self->rec_cb = pf_rec_cb;

    if( (self->init     == NULL) ||
        (self->deinit   == NULL) ||
        (self->rec_cb   == NULL) ) 
    {
        return -1;
    }

    if(0 != self->init()) {
        return -2;
    }

    return 0;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/
