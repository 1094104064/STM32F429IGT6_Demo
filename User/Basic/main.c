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
static void Proj(void);
static void Config(void);
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
    Proj();
    Config();
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
    dev_console_init(DEV_CONSOLE_BAUD_HIGH);
}

/**
  * @brief  All settings.
  * @param  None
  * @retval NULL
  */
static void Config(void)
{
  LOG_USER("Completed!");
}



/**
  * @brief  Program loop.
  * @param  None
  * @retval NULL
  */
static void Loop(void)
{
    for(;;) {
        ex_console_1();
    }
}


/**
  * @brief  Proj information.
  * @param  None
  * @retval NULL
  */
static void Proj(void)
{
    printf("\r\n");
    printf("\r\n");
    LOG_INFO("*************************************************************");
    printf("\r\n");
    LOG_INFO("Project description: Demo base on STM32F429IGT6");
    printf("\r\n");
    LOG_INFO("Project Version: %d.%d.%d", PROJ_VERSION_MAJOR, PROJ_VERSION_MINOR, PROJ_VERSION_PATCH);
    printf("\r\n");
    LOG_INFO("Compile time: (Date)%s,  (Time)%s", __DATE__, __TIME__);
    printf("\r\n");
    LOG_INFO("*************************************************************");
    printf("\r\n");
    printf("\r\n");
}


/******************************* (END OF FILE) *********************************/

   
