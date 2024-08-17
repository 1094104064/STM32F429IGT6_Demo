/**
  ******************************************************************************
  *
  * @file    bsp_tick.h
  * @author  GarMing
  * @brief   Header file of bsp_tick module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_TICK_H
#define _BSP_TICK_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _bsp_tick_t
{
    void     (* init)(void);
    uint32_t (* get)(void);
    void     (* delayms)(uint32_t nms);
    void     (* delayus)(uint32_t nus);
}bsp_tick_t;
/**********************
*  GLOBAL PROTOTYPES
 **********************/

int8_t bsp_tick_init( bsp_tick_t * self, 
                      void     (* pf_init)(void),
                      uint32_t (* pf_get)(void),
                      void     (* pf_delayms)(uint32_t nms),
                      void     (* pf_delayus)(uint32_t nus));

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BSP_TICK_H*/


/******************************* (END OF FILE) *********************************/
