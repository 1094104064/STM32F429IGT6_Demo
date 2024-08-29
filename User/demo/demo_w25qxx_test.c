/**
  ******************************************************************************
  *
  * @file    demo_w25qxx_test.c
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
void demo_w25qxx_test(void)
{
    int8_t ret = 0;

    bsp_w25qxx_t dev_w25q64;

    ret = bsp_w25qxx_init(  &dev_w25q64, 
                            core_usart1_print,
                            core_spi1_init,
                            core_spi1_deinit,
                            core_spi1_chip_selection_pin_high,
                            core_spi1_chip_selection_pin_low,
                            core_spi1_send_receive_byte  );

    if(ret != 0) {

        LOG_ERROR("CODE: %d, Initialization failure!", ret);
        return;
    }                 

    uint32_t dev_id = 0;
    dev_w25q64.read_dev_id(&dev_w25q64, &dev_id);

}
/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
