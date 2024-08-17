/**
  ******************************************************************************
  *
  * @file    demo_tick_delay_printf.c
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
void demo_tick_delay_printf(void)
{
    bsp_tick_t hal_tick;
    
    bsp_tick_init( &hal_tick,
                   core_systick_init,
                   core_systick_get_ticks,
                   core_systick_delay_ms,
                   NULL );

    for(;;) {
        LOG_INFO("This is 1");
        hal_tick.delayms(500);
        LOG_INFO("This is 2");
        hal_tick.delayms(500);
    }

}
/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
