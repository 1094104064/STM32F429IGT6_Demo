/**
  ******************************************************************************
  *
  * @file    bsp_bmp180.c
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
#include "bsp_bmp180.h"
/**********************
 *      MACROS
 **********************/
#define BMP180_DEV_ADDR       0xEE
#define BMP180_ADDR_WR        (BMP180_DEV_ADDR | 0)
#define BMP180_ADDR_RD        (BMP180_DEV_ADDR | 1)

#define BMP180_MESSURE_REG    0XF4
#define BMP180_RESULT_REG     0xF6

#define BMP180_TEMP_REG       0x2E
#define BMP180_PRE_REG        0x34

#define BMP180_OSS            0
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


int8_t bsp_bmp180_temp_reg_read(bsp_bmp180_t * self, uint32_t * temp)
{
    uint8_t data_buf[2] = {0};
    uint8_t buf[4] = {0};
    uint32_t tmp = 0;

    data_buf[0] = BMP180_TEMP_REG;
    self->iic_interface.write_buf(BMP180_DEV_ADDR, BMP180_MESSURE_REG, data_buf, 1);

    self->delay_interface.delay_ms(20);

    self->iic_interface.read_buf(buf, BMP180_DEV_ADDR, BMP180_RESULT_REG, 2);

    tmp = (((buf[0] << 8) | buf[1]));

    *temp = tmp;

    return 0;
}

int8_t bsp_bmp180_pressure_reg_read(bsp_bmp180_t * self, uint32_t * pre)
{
    uint8_t data_buf[2] = {0};
    uint8_t buf[4] = {0};
    uint32_t tmp = 0;

    data_buf[0] = BMP180_PRE_REG;
    self->iic_interface.write_buf(BMP180_DEV_ADDR, BMP180_MESSURE_REG, data_buf, 1);

    self->delay_interface.delay_ms(20);

    self->iic_interface.read_buf(buf, BMP180_DEV_ADDR, BMP180_RESULT_REG, 2);

    tmp = ((buf[0] << 8) | buf[1]);

    *pre = tmp;

    return 0;
}

int8_t bsp_bmp180_temp_calc(bsp_bmp180_t * self, uint32_t val)
{
    int x1 = 0;
    int x2 = 0;
    float t = 0;

    uint16_t ac5 = self->calibration_value.ac5;
    uint16_t ac6 = self->calibration_value.ac6;
    int32_t b5 = self->calibration_value.b5;
    int16_t mc = self->calibration_value.mc;
    int16_t md = self->calibration_value.md;


    x1 = (((long)val - (long)ac6) * (long)ac5) >> 15;
    x2 = ((long)mc << 11) / (x1 + md);
    b5 = x1 + x2;

    t = (b5 + 8) >> 4;
    t = t / 10;

    self->calculated_value.temperature = t;

    return 0;
}

