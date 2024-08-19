/**
  ******************************************************************************
  *
  * @file    demo_bmp180_test.c
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
#include "proj.h"
/**********************
 *      MACROS
 **********************/
#define SW_IIC 0
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
void demo_bmp180_test(void)
{
    int8_t ret = 0;
    
    bsp_bmp180_t dev_bmp180;

#if SW_IIC
    ret = bsp_bmp180_init( &dev_bmp180,
                             core_swiic_init,
                             core_swiic_deinit, 
                             core_swiic_buf_write,
                             core_swiic_buf_read,

                             core_usart1_print,

                             core_systick_init,
                             core_systick_delay_ms,
                             core_systick_delay_us );    

#else 
   ret = bsp_bmp180_init( &dev_bmp180,
                            core_hwiic_init,
                            core_hwiic_deinit,
                            core_hwiic_buf_write,
                            core_hwiic_buf_read,

                            core_usart1_print,

                            core_systick_init,
                            core_systick_delay_ms,
                            core_systick_delay_us );

#endif

   if(ret != 0) {
       
       LOG_ERROR("CODE: %d, Initialization failure!", ret);
       return;
   }

    LOG_INFO("bmp180_ac1 = %d", dev_bmp180.calibration_value.ac1);
    LOG_INFO("bmp180_ac2 = %d", dev_bmp180.calibration_value.ac2);
    LOG_INFO("bmp180_ac3 = %d", dev_bmp180.calibration_value.ac3);
    LOG_INFO("bmp180_ac4 = %d", dev_bmp180.calibration_value.ac4);
    LOG_INFO("bmp180_ac5 = %d", dev_bmp180.calibration_value.ac5);
    LOG_INFO("bmp180_ac6 = %d", dev_bmp180.calibration_value.ac6);
    LOG_INFO("bmp180_b1 = %d", dev_bmp180.calibration_value.b1);
    LOG_INFO("bmp180_b2 = %d", dev_bmp180.calibration_value.b2);
    LOG_INFO("bmp180_mb = %d", dev_bmp180.calibration_value.mb);
    LOG_INFO("bmp180_mc = %d", dev_bmp180.calibration_value.mc);
    LOG_INFO("bmp180_md = %d", dev_bmp180.calibration_value.md);

    uint32_t reg_temp = 0;
    uint32_t reg_pre = 0;

    dev_bmp180.delay_interface.delay_init();

    for(;;) {

        LOG_INFO("*************************************************************");
        dev_bmp180.temp_reg_read(&dev_bmp180, &reg_temp);
        dev_bmp180.pressure_reg_read(&dev_bmp180, &reg_pre);

        dev_bmp180.temp_calc(&dev_bmp180, reg_temp);
        dev_bmp180.pressure_calc(&dev_bmp180, reg_pre);
        dev_bmp180.altitude_calc(&dev_bmp180);
        dev_bmp180.atmosphere_calc(&dev_bmp180);

        LOG_INFO("temperature = %.1f", dev_bmp180.calculated_value.temperature);
        LOG_INFO("pressure = %.2f", dev_bmp180.calculated_value.pressure);
        LOG_INFO("atmosphere = %.2f", dev_bmp180.calculated_value.atmosphere);
        LOG_INFO("altitude = %.2f", dev_bmp180.calculated_value.altitude);

        dev_bmp180.delay_interface.delay_ms(2000);
    }

}
/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
