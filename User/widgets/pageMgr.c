/**
  ******************************************************************************
  *
  * @file    pageMgr.c
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
#include "pageMgr.h"
/**********************
 *      MACROS
 **********************/
#define IS_PAGE_VALID(page) ((page) < (MAX_PAGE))
/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static uint8_t s_PageStack[MAX_PAGE];
static page_mgr_ctx_t s_PagePool[MAX_PAGE];

static volatile uint8_t s_NewPageID;
static volatile uint8_t s_OldPageID;
static volatile uint8_t s_LastPageID;
static volatile uint8_t s_NextPageID;

static volatile uint8_t s_NowPageID;

static volatile uint8_t s_IsPageBusy;

static volatile uint8_t s_PageStackTop;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void pageMgr_init(void)
{
    memset(s_PageStack, 0, sizeof(s_PageStack));
    memset(s_PagePool, 0, sizeof(s_PagePool));

    s_NewPageID = 0;
    s_OldPageID = 0;
    s_LastPageID = 0;
    s_NextPageID = 0;
    s_NowPageID = 0;
    s_IsPageBusy = 0;
    s_PageStackTop = 0;
}

void pageMgr_change_to(uint8_t page_id)
{
    if(!IS_PAGE_VALID(page_id)) {
        return;
    }

    if(!s_IsPageBusy) {
        s_NextPageID = s_NewPageID = page_id;

        s_IsPageBusy = 1;
    }
}

int8_t pageMgr_push(uint8_t page_id)
{
    if(!IS_PAGE_VALID(page_id)) {
        return -1;
    }

    if(s_IsPageBusy) {
        return -2;
    }

    if(s_PageStackTop >= MAX_PAGE - 1) {
        return -3;
    }

    s_PageStackTop++;

    s_PageStack[s_PageStackTop] = page_id;

    pageMgr_change_to(page_id);

    return 0;
}

int8_t pageMgr_pop(void)
{
    if(s_IsPageBusy) {
        return -1;
    }

    if(s_PageStack == 0) {
        return -2;
    }

    s_PageStack[s_PageStackTop] = 0;

    s_PageStackTop--;

    pageMgr_change_to(s_PageStack[s_PageStackTop]);

    return 0;
}

void pageMgr_event_send(void * param, int event_code)
{
    if(s_PagePool[s_NowPageID].event_cb != NULL) {
        s_PagePool[s_NowPageID].event_cb(param, event_code);
    }
}

int8_t pageMgr_register(  uint8_t page_id, 
                            page_mgr_cb_t pf_init_cb,
                            page_mgr_cb_t pf_loop_cb,
                            page_mgr_cb_t pf_exit_cb,
                            page_mgr_event_cb_t pf_event_cb)
{
    if(!IS_PAGE_VALID(page_id)) {
        return -1;
    }

    s_PagePool[page_id].init_cb = pf_init_cb;
    s_PagePool[page_id].loop_cb = pf_loop_cb;
    s_PagePool[page_id].exit_cb = pf_exit_cb;
    s_PagePool[page_id].event_cb = pf_event_cb;

    return 0;

}

void pageMgr_handler(void)
{
    if(s_NewPageID != s_OldPageID) {
        s_IsPageBusy = 1;

        if((s_PagePool[s_OldPageID].exit_cb != NULL) &&
           (IS_PAGE_VALID(s_OldPageID))) 
        {
            s_PagePool[s_OldPageID].exit_cb();
        }

        s_LastPageID = s_OldPageID;

        s_NowPageID = s_NewPageID;

        if((s_PagePool[s_NewPageID].init_cb != NULL) &&
           (IS_PAGE_VALID(s_OldPageID)))
        {
            s_PagePool[s_NewPageID].init_cb();
        }

        s_OldPageID = s_NewPageID;

    }
    else {
        s_IsPageBusy = 0;

        if((s_PagePool[s_NowPageID].loop_cb != NULL) &&
           (IS_PAGE_VALID(s_NowPageID)))
        {
            s_PagePool[s_NowPageID].loop_cb();
        }
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
