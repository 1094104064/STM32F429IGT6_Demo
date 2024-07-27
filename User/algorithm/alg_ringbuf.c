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
extern inline uint8_t alg_ringbuf_is_empty(alg_ringbuf_t * pHandle);
extern inline uint8_t alg_ringbuf_is_full(alg_ringbuf_t * pHandle);
extern inline ringbuf_size_t alg_ringbuf_get_items(alg_ringbuf_t * pHandle);
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

int alg_ringbuf_init(alg_ringbuf_t * pHandle, char * pBuf, ringbuf_size_t buf_size)
{
    if (!(buf_size & (buf_size - 1))) {
        return ALG_RINGBUF_FALSE;
    }

    pHandle->pBuf = pBuf;
    pHandle->buf_mask = buf_size - 1;
    pHandle->tail_index = 0;
    pHandle->head_index = 0;

    return ALG_RINGBUF_TRUE;
}

void alg_ringbuf_enqueue_byte(alg_ringbuf_t * pHandle, char byte)
{
    if(alg_ringbuf_is_full(pHandle)) {
        pHandle->tail_index = ((pHandle->tail_index + 1) & pHandle->buf_mask);
    }

    pHandle->pBuf[pHandle->head_index] = byte;
    pHandle->head_index = ((pHandle->head_index + 1) & pHandle->buf_mask);
}

void alg_ringbuf_enqueue_data(alg_ringbuf_t * pHandle, const char * pData, ringbuf_size_t data_size)
{
    for(ringbuf_size_t i = 0; i < data_size; i++) {
        alg_ringbuf_enqueue_byte(pHandle, pData[i]);
    }
}

int alg_ringbuf_dequeue_byte(alg_ringbuf_t * pHandle, char * pBbyte)
{
    if(alg_ringbuf_is_empty(pHandle)) {
        return ALG_RINGBUF_FALSE;
    }

    *pBbyte = pHandle->pBuf[pHandle->tail_index];
    pHandle->tail_index = ((pHandle->tail_index + 1) & pHandle->buf_mask);
    return ALG_RINGBUF_TRUE;
}

ringbuf_size_t alg_ringbuf_dequeue_data(alg_ringbuf_t * pHandle, char * pData, ringbuf_size_t data_size)
{
    if(alg_ringbuf_is_empty(pHandle)) {
        return ALG_RINGBUF_FALSE;
    }

    char * ptr = pData;
    ringbuf_size_t cnt = 0;
    while((cnt < data_size) && (alg_ringbuf_dequeue_byte(pHandle, ptr))) {
        cnt++;
        ptr++;
    }

    return cnt;
}

int alg_ringbuf_peek(alg_ringbuf_t * pHandle, char * pData, ringbuf_size_t index)
{
    if(index >= alg_ringbuf_get_items(pHandle)) {
        return ALG_RINGBUF_FALSE;
    }

    ringbuf_size_t idx = ((pHandle->tail_index + index) & pHandle->buf_mask);
    *pData = pHandle->pBuf[idx];
    
    return ALG_RINGBUF_TRUE;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/





/******************************* (END OF FILE) *********************************/

