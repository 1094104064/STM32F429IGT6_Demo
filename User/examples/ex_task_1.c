/**
  ******************************************************************************
  *
  * @file    ex_task_1.c
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
void ex_task_1(void)
{
    bsp_task_register(_task_1, 500, BSP_TASK_STATE_EN);
    bsp_task_register(_task_2, 1000, BSP_TASK_STATE_DISEN);
    bsp_task_register(_task_3, 2000, BSP_TASK_STATE_EN);
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
