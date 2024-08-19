/**
  ******************************************************************************
  *
  * @file    bsp_st7735.h
  * @author  GarMing
  * @brief   Header file of bsp_st7735 module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_ST7735_H
#define _BSP_ST7735_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include <stdint.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _st7735_spi_interface_t {
    int8_t (* init)(void);
    int8_t (* deinit)(void);
    
}st7735_spi_interface_t;


typedef struct _bsp_st7735_t {
    st7735_spi_interface_t spi_interface;
}bsp_st7735_t;



/**********************
*  GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BSP_ST7735_H*/


/******************************* (END OF FILE) *********************************/
