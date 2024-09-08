/**
  ******************************************************************************
  *
  * @file    alg_ringbuf.c
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
#include "alg_ringbuf.h"
/**********************
 *      MACROS
 **********************/

/*********************
 *      DEFINES
 *********************/
extern inline uint8_t alg_ringbuf_is_empty(alg_ringbuf_t * self);
extern inline uint8_t alg_ringbuf_is_full(alg_ringbuf_t * self);
extern inline ringbuf_size_t alg_ringbuf_get_items(alg_ringbuf_t * self);
/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

int alg_ringbuf_init(alg_ringbuf_t * self, char * pBuf, ringbuf_size_t buf_size)
{
    if (!(buf_size & (buf_size - 1))) {
        return ALG_RINGBUF_FALSE;
    }

    self->pBuf = pBuf;
    self->buf_mask = buf_size - 1;
    self->tail_index = 0;
    self->head_index = 0;

    return ALG_RINGBUF_TRUE;
}

void alg_ringbuf_enqueue_byte(alg_ringbuf_t * self, char byte)
{
    if(alg_ringbuf_is_full(self)) {
        self->tail_index = ((self->tail_index + 1) & self->buf_mask);
    }

    self->pBuf[self->head_index] = byte;
    self->head_index = ((self->head_index + 1) & self->buf_mask);
}

void alg_ringbuf_enqueue_data(alg_ringbuf_t * self, const char * pData, ringbuf_size_t data_size)
{
    for(ringbuf_size_t i = 0; i < data_size; i++) {
        alg_ringbuf_enqueue_byte(self, pData[i]);
    }
}

int alg_ringbuf_dequeue_byte(alg_ringbuf_t * self, char * pBbyte)
{
    if(alg_ringbuf_is_empty(self)) {
        return ALG_RINGBUF_FALSE;
    }

    *pBbyte = self->pBuf[self->tail_index];
    self->tail_index = ((self->tail_index + 1) & self->buf_mask);
    return ALG_RINGBUF_TRUE;
}

ringbuf_size_t alg_ringbuf_dequeue_data(alg_ringbuf_t * self, char * pData, ringbuf_size_t data_size)
{
    if(alg_ringbuf_is_empty(self)) {
        return ALG_RINGBUF_FALSE;
    }

    char * ptr = pData;
    ringbuf_size_t cnt = 0;
    while((cnt < data_size) && (alg_ringbuf_dequeue_byte(self, ptr))) {
        cnt++;
        ptr++;
    }

    return cnt;
}

int alg_ringbuf_peek(alg_ringbuf_t * self, char * pData, ringbuf_size_t index)
{
    if(index >= alg_ringbuf_get_items(self)) {
        return ALG_RINGBUF_FALSE;
    }

    ringbuf_size_t idx = ((self->tail_index + index) & self->buf_mask);
    *pData = self->pBuf[idx];
    
    return ALG_RINGBUF_TRUE;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/





/******************************* (END OF FILE) *********************************/

