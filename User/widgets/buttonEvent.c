/**
  ******************************************************************************
  *
  * @file    buttonEvent.c
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
#include "buttonEvent.h"
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
static uint32_t get_tick_elaps(uint32_t prev_tick);
/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t (* get_tick)(void) = NULL;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void buttonEvent_tick_init(button_event_get_tick_t pf_get_tick)
{
    get_tick = pf_get_tick;
}

void buttonEvent_indev_init(button_event_ctx_t * self, button_event_is_press_t pf_is_press, button_event_cb_t pf_cb)
{
    self->long_press_time_cfg           = BTN_DEF_LONG_PRESSED_TIME;
    self->long_press_repeat_time_cfg    = BTN_DEF_LONG_PRESSED_REP_TIME;
    self->double_click_time_cfg         = BTN_DEF_DOUBLE_CLICKED_TIME;
    self->is_press                      = pf_is_press;
    self->cb                            = pf_cb;

    self->is_initialized = 1;
}

void buttonEvent_indev_deinit(button_event_ctx_t * self)
{
    memset(self, 0, sizeof(button_event_ctx_t));
}

void buttonEvent_handler(button_event_ctx_t * self)
{
    if(get_tick == NULL) {
        return;
    }

    if(self->is_initialized == 0) {
        return;
    }

    uint8_t is_press = self->is_press();

    if((is_press) && (self->now_state == BTN_STATE_NO_PRESS)) {
        self->now_state = BTN_STATE_PRESS;

        self->last_press_time = get_tick();

        self->cb(BTN_EVENT_PRESSED);
        self->cb(BTN_EVENT_CHANGED);
    }

    if(self->now_state == BTN_STATE_NO_PRESS) {
        return;
    }

    if(is_press) {
        self->cb(BTN_EVENT_PRESSING);
    }

    if((is_press) && (get_tick_elaps(self->last_press_time) >= self->long_press_time_cfg)) {
        self->now_state = BTN_STATE_LONG_PRESS;

        if(!self->is_long_pressed) {
            self->cb(BTN_EVENT_LONG_PRESSED);
            self->last_long_press_time = get_tick();
            self->is_long_pressed = 1;
        }
        else if(get_tick_elaps(self->last_long_press_time) >= self->long_press_time_cfg) {
            self->last_long_press_time = get_tick();
            self->cb(BTN_EVENT_LONG_PRESSED_REPEAT);
        }
    }
    else if(!is_press) {
        self->now_state = BTN_STATE_NO_PRESS;

        if(get_tick_elaps(self->last_click_time) < self->double_click_time_cfg) {
            self->cb(BTN_EVENT_DOUBLE_CLICKED);
        }

        if(self->is_long_pressed) {
            self->cb(BTN_EVENT_LONG_PRESSED_RELEASED);
        }

        self->is_long_pressed = 0;
        self->last_click_time = get_tick();

        if(get_tick_elaps(self->last_press_time) < self->long_press_time_cfg) {
            self->cb(BTN_EVENT_SHORT_CLICKED);
        } 

        self->cb(BTN_EVENT_CLICKED);
        self->cb(BTN_EVENT_RELEASED);
        self->cb(BTN_EVENT_CHANGED);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static uint32_t get_tick_elaps(uint32_t prev_tick)
{
    uint32_t act_time = get_tick();

    /*If there is no overflow in sys_time simple subtract*/
    if(act_time >= prev_tick) {
        prev_tick = act_time - prev_tick;
    }
    else {
        prev_tick = UINT32_MAX - prev_tick + 1;
        prev_tick += act_time;
    }

    return prev_tick;
}

/******************************* (END OF FILE) *********************************/
	
