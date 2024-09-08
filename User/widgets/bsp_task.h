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

typedef struct _bsp_task_heartbeat_interface_t {
    void     (* init)(void);
    void     (* deinit)(void);
    uint32_t (* get_beat)(void);
}bsp_task_heartbeat_interface_t;


typedef struct _bsp_task_class_t {
    bsp_task_heartbeat_interface_t hearbeat_interface;
}bsp_task_class_t;



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
*  GLOBAL PROTOTYPES
 **********************/

void bsp_task_tick_init( bsp_task_class_t * self,
                         void     (* pf_init)(void),
                         void     (* pf_deinit)(void),
                         uint32_t (* pf_get_beat)(void) );
void          bsp_task_init_list(void);
bsp_task_t *  bsp_task_find(bsp_task_cb_f pFunc);
bsp_task_t *  bsp_task_register(bsp_task_cb_f pFunc, uint32_t period, uint8_t state);
bsp_task_t *  bsp_task_get_prev(bsp_task_t * pHandle);
bsp_task_t *  bsp_task_get_next(bsp_task_t * pHandle);
int           bsp_task_logout(bsp_task_cb_f pFunc);
int           bsp_task_set_state(bsp_task_cb_f pFunc, uint8_t state);
int           bsp_task_set_period(bsp_task_cb_f pFunc, uint32_t period_ms);
float         bsp_task_get_cpu_usage(bsp_task_class_t * self);
uint32_t      bsp_task_get_time_cost(bsp_task_cb_f pFunc);
void          bsp_task_handler(bsp_task_class_t * self);
/**********************
 *      MACROS
 **********************/

#endif /*_BSP_TASK_H*/


/******************************* (END OF FILE) *********************************/
