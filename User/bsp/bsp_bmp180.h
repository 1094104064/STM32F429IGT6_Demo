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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
/*********************
 *      DEFINES
 *********************/
#define BMP180_DEBUG    1
/**********************
 *      TYPEDEFS
 **********************/

/** 
* @brief   iic interface object
*/ 
typedef struct _bmp180_iic_interface_t {
    int8_t  (* init)            (void);
    int8_t  (* deinit)          (void);
    int8_t  (* read_buf)        (uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len);
    int8_t  (* write_buf)       (uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len);
}bmp180_iic_interface_t;

/** 
* @brief   delay interface object
*/ 
typedef struct _bmp180_delay_interface_t {
    void (* delay_init) (void);
    void (* delay_ms)   (uint32_t nms);
    void (* delay_us)   (uint32_t nus);
}bmp180_delay_interface_t;

/** 
* @brief   calibration value info
*/ 
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

/** 
* @brief   calculate value info
*/ 
typedef struct _bmp180_calculated_value_t {
    float  temperature;
    float  pressure;
    float  atmosphere;
    double altitude;
}bmp180_calculated_value_t;

/** 
* @brief   bmp180 object
*/  
typedef struct _bsp_bmp180_t {
    bmp180_iic_interface_t          iic_interface;
    bmp180_delay_interface_t        delay_interface;
    bmp180_calibration_value_t      calibration_value;
    bmp180_calculated_value_t       calculated_value;
    
    int8_t (* temp_reg_read)        (struct _bsp_bmp180_t * self, uint32_t * temp);
    int8_t (* pressure_reg_read)    (struct _bsp_bmp180_t * self, uint32_t * pre);
    int8_t (* temp_calc)            (struct _bsp_bmp180_t * self, uint32_t val);
    int8_t (* pressure_calc)        (struct _bsp_bmp180_t * self, uint32_t val);
    int8_t (* atmosphere_calc)      (struct _bsp_bmp180_t * self);
    int8_t (* altitude_calc)        (struct _bsp_bmp180_t * self);

#if BMP180_DEBUG
    void   (* debug_print)          (const char *const fmt, ...);
#endif
}bsp_bmp180_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/
int8_t bsp_bmp180_init( bsp_bmp180_t * self,
                        int8_t  (* pf_iic_init)         (void),
                        int8_t  (* pf_iic_deinit)       (void),
                        int8_t  (* pf_iic_write_buf)    (uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len),
                        int8_t  (* pf_iic_read_buf)     (uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len),
#if BMP180_DEBUG
                        void    (* pf_debug_print)      (const char *const fmt, ...),
#endif
                        void    (* pf_delay_init)       (void),
                        void    (* pf_delay_ms)         (uint32_t nms),
                        void    (* pf_delay_us)         (uint32_t nus) );
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BSP_BMP180_H*/


/******************************* (END OF FILE) *********************************/
