/**
  ******************************************************************************
  *
  * @file    core_ltdc.c
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
#include "core_ltdc.h"
/**********************
 *      MACROS
 **********************/

#define LCD_GPIO_CLK	      RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOF |\
						      RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH| RCC_AHB1Periph_GPIOI

#define LTDC_R2_PORT          GPIOH
#define LTDC_R2_PIN           GPIO_Pin_8
#define LTDC_R2_PINSOURCE     GPIO_PinSource8

#define LTDC_R3_PORT          GPIOH
#define LTDC_R3_PIN           GPIO_Pin_9
#define LTDC_R3_PINSOURCE     GPIO_PinSource9

#define LTDC_R4_PORT          GPIOH
#define LTDC_R4_PIN           GPIO_Pin_10
#define LTDC_R4_PINSOURCE     GPIO_PinSource10

#define LTDC_R5_PORT          GPIOH
#define LTDC_R5_PIN           GPIO_Pin_11
#define LTDC_R5_PINSOURCE     GPIO_PinSource11

#define LTDC_R6_PORT          GPIOB
#define LTDC_R6_PIN           GPIO_Pin_1
#define LTDC_R6_PINSOURCE     GPIO_PinSource1
#define LTDC_R6_AF			  GPIO_AF9_LTDC		

#define LTDC_R7_PORT          GPIOG
#define LTDC_R7_PIN           GPIO_Pin_6
#define LTDC_R7_PINSOURCE     GPIO_PinSource6

#define LTDC_G2_PORT          GPIOH
#define LTDC_G2_PIN           GPIO_Pin_13
#define LTDC_G2_PINSOURCE     GPIO_PinSource13

#define LTDC_G3_PORT          GPIOH
#define LTDC_G3_PIN           GPIO_Pin_14
#define LTDC_G3_PINSOURCE     GPIO_PinSource14

#define LTDC_G4_PORT          GPIOH
#define LTDC_G4_PIN           GPIO_Pin_15
#define LTDC_G4_PINSOURCE     GPIO_PinSource15

#define LTDC_G5_PORT          GPIOI
#define LTDC_G5_PIN           GPIO_Pin_0
#define LTDC_G5_PINSOURCE     GPIO_PinSource0

#define LTDC_G6_PORT          GPIOI
#define LTDC_G6_PIN           GPIO_Pin_1
#define LTDC_G6_PINSOURCE     GPIO_PinSource1

#define LTDC_G7_PORT          GPIOI
#define LTDC_G7_PIN           GPIO_Pin_2
#define LTDC_G7_PINSOURCE     GPIO_PinSource2

#define LTDC_B2_PORT          GPIOD
#define LTDC_B2_PIN           GPIO_Pin_6
#define LTDC_B2_PINSOURCE     GPIO_PinSource6

#define LTDC_B3_PORT          GPIOG
#define LTDC_B3_PIN           GPIO_Pin_11
#define LTDC_B3_PINSOURCE     GPIO_PinSource11

#define LTDC_B4_PORT          GPIOI
#define LTDC_B4_PIN           GPIO_Pin_4
#define LTDC_B4_PINSOURCE     GPIO_PinSource4

#define LTDC_B5_PORT          GPIOI
#define LTDC_B5_PIN           GPIO_Pin_5
#define LTDC_B5_PINSOURCE     GPIO_PinSource5

#define LTDC_B6_PORT          GPIOI
#define LTDC_B6_PIN           GPIO_Pin_6
#define LTDC_B6_PINSOURCE     GPIO_PinSource6

#define LTDC_B7_PORT          GPIOI
#define LTDC_B7_PIN           GPIO_Pin_7
#define LTDC_B7_PINSOURCE     GPIO_PinSource7


#define LTDC_CLK_PORT         GPIOG					
#define LTDC_CLK_PIN          GPIO_Pin_7
#define LTDC_CLK_PINSOURCE    GPIO_PinSource7

#define LTDC_HSYNC_PORT       GPIOI					
#define LTDC_HSYNC_PIN        GPIO_Pin_10
#define LTDC_HSYNC_PINSOURCE  GPIO_PinSource10

#define LTDC_VSYNC_PORT       GPIOI					
#define LTDC_VSYNC_PIN        GPIO_Pin_9
#define LTDC_VSYNC_PINSOURCE  GPIO_PinSource9

