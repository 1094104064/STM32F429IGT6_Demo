/**
  ******************************************************************************
  *
  * @file    ringBuffer.c
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
#include "ringBuffer.h"
/**********************
 *      MACROS
 **********************/

/*********************
 *      DEFINES
 *********************/
extern inline uint8_t               ringBuffer_is_empty (ring_buffer_ctx_t * self);
extern inline uint8_t               ringBuffer_is_full  (ring_buffer_ctx_t * self);
extern inline ring_buffer_size_t    ringBuffer_get_items(ring_buffer_ctx_t * self);
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
int8_t ringBuffer_init(ring_buffer_ctx_t * self, char * buf_ptr, ring_buffer_size_t buf_length)
{
    if (!(buf_length & (buf_length - 1))) {
        return -1;
    }

    self->buf_ptr = buf_ptr;
    self->buf_mask = buf_length - 1;
    self->tail_index = 0;
    self->head_index = 0;

    return 0;
}

void ringBuffer_enqueue_byte(ring_buffer_ctx_t * self, char byte)
{
    if(ringBuffer_is_full(self)) {
        self->tail_index = ((self->tail_index + 1) & self->buf_mask);
    }

    self->buf_ptr[self->head_index] = byte;
    self->head_index = ((self->head_index + 1) & self->buf_mask);
}

void ringBuffer_enqueue_data(ring_buffer_ctx_t * self, const char * data_ptr, ring_buffer_size_t data_length)
{
    for(ring_buffer_size_t i = 0; i < data_length; i++) {
        ringBuffer_enqueue_byte(self, data_ptr[i]);
    }
}

int8_t ringBuffer_dequeue_byte(ring_buffer_ctx_t * self, char * byte)
{
    if(ringBuffer_is_empty(self)) {
        return -1;
    }

    *byte = self->buf_ptr[self->tail_index];
    self->tail_index = ((self->tail_index + 1) & self->buf_mask);

    return 0;
}

ring_buffer_size_t ringBuffer_dequeue_data(ring_buffer_ctx_t * self, char * data_ptr, ring_buffer_size_t data_length)
{
    if(ringBuffer_is_empty(self)) {
        return 0;
    }

    char * ptr = data_ptr;
    ring_buffer_size_t cnt = 0;

    while((cnt < data_length) && (ringBuffer_dequeue_byte(self, ptr))) {
        cnt++;
        ptr++;
    }

    return cnt;
}

int8_t ringBuffer_peek(ring_buffer_ctx_t * self, char * data_ptr, ring_buffer_size_t idx)
{
    if(idx >= ringBuffer_get_items(self)) {
        return -1;
    }

    idx = ((self->tail_index + idx) & self->buf_mask);
    *data_ptr = self->buf_ptr[idx];
    
    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
