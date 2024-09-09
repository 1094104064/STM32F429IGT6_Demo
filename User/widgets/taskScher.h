/**
  ******************************************************************************
  *
  * @file    taskScher.h
  * @author  GarMing
  * @brief   Header file of taskScher module.
  *
  ******************************************************************************
  **/
  
#ifndef _TASKSCHER_H
#define _TASKSCHER_H


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
#define MAX_TASK_ITEMS  16
/**********************
 *      TYPEDEFS
 **********************/

typedef void (* task_scher_cb_t)(void);

typedef struct _task_scher_ctx_t {
    uint8_t                     id_num;
    uint8_t                     state;
    uint32_t                    time_period;
    uint32_t                    time_prev;
    uint32_t                    time_cost;
    uint32_t                    time_error;
    task_scher_cb_t             task_cb;
    struct  _task_scher_ctx_t * next_task_handle;
}task_scher_ctx_t;


/**********************
*  GLOBAL PROTOTYPES
 **********************/
void                taskScher_init          (uint32_t (* pf_get_tick)(void));
task_scher_ctx_t *  taskScher_find_task     (task_scher_cb_t pf_task_cb);
task_scher_ctx_t *  taskScher_get_prev_task (task_scher_ctx_t * self);
task_scher_ctx_t *  taskScher_get_next_task (task_scher_ctx_t * self);
task_scher_ctx_t *  taskScher_register_task (task_scher_cb_t pf_task_cb, uint32_t period, uint8_t state);
int8_t              taskScher_logout_task   (task_scher_cb_t pf_task_cb);
int8_t              taskScher_set_state     (task_scher_cb_t pf_task_cb, uint8_t state);
int8_t              taskScher_set_period    (task_scher_cb_t pf_task_cb, uint32_t period_ms);
float               taskScher_get_cpu_usage (void);
uint32_t            taskScher_get_time_cost (task_scher_cb_t pf_task_cb);
void                taskScher_handler       (void);

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_TASKSCHER_H*/


/******************************* (END OF FILE) *********************************/

