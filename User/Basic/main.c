/**
  ******************************************************************************
  *
  * @file    main.c
  * @author  GarMing
  * @brief   Demo Project
  *
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  **/


/*********************
 *      INCLUDES
 *********************/
#include "proj.h"
#include "demo.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void Init(void);
static void Info(void);
static void Demo(void);
static void Loop(void);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

/**
  * @brief  Program entrance.
  * @param  None
  * @retval 0 Exit status of the program
  */
int main(void)
{	
    Init();
    Info();
    Demo();
    Loop();
    
    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
  * @brief  All initialisation.
  * @param  None
  * @retval NULL
  */
static void Init(void)
{
    bsp_init();
}

/**
  * @brief  All settings.
  * @param  None
  * @retval NULL
  */
static void Demo(void)
{
    LOG_USER("Running!");

#if 0
    demo_ioled_flash_light();
#endif

#if 0
    demo_ioled_grad_light();
#endif

#if 0
    demo_console_receive();
#endif

#if 0
    demo_tick_delay_printf();
#endif

#if 0
    demo_task_printf();
#endif

#if 0
    demo_bmp180_test();
#endif

#if 0
    demo_w25qxx_test();
#endif

#if 0
    demo_lcd_test();
#endif

}



/**
  * @brief  Program loop.
  * @param  None
  * @retval NULL
  */
static void Loop(void)
{
    for(;;) {

    }
}


/**
  * @brief  Proj information.
  * @param  None
  * @retval NULL
  */
static void Info(void)
{
    printf("\r\n");
    printf("\r\n");
    LOG_USER("*************************************************************");
    printf("\r\n");
    LOG_USER("Project description: Demo base on STM32F429IGT6");
    printf("\r\n");
    LOG_USER("Project Version: %d.%d.%d", PROJ_VERSION_MAJOR, PROJ_VERSION_MINOR, PROJ_VERSION_PATCH);
    printf("\r\n");
    LOG_USER("Compile time: (Date)%s,  (Time)%s", __DATE__, __TIME__);
    printf("\r\n");
    LOG_USER("System Frequency = %d", SystemCoreClock);
    printf("\r\n");
    LOG_USER("*************************************************************");
    printf("\r\n");
    printf("\r\n");
}


/******************************* (END OF FILE) *********************************/

   
