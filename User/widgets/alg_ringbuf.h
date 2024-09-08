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
#include <stdint.h>
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

int             alg_ringbuf_init(alg_ringbuf_t * self, char * pBuf, ringbuf_size_t buf_size);
void            alg_ringbuf_enqueue_byte(alg_ringbuf_t * self, char byte);
void            alg_ringbuf_enqueue_data(alg_ringbuf_t * self, const char * pData, ringbuf_size_t data_size);
int             alg_ringbuf_dequeue_byte(alg_ringbuf_t * self, char * pBbyte);
ringbuf_size_t  alg_ringbuf_dequeue_data(alg_ringbuf_t * self, char * pData, ringbuf_size_t data_size);
int             alg_ringbuf_peek(alg_ringbuf_t * self, char * pData, ringbuf_size_t index);



inline uint8_t alg_ringbuf_is_empty(alg_ringbuf_t * self)
{
    return (self->head_index == self->tail_index);
}

inline uint8_t alg_ringbuf_is_full(alg_ringbuf_t * self)
{
    return ((self->head_index - self->tail_index) &
            (self->buf_mask) == self->buf_mask);
}

inline ringbuf_size_t alg_ringbuf_get_items(alg_ringbuf_t * self)
{
    return ((self->head_index - self->tail_index) &
            (self->buf_mask));
}

/**********************
 *      MACROS
 **********************/

#endif /*_ALG_RINGBUF_H*/


/******************************* (END OF FILE) *********************************/
