/**
  ******************************************************************************
  *
  * @file    buttonEvent.h
  * @author  GarMing
  * @brief   Header file of buttonEvent module.
  *
  ******************************************************************************
  **/
  
#ifndef _BUTTONEVENT_H
#define _BUTTONEVENT_H


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
#define BTN_DEF_LONG_PRESSED_TIME       500
#define BTN_DEF_LONG_PRESSED_REP_TIME   200
#define BTN_DEF_DOUBLE_CLICKED_TIME     200
/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    BTN_EVENT_ALL                   = 0,
    BTN_EVENT_PRESSED,
    BTN_EVENT_PRESSING,
    BTN_EVENT_SHORT_CLICKED,
    BTN_EVENT_LONG_PRESSED,
    BTN_EVENT_LONG_PRESSED_REPEAT,
    BTN_EVENT_LONG_PRESSED_RELEASED,
    BTN_EVENT_CLICKED,
    BTN_EVENT_RELEASED,
    BTN_EVENT_DOUBLE_CLICKED,
    BTN_EVENT_CHANGED
}button_event_code_t;

typedef enum {
    BTN_STATE_NO_PRESS,
    BTN_STATE_PRESS,
    BTN_STATE_LONG_PRESS
}button_state_code_t;

typedef uint32_t    (* button_event_get_tick_t)(void);
typedef void        (* button_event_cb_t)(button_event_code_t event_code);
typedef uint8_t     (* button_event_is_press_t)(void);


typedef struct _button_event_ctx_t {
    uint8_t             is_initialized;
    button_state_code_t now_state;
    uint8_t             is_long_pressed;
    uint16_t            long_press_time_cfg;
    uint16_t            long_press_repeat_time_cfg;
    uint16_t            double_click_time_cfg;
    uint32_t            last_long_press_time;
    uint32_t            last_press_time;
    uint32_t            last_click_time;
    uint8_t             (* is_press)(void);
    button_event_cb_t   cb;
}button_event_ctx_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/
void buttonEvent_tick_init      (button_event_get_tick_t pf_get_tick);
void buttonEvent_indev_init     (button_event_ctx_t * self, button_event_is_press_t pf_is_press, button_event_cb_t pf_cb);
void buttonEvent_indev_deinit   (button_event_ctx_t * self);
void buttonEvent_handler        (button_event_ctx_t * self);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BUTTONEVENT_H*/


/******************************* (END OF FILE) *********************************/

