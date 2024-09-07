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
#define SW_IIC 1
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
    
    bsp_bmp180_t drv_bmp180;

#if SW_IIC
    ret = bsp_bmp180_init( &drv_bmp180,
                             core_swiic_init,
                             core_swiic_deinit, 
                             core_swiic_buf_write,
                             core_swiic_buf_read,

                             core_usart1_print,

                             core_systick_init,
                             core_systick_delay_ms,
                             core_systick_delay_us );    

#else 
   ret = bsp_bmp180_init( &drv_bmp180,
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

    uint32_t reg_temp = 0;
    uint32_t reg_pre = 0;

    drv_bmp180.delay_interface.delay_init();

    for(;;) {

        LOG_INFO("*************************************************************");
        drv_bmp180.temp_reg_read(&drv_bmp180, &reg_temp);
        drv_bmp180.pressure_reg_read(&drv_bmp180, &reg_pre);

        drv_bmp180.temp_calc(&drv_bmp180, reg_temp);
        drv_bmp180.pressure_calc(&drv_bmp180, reg_pre);
        drv_bmp180.altitude_calc(&drv_bmp180);
        drv_bmp180.atmosphere_calc(&drv_bmp180);

        LOG_INFO("temperature = %.1f", drv_bmp180.calculated_value.temperature);
        LOG_INFO("pressure = %.2f", drv_bmp180.calculated_value.pressure);
        LOG_INFO("atmosphere = %.2f", drv_bmp180.calculated_value.atmosphere);
        LOG_INFO("altitude = %.2f", drv_bmp180.calculated_value.altitude);

        drv_bmp180.delay_interface.delay_ms(2000);
    }

}
/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
