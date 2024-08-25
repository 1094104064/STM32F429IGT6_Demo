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
#include "core_ltdc.h"
/**********************
 *      MACROS
 **********************/
#define DISP_HOR_RES    480
#define DISP_VER_RES    272

#define PIXEL_FORMAT 


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


int8_t core_dma2d_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
    DMA2D->CR	    &=	~(DMA2D_CR_START);				    //	停止DMA2D
    DMA2D->CR		=	DMA2D_R2M;							//	寄存器到SDRAM
    DMA2D->OPFCCR	=	g_DispRenderInfo.color_mode;						//	设置颜色格式
    DMA2D->OCOLR	=	color;							    //	颜色

    if(g_DispRenderInfo.flush_dir == LCD_DISP_DIR_HOR) {
        DMA2D->OOR		=	LCD_WIDTH - width;
        DMA2D->OMAR		=	g_DispRenderInfo.layer_addr + g_DispRenderInfo.pixel_byte * (LCD_WIDTH * y + x);
        DMA2D->NLR		=	(width << 16) | (height);
    }
    else if(g_DispRenderInfo.flush_dir == LCD_DISP_DIR_VER) {
		DMA2D->OOR		=	LCD_WIDTH - height;
		DMA2D->OMAR		=	g_DispRenderInfo.layer_addr + g_DispRenderInfo.pixel_byte * ((LCD_HEIGHT - x - 1 - width) * LCD_WIDTH + y);	
		DMA2D->NLR		=	(width) | (height << 16);
    }
    else {
        return -1;
    }

	DMA2D->CR	  |=	DMA2D_CR_START;					//	启动DMA2D
		
	while (DMA2D->CR & DMA2D_CR_START) ;			//	等待传输完成

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
	
