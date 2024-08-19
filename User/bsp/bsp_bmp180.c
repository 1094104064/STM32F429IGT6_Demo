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
#if BMP180_DEBUG

static void _bsp_bmp180_log_add( bsp_bmp180_t * self, 
                                        const char * file, 
                                        int line, 
                                        const char * func, 
                                        const char * format, 
                                        ... );

#define LOG(self, ...) _bsp_bmp180_log_add(self, __FILE__, __LINE__, __func__, __VA_ARGS__)

#else 

#define LOG(self, ...)

#endif

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

    self->iic_interface.read_buf(BMP180_DEV_ADDR, BMP180_RESULT_REG, buf, 2);

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

    self->iic_interface.read_buf(BMP180_DEV_ADDR, BMP180_RESULT_REG, buf, 2);

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
                        int8_t  (* pf_iic_write_buf)    (uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len),
                        int8_t  (* pf_iic_read_buf)     (uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len),
#if BMP180_DEBUG
                        void    (* pf_debug_print)      (const char *const fmt, ...),
#endif
                        void    (* pf_delay_init)       (void),
                        void    (* pf_delay_ms)         (uint32_t nms),
                        void    (* pf_delay_us)         (uint32_t nus) )
{   
    int8_t ret = 0;
    uint8_t rec_buf[4] = {0};
    
    memset(self, 0, sizeof(bsp_bmp180_t));

    self->iic_interface.init            = pf_iic_init;
    self->iic_interface.deinit          = pf_iic_deinit;
    self->iic_interface.write_buf       = pf_iic_write_buf;
    self->iic_interface.read_buf        = pf_iic_read_buf;

    if( (self->iic_interface.init           == NULL) ||
        (self->iic_interface.deinit         == NULL) ||
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

#if BMP180_DEBUG

    self->debug_print = pf_debug_print;

    if(self->debug_print == NULL) {
        return -3;
    }

#endif

    self->temp_reg_read       = bsp_bmp180_temp_reg_read;
    self->pressure_reg_read   = bsp_bmp180_pressure_reg_read;
    self->temp_calc           = bsp_bmp180_temp_calc;
    self->pressure_calc       = bsp_bmp180_pressure_calc;
    self->atmosphere_calc     = bsp_bmp180_atmosphere_calc;
    self->altitude_calc       = bsp_bmp180_altitude_calc;


    if(0 != self->iic_interface.init()) {
        return -4;
    }

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xAA, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac1 = (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

    ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xAC, rec_buf, 2);
    if(ret != 0) return ret;
	self->calibration_value.ac2 = (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xAE, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac3 = (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xB0, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac4 = (uint16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xB2, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac5 = (uint16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xB4, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.ac6 = (uint16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xB6, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.b1  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xB8, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.b2  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xBA, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.mb  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xBC, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.mc  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    

	ret = self->iic_interface.read_buf(BMP180_DEV_ADDR, 0xBE, rec_buf, 2);
    if(ret != 0) return ret;
    self->calibration_value.md  =  (int16_t)((rec_buf[0] << 8) | rec_buf[1]);
    
    LOG(self, "Finished!");

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _bsp_bmp180_log_add( bsp_bmp180_t * self, 
            							const char * file, 
            							int line, 
            							const char * func, 
            							const char * format, 
            							... )
{
    char str[512] = {0};
    char * ptr = &str[0];
    
    va_list args;
    va_start(args, format); 
    
    /*Use only the file name not the path*/
    size_t p;
    for(p = strlen(file); p > 0; p--) {
        if(file[p] == '/' || file[p] == '\\') {
            p++;    /*Skip the slash*/
            break;
        }
    }

    self->debug_print("[%s]\t %s: ", "BMP180", func);
    
    vsnprintf(str, 255, format, args);
    va_end(args);

    self->debug_print("%s", ptr);
    
    self->debug_print(" \t(in %s line #%d)\n", &file[p], line);
}


/******************************* (END OF FILE) *********************************/
