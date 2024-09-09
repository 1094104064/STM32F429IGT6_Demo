/**
  ******************************************************************************
  *
  * @file    ringBuffer.h
  * @author  GarMing
  * @brief   Header file of ringBuffer module.
  *
  ******************************************************************************
  **/
  
#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stddef.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef size_t ring_buffer_size_t;

typedef struct _ring_buffer_ctx_t {
    char *              buf_ptr;
    ring_buffer_size_t  buf_mask;
    ring_buffer_size_t  tail_index;
    ring_buffer_size_t  head_index;
}ring_buffer_ctx_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/

int8_t              ringBuffer_init         (ring_buffer_ctx_t * self, char * buf_ptr, ring_buffer_size_t buf_length);
void                ringBuffer_enqueue_byte (ring_buffer_ctx_t * self, char byte);
void                ringBuffer_enqueue_data (ring_buffer_ctx_t * self, const char * data_ptr, ring_buffer_size_t data_length);
int8_t              ringBuffer_dequeue_byte (ring_buffer_ctx_t * self, char * byte);
ring_buffer_size_t  ringBuffer_dequeue_data (ring_buffer_ctx_t * self, char * data_ptr, ring_buffer_size_t data_length);
int8_t              ringBuffer_peek         (ring_buffer_ctx_t * self, char * data_ptr, ring_buffer_size_t idx);

inline uint8_t ringBuffer_is_empty(ring_buffer_ctx_t * self)
{
    return (self->head_index == self->tail_index);
}

inline uint8_t ringBuffer_is_full(ring_buffer_ctx_t * self)
{
    return ((self->head_index - self->tail_index) &
            (self->buf_mask) == self->buf_mask);
}

inline ring_buffer_size_t ringBuffer_get_items(ring_buffer_ctx_t * self)
{
    return ((self->head_index - self->tail_index) &
            (self->buf_mask));
}

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_RINGBUFFER_H*/


/******************************* (END OF FILE) *********************************/

