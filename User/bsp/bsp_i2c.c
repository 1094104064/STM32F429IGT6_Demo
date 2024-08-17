/**
  ******************************************************************************
  *
  * @file    bsp_i2c.c
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
#include "bsp_i2c.h"
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
 
int8_t bsp_i2c_init()
{

}


int8_t bsp_i2c_start(bsp_i2c_t * self)
{
    self->sda_high();
    self->scl_high();
    self->delay_interface.delay_ms(2);
}


int8_t bsp_i2c_stop()
{
    
}

int8_t bsp_i2c_send_byte()
{
    
}


uint8_t bsp_i2c_read_byte()
{
    
}


uint8_t bsp_i2c_wait_ack()
{
    
}


int8_t bsp_i2c_generate_ack()
{
    
}


int8_t bsp_i2c_generate_nack()
{
    
}


int8_t bsp_i2c_check_device()
{
    
}





/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
