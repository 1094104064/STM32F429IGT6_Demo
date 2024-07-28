/**
  ******************************************************************************
  *
  * @file    bsp_task.h
  * @author  GarMing
  * @brief   Header file of bsp_task module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_TASK_H
#define _BSP_TASK_H

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdlib.h>
/*********************
 *      DEFINES
 *********************/
#define BSP_TASK_NONE  NULL

#define BSP_TASK_TRUE   1
#define BSP_TASK_FALSE  0
/**********************
 *      TYPEDEFS
 **********************/

typedef void (* bsp_task_cb_f)(void);

typedef struct _bsp_task_t {
    uint8_t               state;
    uint32_t              time_period;
    uint32_t              time_prev;
    uint32_t              time_cost;
    uint32_t              time_error;
    bsp_task_cb_f         pCallback;
    struct  _bsp_task_t * pNextTask;
}bsp_task_t;

enum {
    BSP_TASK_STATE_EN       = 1,
    BSP_TASK_STATE_DISEN    = 0
};

/**********************
* GLOBAL PROTOTYPES
**********************/
void          bsp_task_inc_ticks(uint32_t millis);
uint32_t      bsp_task_get_ticks(void);
void          bsp_task_init_time(void);
void          bsp_task_init_list(void);
bsp_task_t *  bsp_task_find(bsp_task_cb_f pFunc);
bsp_task_t *  bsp_task_register(bsp_task_cb_f pFunc, uint32_t period, uint8_t state);
bsp_task_t *  bsp_task_get_prev(bsp_task_t * pHandle);
bsp_task_t *  bsp_task_get_next(bsp_task_t * pHandle);
int           bsp_task_logout(bsp_task_cb_f pFunc);
int           bsp_task_set_state(bsp_task_cb_f pFunc, uint8_t state);
int           bsp_task_set_period(bsp_task_cb_f pFunc, uint32_t period_ms);
float         bsp_task_get_cpu_usage(void);
uint32_t      bsp_task_get_time_cost(bsp_task_cb_f pFunc);
void          bsp_task_handler(void);
/**********************
 *      MACROS
 **********************/

#endif /*_BSP_TASK_H*/


/******************************* (END OF FILE) *********************************/
