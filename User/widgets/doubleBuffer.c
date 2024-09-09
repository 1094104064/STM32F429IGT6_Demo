/**
  ******************************************************************************
  *
  * @file    doubleBuffer.c
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
#include "doubleBuffer.h"
/**********************
 *      MACROS
 **********************/

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

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

/**
  * @brief  Double buffer initialization
  * @param  self: Pointer to the double buffer structure
  * @param  buf0: Pointer to the first buffer
  * @param  buf1: Pointer to the second buffer
  * @retval None
  */
void doubleBuffer_init(double_buffer_ctx_t * self, void * buf0, void * buf1)
{
    memset(self, 0, sizeof(double_buffer_ctx_t));

    self->buffer[0] = buf0;
    self->buffer[1] = buf1;
}

/**
  * @brief  Get a readable buffer
  * @param  self: Pointer to the double buffer structure
  * @param  read_buf: Pointer to the pointer to the buffer to be read
  * @retval None
  */
void doubleBuffer_get_read_buf(double_buffer_ctx_t * self, void ** read_buf)
{
    if(self->read_avaliable[0]) {
        self->read_index = 0;
    }
    else if(self->read_avaliable[1]) {
        self->read_index = 1;
    }
    else {
        return;
    }

    *read_buf = self->buffer[self->read_index];
}

/**
  * @brief  Notify buffer read completion
  * @param  self: Pointer to the double buffer structure
  * @retval None
  */
void doubleBuffer_set_read_done(double_buffer_ctx_t * self)
{
    self->read_avaliable[self->read_index] = 0;
}

/**
  * @brief  Get writable buffer
  * @param  self: Pointer to the double buffer structure
  * @param  write_buf: Pointer to the pointer to the buffer to be wriye
  * @retval None
  */
void doubleBuffer_get_write_buf(double_buffer_ctx_t * self, void ** write_buf)
{
    if(self->wirte_index == self->read_index) {
        self->wirte_index = !self->read_index;
    }

    *write_buf = self->buffer[self->wirte_index];
}

/**
  * @brief  Notify buffer write completion
  * @param  self: Pointer to the double buffer structure
  * @retval None
  */
void doubleBuffer_set_write_done(double_buffer_ctx_t * self)
{
    self->read_avaliable[self->wirte_index] = 1;
    self->wirte_index = !self->wirte_index;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
