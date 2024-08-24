/**
  ******************************************************************************
  *
  * @file    core_fmc.h
  * @author  GarMing
  * @brief   Header file of core_fmc module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_FMC_H
#define _CORE_FMC_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "stm32f4xx.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
*  GLOBAL PROTOTYPES
 **********************/
int8_t core_fmc_sdram_init(void);
int8_t core_fmc_sdram_deinit(void);
int8_t core_fmc_sdram_test(void);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_FMC_H*/


/******************************* (END OF FILE) *********************************/
