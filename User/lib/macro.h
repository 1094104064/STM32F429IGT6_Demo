/**
  ******************************************************************************
  *
  * @file    macro.h
  * @author  GarMing
  * @brief   Header file of macro module.
  *
  ******************************************************************************
  **/
  
#ifndef _MACRO_H
#define _MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *      DEFINES
 *********************/

#define REG8(x)         (*((volatile uint8_t  *)(x)))
#define REG16(x)        (*((volatile uint16_t *)(x)))
#define REG32(x)        (*((volatile uint32_t *)(x)))

#define ARRAY_SIZE(x)   (sizeof(x) / sizeof((x)[0]))



/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
* GLOBAL PROTOTYPES
**********************/

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
}
#endif

#endif /*_MACRO_H*/


/******************************* (END OF FILE) *********************************/
