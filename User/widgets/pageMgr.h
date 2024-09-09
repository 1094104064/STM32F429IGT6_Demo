/**
  ******************************************************************************
  *
  * @file    pageMgr.h
  * @author  GarMing
  * @brief   Header file of pageMgr module.
  *
  ******************************************************************************
  **/
  
#ifndef _PAGEMGR_H
#define _PAGEMGR_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
/*********************
 *      DEFINES
 *********************/
#define MAX_PAGE 16
/**********************
 *      TYPEDEFS
 **********************/
typedef void (* page_mgr_cb_t)(void);
typedef void (* page_mgr_event_cb_t)(void * obj, int event_code);


typedef struct _page_mgr_ctx_t {
    page_mgr_cb_t       init_cb;
    page_mgr_cb_t       loop_cb;
    page_mgr_cb_t       exit_cb;
    page_mgr_event_cb_t event_cb;
}page_mgr_ctx_t;
/**********************
*  GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_PAGEMGR_H*/


/******************************* (END OF FILE) *********************************/

