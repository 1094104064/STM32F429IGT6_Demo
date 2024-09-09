/**
  ******************************************************************************
  *
  * @file    demo_taskScher_print.c
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
static void mytask1(void);
static void mytask2(void);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void demo_taskScher_print(void)
{
    taskScher_init(core_systick_get_ticks);

    taskScher_register_task(mytask1, 500, 1);
    taskScher_register_task(mytask2, 1000, 1);

    for(;;) {
        taskScher_handler();
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
static void mytask1(void)
{
    LOG_INFO("Finished!");
}

static void mytask2(void)
{
    LOG_INFO("Finished!");
}

/******************************* (END OF FILE) *********************************/
