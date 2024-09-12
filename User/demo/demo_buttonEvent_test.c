/**
  ******************************************************************************
  *
  * @file    demo_buttonEvent_test.c
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
static void board_key_event_cb(button_event_code_t ecode);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void demo_buttonEvent_test(void)
{
    core_gpio_key_init();
    buttonEvent_tick_init(core_systick_get_ticks);

    button_event_ctx_t button_drv = {0};

    buttonEvent_indev_init(&button_drv, core_gpio_key_get_state, board_key_event_cb);

    for(;;) {
        buttonEvent_handler(&button_drv);
        core_systick_delay_ms(20);
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
static void board_key_event_cb(button_event_code_t ecode)
{
    switch (ecode) {
    case BTN_EVENT_PRESSED:
        LOG_INFO("BTN_EVENT_PRESSED");
        break;
    
    case BTN_EVENT_PRESSING:
        LOG_INFO("BTN_EVENT_PRESSING");
        break;

    case BTN_EVENT_SHORT_CLICKED:
        LOG_INFO("BTN_EVENT_SHORT_CLICKED");
        break;

    case BTN_EVENT_LONG_PRESSED:
        LOG_INFO("BTN_EVENT_LONG_PRESSED");
        break;

    case BTN_EVENT_LONG_PRESSED_REPEAT:
        LOG_INFO("BTN_EVENT_LONG_PRESSED_REPEAT");
        break;

    case BTN_EVENT_LONG_PRESSED_RELEASED:
        LOG_INFO("BTN_EVENT_LONG_PRESSED_RELEASED");
        break;

    case BTN_EVENT_CLICKED:
        LOG_INFO("BTN_EVENT_CLICKED");
        break;

    case BTN_EVENT_RELEASED:
        LOG_INFO("BTN_EVENT_RELEASED");
        break;

    case BTN_EVENT_DOUBLE_CLICKED:
        LOG_INFO("BTN_EVENT_DOUBLE_CLICKED");
        break;

    case BTN_EVENT_CHANGED:
        LOG_INFO("BTN_EVENT_CHANGED");
        break;
    
    default:
        LOG_INFO("Error Event Code");
        break;
    }

}

/******************************* (END OF FILE) *********************************/
	
