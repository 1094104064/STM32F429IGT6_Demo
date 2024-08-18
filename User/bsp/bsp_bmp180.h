/**
  ******************************************************************************
  *
  * @file    bsp_bmp180.h
  * @author  GarMing
  * @brief   Header file of bsp_bmp180 module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_BMP180_H
#define _BSP_BMP180_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "stm32f4xx.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _bmp180_iic_interface_t {
    int8_t  (* init)(void);
    int8_t  (* deinit)(void);
    int8_t  (* start)(void);
    int8_t  (* stop)(void);
    int8_t  (* send_byte)(uint8_t byte);
    uint8_t (* read_byte)(void);
    uint8_t (* wait_ack)(void);
    int8_t  (* generate_ack)(void);
    int8_t  (* generate_nack)(void);
    int8_t  (* is_busy)(void);
    int8_t  (* write_buf)(uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t byte_num);
    int8_t  (* read_buf)(uint8_t * pbuf, uint8_t dev_addr, uint8_t reg_addr, uint16_t byte_num);
}bmp180_iic_interface_t;


typedef struct _bmp180_delay_interface_t {
    void (* delay_init)(void);
    void (* delay_us)(uint32_t nus);
    void (* delay_ms)(uint32_t nms);
}bmp180_delay_interface_t;

typedef struct _bmp180_calibration_value_t {
    int16_t  ac1;
    int16_t  ac2;
    int16_t  ac3;
    uint16_t ac4;
    uint16_t ac5;
    uint16_t ac6;
    int16_t  b1;
    int16_t  b2;
    int32_t  b5;
    int16_t  mb;
    int16_t  mc;
    int16_t  md;
}bmp180_calibration_value_t;

typedef struct _bmp180_calculated_value_t {
    float  temperature;
    float  pressure;
    float  atmosphere;
    double altitude;
}bmp180_calculated_value_t;


typedef struct _bsp_bmp180_t {
    bmp180_iic_interface_t          iic_interface;
    bmp180_delay_interface_t        delay_interface;
    bmp180_calibration_value_t      calibration_value;
    bmp180_calculated_value_t       calculated_value;
    
    int8_t (* temp_reg_read)(struct _bsp_bmp180_t * self, uint32_t * temp);
    int8_t (* pressure_reg_read)(struct _bsp_bmp180_t * self, uint32_t * pre);
    int8_t (* temp_calc)(struct _bsp_bmp180_t * self, uint32_t val);
    int8_t (* pressure_calc)(struct _bsp_bmp180_t * self, uint32_t val);
    int8_t (* atmosphere_calc)(struct _bsp_bmp180_t * self);
    int8_t (* altitude_calc)(struct _bsp_bmp180_t * self);
    
}bsp_bmp180_t;






/**********************
*  GLOBAL PROTOTYPES
 **********************/
int8_t bsp_bmp180_init( bsp_bmp180_t * self,
                        int8_t  (* pf_iic_init)(void),
                        int8_t  (* pf_iic_deinit)(void),
                        int8_t  (* pf_iic_start)(void),
                        int8_t  (* pf_iic_stop)(void),
                        int8_t  (* pf_iic_send_byte)(uint8_t byte),
                        uint8_t (* pf_iic_read_byte)(void),
                        uint8_t (* pf_iic_wait_ack)(void),
                        int8_t  (* pf_iic_generate_ack)(void),
                        int8_t  (* pf_iic_generate_nack)(void),
                        int8_t  (* pf_iic_is_busy)(void),
                        int8_t  (* pf_iic_write_buf)(uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t byte_num),
                        int8_t  (* pf_iic_read_buf)(uint8_t * pbuf, uint8_t dev_addr, uint8_t reg_addr, uint16_t byte_num),
                        
                        void    (* pf_delay_init)(void),
                        void    (* pf_delay_us)(uint32_t nus),
                        void    (* pf_delay_ms)(uint32_t nms) );
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BSP_BMP180_H*/


/******************************* (END OF FILE) *********************************/