int8_t bsp_bmp180_pressure_calc(bsp_bmp180_t * self, uint32_t val)
{
    int x1 = 0;
    int x2 = 0;
    int x3 = 0;
    int b3 = 0;
    int b6 = 0;
    int p = 0;
    uint32_t b4 = 0;
    uint32_t b7 = 0;


    int16_t ac1 = self->calibration_value.ac1;
    int16_t ac2 = self->calibration_value.ac2;
    int16_t ac3 = self->calibration_value.ac3;
    uint16_t ac4 = self->calibration_value.ac4;
    int16_t b1 = self->calibration_value.b1;
    int16_t b2 = self->calibration_value.b2;
    int32_t b5 = self->calibration_value.b5;

    b6 = b5 - 4000;

    x1 = (b2 * ((b6 * b6) >> 12)) >> 11;
    x2 = (ac2 * b6) >> 11;
    x3 = x1 + x2;
    b3 = ((((long)ac1 * 4 + x3) << BMP180_OSS) + 2) >>2;

    x1 = (ac3 * b6) >> 13;
    x2 = (b1 * ((b6 * b6) >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    b4 = (ac4 * (unsigned long)(x3 + 32768)) >> 15;

    b7 = (unsigned long)((val - b3) * (50000 >> BMP180_OSS));
    if(b7 < 0x80000000) {
        p = (b7 << 1) / b4;
    }
    else {
        p = (b7 / b4) << 1;
    }

    x1 = (p >> 8) * (p >> 8);
    x1 = (x1 * 3038) >> 16;
    x2 = (-7357 * p) >> 16;
    p += (x1 + x2 + 3791) >> 4;

    self->calculated_value.pressure = (float)p;

    return 0;
}

int8_t bsp_bmp180_atmosphere_calc(bsp_bmp180_t * self)
{
    self->calculated_value.atmosphere = self->calculated_value.pressure / 101325;

    return 0;
}

int8_t bsp_bmp180_altitude_calc(bsp_bmp180_t * self)
{
    float a = self->calculated_value.pressure / 101325;
    float b = 1/5.25588;
    double c = pow(a, b);
    c = 1 - c;
    c = c / 0.0000225577;

    self->calculated_value.altitude = c;

    return 0;
}


int8_t bsp_bmp180_init( bsp_bmp180_t * self,
                        int8_t  (* pf_iic_init)         (void),
                        int8_t  (* pf_iic_deinit)       (void),
                        int8_t  (* pf_iic_start)        (void),
                        int8_t  (* pf_iic_stop)         (void),
                        int8_t  (* pf_iic_send_byte)    (uint8_t byte),
                        uint8_t (* pf_iic_read_byte)    (void),
                        uint8_t (* pf_iic_wait_ack)     (void),
                        int8_t  (* pf_iic_generate_ack) (void),
                        int8_t  (* pf_iic_generate_nack)(void),
                        int8_t  (* pf_iic_is_busy)      (void),
                        int8_t  (* pf_iic_write_buf)    (uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t byte_num),
                        int8_t  (* pf_iic_read_buf)     (uint8_t * pbuf, uint8_t dev_addr, uint8_t reg_addr, uint16_t byte_num),
                        
                        void    (* pf_delay_init)       (void),
                        void    (* pf_delay_us)         (uint32_t nus),
                        void    (* pf_delay_ms)         (uint32_t nms) )
{   
    int8_t ret = 0;
    uint8_t rec_buf[4] = {0};
    
    memset(self, 0, sizeof(bsp_bmp180_t));

    self->iic_interface.init            = pf_iic_init;
    self->iic_interface.deinit          = pf_iic_deinit;
    self->iic_interface.start           = pf_iic_start;
    self->iic_interface.stop            = pf_iic_stop;
    self->iic_interface.send_byte       = pf_iic_send_byte;
    self->iic_interface.read_byte       = pf_iic_read_byte;
    self->iic_interface.wait_ack        = pf_iic_wait_ack;
    self->iic_interface.generate_ack    = pf_iic_generate_ack;
    self->iic_interface.generate_nack   = pf_iic_generate_nack;
    self->iic_interface.is_busy         = pf_iic_is_busy;
    self->iic_interface.write_buf       = pf_iic_write_buf;
    self->iic_interface.read_buf        = pf_iic_read_buf;

    if( (self->iic_interface.init           == NULL) ||
        (self->iic_interface.deinit         == NULL) ||
        (self->iic_interface.start          == NULL) ||
        (self->iic_interface.stop           == NULL) ||
        (self->iic_interface.send_byte      == NULL) ||
        (self->iic_interface.read_byte      == NULL) ||
        (self->iic_interface.wait_ack       == NULL) ||
        (self->iic_interface.generate_ack   == NULL) ||
        (self->iic_interface.generate_nack  == NULL) ||
        (self->iic_interface.is_busy        == NULL) ||
        (self->iic_interface.write_buf      == NULL) ||
        (self->iic_interface.read_buf       == NULL) )
    {
        return -1;
    }

    self->delay_interface.delay_init    = pf_delay_init;
    self->delay_interface.delay_us      = pf_delay_us;
    self->delay_interface.delay_ms      = pf_delay_ms;

    if( (self->delay_interface.delay_init   == NULL) ||
        (self->delay_interface.delay_us     == NULL) ||
        (self->delay_interface.delay_ms     == NULL)  )
    {
        return -2;
    }

    self->temp_reg_read       = bsp_bmp180_temp_reg_read;
    self->pressure_reg_read   = bsp_bmp180_pressure_reg_read;
    self->temp_calc           = bsp_bmp180_temp_calc;
    self->pressure_calc       = bsp_bmp180_pressure_calc;
    self->atmosphere_calc     = bsp_bmp180_atmosphere_calc;
    self->altitude_calc       = bsp_bmp180_altitude_calc;


    if(0 != self->iic_interface.init()) {
        return -3;
    }

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xAA, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac1 = (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

    ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xAC, 2);
    if(ret != 0) return ret;
	self->calibration_value.ac2 = (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xAE, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac3 = (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xB0, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac4 = (uint16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xB2, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac5 = (uint16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xB4, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac6 = (uint16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xB6, 2);
    if(ret != 0) return ret;
    self->calibration_value.b1  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xB8, 2);
    if(ret != 0) return ret;
    self->calibration_value.b2  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xBA, 2);
    if(ret != 0) return ret;
    self->calibration_value.mb  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xBC, 2);
    if(ret != 0) return ret;
    self->calibration_value.mc  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(rec_buf, BMP180_DEV_ADDR, 0xBE, 2);
    if(ret != 0) return ret;
    self->calibration_value.md  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