#define LTDC_DE_PORT          GPIOF					
#define LTDC_DE_PIN           GPIO_Pin_10
#define LTDC_DE_PINSOURCE     GPIO_PinSource10

/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 
core_ltdc_render_info_t g_DispRenderInfo;
/**********************
 *  STATIC PROTOTYPES
 **********************/
static int8_t _core_ltdc_gpio_init(void);
static int8_t _core_ltdc_layer_init(void);
static int8_t _core_ltdc_init(void);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
int8_t core_ltdc_init(void)
{
    _core_ltdc_gpio_init();
    _core_ltdc_init();
	_core_ltdc_layer_init();

	LTDC_Cmd(ENABLE);	//	使能LCD控制器
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE); //	使能DMA2D

    memset(&g_DispRenderInfo, 0, sizeof(g_DispRenderInfo));
    
    g_DispRenderInfo.pixel_byte = PIXEL_BYTE_LAYER0;
    g_DispRenderInfo.color_mode = COLOR_MODE_LAYER0;
    g_DispRenderInfo.flush_dir  = LCD_DISP_DIR_HOR;
    g_DispRenderInfo.layer_addr = LCD_LAYER0_ADDR;
    g_DispRenderInfo.color      = core_ltdc_color_hex(g_DispRenderInfo.color_mode, 0x0000FF);;

    return 0;
}

uint32_t core_ltdc_color_hex(uint32_t color_mode, uint32_t color)
{
	uint16_t Alpha_Value = 0, Red_Value = 0, Green_Value = 0, Blue_Value = 0; //各个颜色通道的值
    uint32_t color_getter = 0;

	if(color_mode == LCD_RGB565){
		Red_Value   = (uint16_t)((color & 0x00F80000) >> 8);
		Green_Value = (uint16_t)((color & 0x0000FC00) >> 5);
		Blue_Value  = (uint16_t)((color &0x000000F8) >> 3);
		color_getter = (uint16_t)(Red_Value | Green_Value | Blue_Value);		
	}
	else if(color_mode == LCD_ARGB1555) {
		if((color & 0xFF000000) == 0)	
			Alpha_Value = 0x0000;
		else
			Alpha_Value = 0x8000;

		Red_Value   = (uint16_t)((color & 0x00F80000) >> 9);	
		Green_Value = (uint16_t)((color & 0x0000F800) >> 6);
		Blue_Value  = (uint16_t)((color & 0x000000F8) >> 3);
		color_getter = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);	
	}
	else if(color_mode == LCD_ARGB4444){

		Alpha_Value = (uint16_t)((color & 0xf0000000) >> 16);
		Red_Value   = (uint16_t)((color & 0x00F00000) >> 12);	
		Green_Value = (uint16_t)((color & 0x0000F000) >> 8);
		Blue_Value  = (uint16_t)((color & 0x000000F8) >> 4);
		color_getter = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);	
	}	
	else {
        color_getter = color;	
    }
		
    return color_getter;
}

