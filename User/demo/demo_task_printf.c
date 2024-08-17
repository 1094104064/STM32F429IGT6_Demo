/**
  ******************************************************************************
  *
  * @file    demo_task_printf.c
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
static void _task_1(void);
static void _task_2(void);
static void _task_3(void);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void demo_task_printf(void)
{
    bsp_task_class_t millis_task;

    bsp_task_tick_init( &millis_task, 
                        core_systick_init,
                        NULL,
                        core_systick_get_ticks);

    bsp_task_register(_task_1, 500, BSP_TASK_STATE_EN);
    bsp_task_register(_task_2, 1000, BSP_TASK_STATE_DISEN);
    bsp_task_register(_task_3, 2000, BSP_TASK_STATE_EN);

    millis_task.hearbeat_interface.init();

    for(;;) {
        bsp_task_handler(&millis_task);
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _task_1(void)
{
    LOG_INFO("Task 1 Finished!");
}

static void _task_2(void)
{
    LOG_INFO("Task 2 Finished!");
}

static void _task_3(void)
{
    LOG_INFO("Task 3 Finished!");
}

/******************************* (END OF FILE) *********************************/
