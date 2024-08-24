/**
  ******************************************************************************
  *
  * @file    core_dma2d.c
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
#include "core_dma2d.h"
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
int8_t core_dma2d_fill_rect_hor(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    // DMA2D->CR	  &=	~(DMA2D_CR_START);				    //	停止DMA2D
    // DMA2D->CR		=	DMA2D_R2M;							//	寄存器到SDRAM
    // DMA2D->OPFCCR	=	LCD.ColorMode;						//	设置颜色格式
    // DMA2D->OCOLR	=	LCD.Color;							//	颜色

    // DMA2D->OOR		=	LCD_Width - width;				//	设置行偏移 
    // DMA2D->OMAR		=	LCD.LayerMemoryAdd + LCD.BytesPerPixel*(LCD_Width * y + x);	// 地址;
    // DMA2D->NLR		=	(width<<16)|(height);			//	设定长度和宽度	

    return 0;
}

int8_t core_dma2d_fill_rect_ver(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    // DMA2D->CR	  &=	~(DMA2D_CR_START);				    //	停止DMA2D
    // DMA2D->CR		=	DMA2D_R2M;							//	寄存器到SDRAM
    // DMA2D->OPFCCR	=	LCD.ColorMode;						//	设置颜色格式
    // DMA2D->OCOLR	=	LCD.Color;							//	颜色



    return 0;
}

int8_t core_dma2d_copy_buffer_hor(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t * color)
{
    return 0;
}

int8_t core_dma2d_copy_buffer_ver(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t * color)
{
    return 0;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