int8_t core_ltdc_set_layer(uint8_t layer_idx)
{
    if (layer_idx == 0) {
        g_DispRenderInfo.layer_addr     = LCD_LAYER0_ADDR; 	
        g_DispRenderInfo.color_mode     = COLOR_MODE_LAYER0;		
        g_DispRenderInfo.pixel_byte     = PIXEL_BYTE_LAYER0;	
    }
    else if(layer_idx == 1) {
        g_DispRenderInfo.layer_addr     = LCD_LAYER1_ADDR;	
        g_DispRenderInfo.color_mode     = COLOR_MODE_LAYER1;                           
        g_DispRenderInfo.pixel_byte     = PIXEL_BYTE_LAYER1;		                  
    }

    return 0;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
static int8_t _core_ltdc_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	RCC_AHB1PeriphClockCmd(LCD_GPIO_CLK, ENABLE); 	
						
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

	// LCD 颜色 R 引脚配置 

	GPIO_PinAFConfig(LTDC_R2_PORT, LTDC_R2_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R3_PORT, LTDC_R3_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R4_PORT, LTDC_R4_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R5_PORT, LTDC_R5_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R6_PORT, LTDC_R6_PINSOURCE, LTDC_R6_AF);		//  当B1作为LTDC的引脚时，复用线为 AF9，这一点比较特殊，可查阅STM32数据手册的 74页
	GPIO_PinAFConfig(LTDC_R7_PORT, LTDC_R7_PINSOURCE, GPIO_AF_LTDC);	


	GPIO_InitStruct.GPIO_Pin = LTDC_R2_PIN;
	GPIO_Init(LTDC_R2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R3_PIN;
	GPIO_Init(LTDC_R3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R4_PIN;
	GPIO_Init(LTDC_R4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R5_PIN;
	GPIO_Init(LTDC_R5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R6_PIN;
	GPIO_Init(LTDC_R6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R7_PIN;
	GPIO_Init(LTDC_R7_PORT, &GPIO_InitStruct);

  
  // LCD 颜色 G 引脚配置 
 
	GPIO_PinAFConfig(LTDC_G2_PORT, LTDC_G2_PINSOURCE, GPIO_AF_LTDC); 
	GPIO_PinAFConfig(LTDC_G3_PORT, LTDC_G3_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G4_PORT, LTDC_G4_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G5_PORT, LTDC_G5_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G6_PORT, LTDC_G6_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G7_PORT, LTDC_G7_PINSOURCE, GPIO_AF_LTDC);  
  

	GPIO_InitStruct.GPIO_Pin = LTDC_G2_PIN;
	GPIO_Init(LTDC_G2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G3_PIN;
	GPIO_Init(LTDC_G3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G4_PIN;
	GPIO_Init(LTDC_G4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G5_PIN;
	GPIO_Init(LTDC_G5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G6_PIN;
	GPIO_Init(LTDC_G6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G7_PIN;
	GPIO_Init(LTDC_G7_PORT, &GPIO_InitStruct);

  
  // LCD 颜色 B 引脚配置  
  
	GPIO_PinAFConfig(LTDC_B2_PORT, LTDC_B2_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_B3_PORT, LTDC_B3_PINSOURCE, GPIO_AF_LTDC);
	GPIO_PinAFConfig(LTDC_B4_PORT, LTDC_B4_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_B5_PORT, LTDC_B5_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_B6_PORT, LTDC_B6_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_B7_PORT, LTDC_B7_PINSOURCE, GPIO_AF_LTDC);  

	
	GPIO_InitStruct.GPIO_Pin = LTDC_B2_PIN;
	GPIO_Init(LTDC_B2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B3_PIN;
	GPIO_Init(LTDC_B3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B4_PIN;
	GPIO_Init(LTDC_B4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B5_PIN;
	GPIO_Init(LTDC_B5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B6_PIN;
	GPIO_Init(LTDC_B6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B7_PIN;
	GPIO_Init(LTDC_B7_PORT, &GPIO_InitStruct);

  
  //控制线
	GPIO_PinAFConfig(LTDC_CLK_PORT,   LTDC_CLK_PINSOURCE,  GPIO_AF_LTDC); 
	GPIO_PinAFConfig(LTDC_HSYNC_PORT, LTDC_HSYNC_PINSOURCE,GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_VSYNC_PORT, LTDC_VSYNC_PINSOURCE,GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_DE_PORT,    LTDC_DE_PINSOURCE,   GPIO_AF_LTDC);
    
	GPIO_InitStruct.GPIO_Pin = LTDC_CLK_PIN;
	GPIO_Init(LTDC_CLK_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_HSYNC_PIN;
	GPIO_Init(LTDC_HSYNC_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_VSYNC_PIN;
	GPIO_Init(LTDC_VSYNC_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_DE_PIN;
	GPIO_Init(LTDC_DE_PORT, &GPIO_InitStruct);

	return 0;
}

static int8_t _core_ltdc_layer_init(void)
{
    LTDC_Layer_InitTypeDef LTDC_Layer_InitStruct = {0}; 

    /*!< layer0 显示配置 */
    LTDC_Layer_InitStruct.LTDC_HorizontalStart 	= HBP + 1;
    LTDC_Layer_InitStruct.LTDC_HorizontalStop  	= (LCD_WIDTH + HBP);
    LTDC_Layer_InitStruct.LTDC_VerticalStart   	=  VBP + 1;
    LTDC_Layer_InitStruct.LTDC_VerticalStop    	= (LCD_HEIGHT + VBP);
    LTDC_Layer_InitStruct.LTDC_CFBLineNumber 	= LCD_HEIGHT;               /**< 显示区域的行数*/
    LTDC_Layer_InitStruct.LTDC_PixelFormat     	= COLOR_MODE_LAYER0;        /**< 像素格式设置*/
	
// 配置 layer0 的恒定透明度，最终写入 LTDC_LxCACR 寄存器 
//	需要注意的是，这个参数是直接配置整个 layer0 的透明度，这里设置为255即不透明 
	LTDC_Layer_InitStruct.LTDC_ConstantAlpha 	= 255;                      /**< 取值范围0~255，255表示不透明，0表示完全透明*/

// 设置 layer0 的层混合系数，最终写入 LTDC_LxBFCR 寄存器 
// 该参数用于设置 layer0 和 底层背景 之间的颜色混合系数，计算公式为 ：
// 混合后的颜色 =  BF1 * layer0的颜色 + BF2 * 底层背景的颜色
// 如果 layer0 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
//	更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
	
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_1	= LTDC_BlendingFactor1_CA;    // 混合系数1
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_CA;    // 混合系数2
	
// layer0 的显存地址，本例程使用外部的SDRAM作为显存，起始地址0xD0000000，SDRAM大小为32M
// layer0 显存大小等于 = LCD_WIDTH * LCD_WIDTH * BytesPerPixel_0（每个像素所占字节大小）
// 因为 SDRAM 大小为32M，用户设置的区域一定不能超过这个值！		
	LTDC_Layer_InitStruct.LTDC_CFBStartAdress   = LCD_LAYER0_ADDR; 				//第一层的起始地址

// 配置 layer0 的初始默认颜色，包括A,R,G,B 的值 ，最终写入 LTDC_LxDCCR 寄存器 
	LTDC_Layer_InitStruct.LTDC_DefaultColorAlpha = 0;	// 初始颜色，A
	LTDC_Layer_InitStruct.LTDC_DefaultColorRed 	 = 0;  //	初始颜色，R
 	LTDC_Layer_InitStruct.LTDC_DefaultColorGreen = 0;  //	初始颜色，G
	LTDC_Layer_InitStruct.LTDC_DefaultColorBlue  = 0; 	//	初始颜色，B   
 
   
#if ( COLOR_MODE_LAYER0 == LCD_RGB565 || COLOR_MODE_LAYER0 == LCD_ARGB1555 || COLOR_MODE_LAYER0 == LCD_ARGB4444 ) //判断颜色格式
	
		LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_WIDTH * 2) + 3);	 //每行的像素占的总字节数
		LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_WIDTH * 2); 				 //行间距，某像素的起始处到下一行的起始处的增量
	
#elif ( COLOR_MODE_LAYER0 == LCD_RGB888 || COLOR_MODE_LAYER0 == LCD_ARGB8888  )	//这里ARGB8888和RGB888使用相同的计算方式
	
		LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_WIDTH * 4) + 3);	//每行的像素占的总字节数
		LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_WIDTH * 4);  			   //行间距，某像素的起始处到下一行的起始处的增量
	
		LTDC_DitherCmd(ENABLE);		//使能颜色抖动，24位以上的颜色必须打开，否则无法达到相应的效果
	
#endif	

	LTDC_LayerInit(LTDC_Layer1, &LTDC_Layer_InitStruct);	//初始化层0
 	LTDC_LayerCmd(LTDC_Layer1, ENABLE);  //使能层0
	LTDC_ReloadConfig(LTDC_IMReload); //重新载入参数
	
/*---------------------------------- layer1 显示配置 --------------------------------*/

#if (LCD_LAYERS_NUM == 2)	//当定义了双层时

// 设置 layer1 的层混合系数，最终写入 LTDC_LxBFCR 寄存器 
// 该参数用于设置 layer1 和 (layer0+背景）之间的颜色混合系数，计算公式为 ：
// 混合后的颜色 =  BF1 * layer1的颜色 + BF2 * (layer0+背景混合后的颜色）
// 如果 layer1 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
//	更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_1 	= LTDC_BlendingFactor1_PAxCA;  
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 	= LTDC_BlendingFactor2_PAxCA;

// layer1 的显存地址，本例程使用外部的SDRAM作为显存，起始地址0xD0000000，SDRAM大小为32M
// 由于 layer0 会占用一部分显存，因此设置 layer1 显存时，需要进行一定偏移
	LTDC_Layer_InitStruct.LTDC_CFBStartAdress 	= LCD_LAYER1_ADDR; //层2的起始地址
	
	LTDC_Layer_InitStruct.LTDC_PixelFormat 		= COLOR_MODE_LAYER1;		//像素格式设置
	
	#if	 ( COLOR_MODE_LAYER1 == LCD_RGB565 || COLOR_MODE_LAYER1 == LCD_ARGB1555 || COLOR_MODE_LAYER1 == LCD_ARGB4444 ) //判断颜色格式
	
		LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_WIDTH * 2) + 3);	//每行的像素占的总字节数
		LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_WIDTH * 2);  				//行间距，某像素的起始处到下一行的起始处的增量
	
	#elif  ( COLOR_MODE_LAYER1 == LCD_RGB888 || COLOR_MODE_LAYER1 == LCD_ARGB8888  )	 //这里ARGB8888和RGB888使用相同的计算方式
	
		LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_WIDTH * 4) + 3);	//每行的像素占的总字节数
		LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_WIDTH * 4); 			   //行间距，某像素的起始处到下一行的起始处的增量
	
		LTDC_DitherCmd(ENABLE);		//使能颜色抖动，24位以上的颜色必须打开，否则无法达到相应的效果

	#endif	
	
	LTDC_LayerInit(LTDC_Layer2, &LTDC_Layer_InitStruct);	//初始化层1
	LTDC_LayerCmd(LTDC_Layer2, ENABLE);  //使能层1
	LTDC_ReloadConfig(LTDC_IMReload); //重新载入参数
		
#endif


    return 0;
}

static int8_t _core_ltdc_init(void)
{
    uint16_t LCD_PLLSAIN = 0;		//	用于倍频的PLLSAIN参数，可取范围为50~432
    uint8_t  LCD_PLLSAIR = 3;		//	用于分频的PLLSAIR参数，可取范围为2~7
    uint8_t  LCD_CLKDIV	= 8;		//	LCD时钟分频参数，默认设置为8分频，数值上等于RCC_PLLSAIDivR_Div8

    LTDC_InitTypeDef  LTDC_InitStruct = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, ENABLE); 	//	使能LTDC时钟

    LCD_PLLSAIN = LTDC_CLK * LCD_PLLSAIR * LCD_CLKDIV;	//	根据需要使用的LCD时钟计算PLLSAIN参数，可取范围为50~432
    RCC_PLLSAIConfig(LCD_PLLSAIN, 7, LCD_PLLSAIR);  		//	时钟配置
    RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div8);	 		//	LCD时钟分频设置，要和LCD_CLKDIV对应
    RCC_PLLSAICmd(ENABLE);	//使能PLLSAI时钟
    while(RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET);	//	等待时钟配置完成


    LTDC_InitStruct.LTDC_HSPolarity = LTDC_HSPolarity_AL;    // 低电平有效 	
    LTDC_InitStruct.LTDC_VSPolarity = LTDC_VSPolarity_AL;    // 低电平有效 
    LTDC_InitStruct.LTDC_DEPolarity = LTDC_DEPolarity_AL;    // 低电平有效，要注意的是，很多面板都是高电平有效，但是429需要设置成低电平才能正常显示 
    LTDC_InitStruct.LTDC_PCPolarity = LTDC_PCPolarity_IPC;   // 正常时钟信号
                
    LTDC_InitStruct.LTDC_BackgroundRedValue	    = 0;  // 初始背景色，R	     	     
    LTDC_InitStruct.LTDC_BackgroundGreenValue   = 0;  // 初始背景色，G	        
    LTDC_InitStruct.LTDC_BackgroundBlueValue 	= 0;  // 初始背景色，B 

    LTDC_InitStruct.LTDC_HorizontalSync 		=	HSW - 1;									// 根据屏幕设置参数即可
    LTDC_InitStruct.LTDC_VerticalSync 			= 	VSW	-1 ;
    LTDC_InitStruct.LTDC_AccumulatedHBP 		=	HBP + HSW -1;
    LTDC_InitStruct.LTDC_AccumulatedVBP 		= 	VBP + VSW -1;
    LTDC_InitStruct.LTDC_AccumulatedActiveW 	= 	LCD_WIDTH  + HSW + HBP - 1;
    LTDC_InitStruct.LTDC_AccumulatedActiveH 	= 	LCD_HEIGHT + VSW + VBP - 1;
    LTDC_InitStruct.LTDC_TotalWidth 			=	LCD_WIDTH  + HSW + HBP + HFP - 1; 
    LTDC_InitStruct.LTDC_TotalHeigh 			=	LCD_HEIGHT + VSW + VBP + VFP - 1;

    LTDC_Init(&LTDC_InitStruct);	//	初始化LCD控制器



	return 0;
}

/******************************* (END OF FILE) *********************************/
	
