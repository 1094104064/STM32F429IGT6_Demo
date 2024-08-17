/**
  ******************************************************************************
  *
  * @file    bsp_console.h
  * @author  GarMing
  * @brief   Header file of bsp_console module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_CONSOLE_H
#define _BSP_CONSOLE_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdlib.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _bsp_console_t {
    int8_t (* init)(void);
    int8_t (* deinit)(void);
    void   (* rec_cb)(void);
}bsp_console_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/
int8_t bsp_console_init( bsp_console_t * self,
                         int8_t (* pf_init)(void),
                         int8_t (* pf_deinit)(void),
                         void   (* pf_rec_cb)(void));
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BSP_CONSOLE_H*/


/******************************* (END OF FILE) *********************************/
