/**
  ******************************************************************************
  *
  * @file    alg_ringbuf.h
  * @author  GarMing
  * @brief   Header file of alg_ringbuf module.
  *
  ******************************************************************************
  **/
  
#ifndef _ALG_RINGBUF_H
#define _ALG_RINGBUF_H

/*********************
 *      INCLUDES
 *********************/
#include "stdint.h"
#include <stddef.h>
/*********************
 *      DEFINES
 *********************/
#define ALG_RINGBUF_TRUE      1
#define ALG_RINGBUF_FALSE     0
/**********************
 *      TYPEDEFS
 **********************/

typedef size_t ringbuf_size_t;

typedef struct _alg_ringbuf_t {
    char * pBuf;
    ringbuf_size_t buf_mask;
    ringbuf_size_t tail_index;
    ringbuf_size_t head_index;
}alg_ringbuf_t;

/**********************
* GLOBAL PROTOTYPES
**********************/


inline uint8_t alg_ringbuf_is_empty(alg_ringbuf_t * pHandle)
{
    return (pHandle->head_index == pHandle->tail_index);
}

inline uint8_t alg_ringbuf_is_full(alg_ringbuf_t * pHandle)
{
    return ((pHandle->head_index - pHandle->tail_index) &
            (pHandle->buf_mask) == pHandle->buf_mask);
}

inline ringbuf_size_t alg_ringbuf_get_items(alg_ringbuf_t * pHandle)
{
    return ((pHandle->head_index - pHandle->tail_index) &
            (pHandle->buf_mask));
}

/**********************
 *      MACROS
 **********************/

#endif /*_ALG_RINGBUF_H*/


/******************************* (END OF FILE) *********************************/
