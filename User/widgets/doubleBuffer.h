/**
  ******************************************************************************
  *
  * @file    doubleBuffer.h
  * @author  GarMing
  * @brief   Header file of doubleBuffer module.
  *
  ******************************************************************************
  **/
  
#ifndef _DOUBLEBUFFER_H
#define _DOUBLEBUFFER_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <string.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _double_buffer_ctx_t {
    void *              buffer[2];
    volatile uint8_t    wirte_index;
    volatile uint8_t    read_index;
    volatile uint8_t    read_avaliable[2];
}double_buffer_ctx_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/

void doubleBuffer_init          (double_buffer_ctx_t * self, void * buf0, void * buf1);
void doubleBuffer_get_read_buf  (double_buffer_ctx_t * self, void ** read_buf);
void doubleBuffer_set_read_done (double_buffer_ctx_t * self);
void doubleBuffer_get_write_buf (double_buffer_ctx_t * self, void ** write_buf);
void doubleBuffer_set_write_done(double_buffer_ctx_t * self);

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_DOUBLEBUFFER_H*/


/******************************* (END OF FILE) *********************************/

