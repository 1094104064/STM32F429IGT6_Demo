/**
  ******************************************************************************
  *
  * @file    bsp_i2c.h
  * @author  GarMing
  * @brief   Header file of bsp_i2c module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_I2C_H
#define _BSP_I2C_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _bsp_i2c_delay_interface_t {
    void (* init)(void);
    void (* deinit)(void);
    void (* delay_ms)(void);
    void (* delay_us)(void);
}bsp_i2c_delay_interface_t;



typedef struct _bsp_i2c_t {
    int8_t (* init) (void);
    int8_t (* deinit) (void);
    int8_t (* scl_high)(void);
    int8_t (* scl_low)(void);
    int8_t (* sda_high)(void);
    int8_t (* sda_low)(void);
    bsp_i2c_delay_interface_t delay_interface;
}bsp_i2c_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BSP_I2C_H*/


/******************************* (END OF FILE) *********************************/
