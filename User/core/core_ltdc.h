/**
  ******************************************************************************
  *
  * @file    core_ltdc.h
  * @author  GarMing
  * @brief   Header file of core_ltdc module.
  *
  ******************************************************************************
  **/
  
#ifndef _CORE_LTDC_H
#define _CORE_LTDC_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include "stm32f4xx.h"
/*********************
 *      DEFINES
 *********************/

#define HBP  43	              // 根据屏幕的手册进行设置
#define VBP  12
#define HSW  1
#define VSW  1
#define HFP  8
#define VFP  8

#define LTDC_CLK            10
#define LCD_WIDTH           480				//LCD的像素长度
#define LCD_HEIGHT          272				//LCD的像素宽度


#define	LCD_ARGB4444    4  	            // 定义颜色格式 ARGB4444， 对应寄存器 LTDC_LxPFCR 的 PF[2:0]
#define	LCD_ARGB1555    3   	        // 定义颜色格式 ARGB1555， 对应寄存器 LTDC_LxPFCR 的 PF[2:0]
#define	LCD_RGB565      2   	        // 定义颜色格式 RGB565，   对应寄存器 LTDC_LxPFCR 的 PF[2:0]
#define	LCD_RGB888      1   	        // 定义颜色格式 RGB888 ，  对应寄存器 LTDC_LxPFCR 的 PF[2:0]
#define	LCD_ARGB8888    0  	            // 定义颜色格式 ARGB8888 ，对应寄存器 LTDC_LxPFCR 的 PF[2:0]


// 1. 如果只用单层，该参数定义为1即可，使用双层的话，需要修改为 2
// 2. FK429M2 核心板 使用的是外部 SDRAM 作为显存，起始地址0xD0000000，SDRAM大小为32M
// 3. 显存所需空间 = 分辨率 * 每个像素所占字节数，例如 480*272的屏，使用16位色（RGB565或者AEGB1555），需要显存 480*272*2 = 261120 字节
// 4. 不管是单层显示还是双层显示，都不能超过 SDRAM 的大小
//	5. 如果用户需要双层显示，则 layer1 应设置为带透明色的格式，即 ColorMode_1 设置为 ARGB8888 、 ARGB1555 或者 ARGB4444
// 6. 如果只是单层，推荐使用RGB565，这样可以大大减小对系统资源的占用
#define LCD_LAYERS_NUM  1			//定义显示的层数，429可驱动两层显示

#define LCD_DISP_DIR_HOR 1
#define LCD_DISP_DIR_VER 2

/* 定义层0的颜色格式 */
#define COLOR_MODE_LAYER0   LCD_RGB565   	

#if (COLOR_MODE_LAYER0 == LCD_RGB565 || COLOR_MODE_LAYER0 == LCD_ARGB1555 || COLOR_MODE_LAYER0 == LCD_ARGB4444)
    #define PIXEL_BYTE_LAYER0   2
#elif COLOR_MODE_LAYER0 == LCD_RGB888
    #define PIXEL_BYTE_LAYER0   3
#elif COLOR_MODE_LAYER0 == LCD_ARGB8888
    #define PIXEL_BYTE_LAYER0   4
#else
    #define PIXEL_BYTE_LAYER0   2
#endif

/* 定义层1的颜色格式 */
#define COLOR_MODE_LAYER1   LCD_ARGB8888

#if (COLOR_MODE_LAYER1 == LCD_RGB565 || COLOR_MODE_LAYER1 == LCD_ARGB1555 || COLOR_MODE_LAYER1 == LCD_ARGB4444)
    #define PIXEL_BYTE_LAYER1   2
#elif COLOR_MODE_LAYER1 == LCD_RGB888
    #define PIXEL_BYTE_LAYER1   3
#elif COLOR_MODE_LAYER1 == LCD_ARGB8888
    #define PIXEL_BYTE_LAYER1   4
#else
    #define PIXEL_BYTE_LAYER1   2
#endif

#define LCD_LAYER0_ADDR (0xD0000000)
#define LCD_LAYER1_ADDR (LCD_LAYER0_ADDR + (LCD_WIDTH * LCD_HEIGHT * PIXEL_BYTE_LAYER0))


/**********************
 *      TYPEDEFS
 **********************/
typedef struct _core_ltdc_render_info_t {
    uint8_t     pixel_byte;
    uint8_t     color_mode;
    uint8_t     flush_dir;
    uint32_t    layer_addr;
    uint32_t    color;
}core_ltdc_render_info_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/
extern core_ltdc_render_info_t g_DispRenderInfo;

int8_t core_ltdc_init(void);
uint32_t core_ltdc_color_hex(uint32_t color_mode, uint32_t color);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_CORE_LTDC_H*/


/******************************* (END OF FILE) *********************************/
