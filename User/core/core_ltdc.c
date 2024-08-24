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


#define LTDC_CLK_PORT         GPIOG					//LCD时钟引脚
#define LTDC_CLK_PIN          GPIO_Pin_7
#define LTDC_CLK_PINSOURCE    GPIO_PinSource7

#define LTDC_HSYNC_PORT       GPIOI					//行同步
#define LTDC_HSYNC_PIN        GPIO_Pin_10
#define LTDC_HSYNC_PINSOURCE  GPIO_PinSource10

#define LTDC_VSYNC_PORT       GPIOI					//帧同步
#define LTDC_VSYNC_PIN        GPIO_Pin_9
#define LTDC_VSYNC_PINSOURCE  GPIO_PinSource9

#define LTDC_DE_PORT          GPIOF					//数据使能
#define LTDC_DE_PIN           GPIO_Pin_10
#define LTDC_DE_PINSOURCE     GPIO_PinSource10


#define HBP  43	// 根据屏幕的手册进行设置
#define VBP  12
#define HSW  1
#define VSW  1
#define HFP  8
#define VFP  8

#define LCD_HOR         480				//LCD的像素长度
#define LCD_VER         272				//LCD的像素宽度
#define LCD_MemoryAdd   0xD0000000 	    //显存的起始地址  

#define	LCD_ARGB4444    4  	            // 定义颜色格式 ARGB4444， 对应寄存器 LTDC_LxPFCR 的 PF[2:0]
#define	LCD_ARGB1555    3   	        // 定义颜色格式 ARGB1555， 对应寄存器 LTDC_LxPFCR 的 PF[2:0]
#define	LCD_RGB565      2   	        // 定义颜色格式 RGB565，   对应寄存器 LTDC_LxPFCR 的 PF[2:0]
#define	LCD_RGB888      1   	        // 定义颜色格式 RGB888 ，  对应寄存器 LTDC_LxPFCR 的 PF[2:0]
#define	LCD_ARGB8888    0  	            // 定义颜色格式 ARGB8888 ，对应寄存器 LTDC_LxPFCR 的 PF[2:0]



// 1. 设置LTDC时钟，这里设置为10MHz，即刷新率在60帧左右，过高或者过低都会造成闪烁 
// 2. 这里为了方便计算数值应在3-18之间，单位为MHz，具体设置时钟的代码在 LCD_Init()
// 3. 这里的时钟并不是越快越好！！！
// 4. 过高的时钟会加大对SDRAM的占用，容易造成花屏，并且屏幕本身不支持这么高的刷新率，还会导致屏幕闪烁显示异常等
// 5. 过低的时钟会导致刷新率太低，屏幕会有闪烁
#define 	LCD_CLK   10 	// 10M的时钟，刷新率在60Hz左右


// 1. 如果只用单层，该参数定义为1即可，使用双层的话，需要修改为 2
// 2. FK429M2 核心板 使用的是外部 SDRAM 作为显存，起始地址0xD0000000，SDRAM大小为32M
// 3. 显存所需空间 = 分辨率 * 每个像素所占字节数，例如 480*272的屏，使用16位色（RGB565或者AEGB1555），需要显存 480*272*2 = 261120 字节
// 4. 不管是单层显示还是双层显示，都不能超过 SDRAM 的大小
//	5. 如果用户需要双层显示，则 layer1 应设置为带透明色的格式，即 ColorMode_1 设置为 ARGB8888 、 ARGB1555 或者 ARGB4444
// 6. 如果只是单层，推荐使用RGB565，这样可以大大减小对系统资源的占用
#define 	LCD_NUM_LAYERS  2			//定义显示的层数，429可驱动两层显示

#define	ColorMode_0   LCD_RGB565   		//定义层0的颜色格式
//#define	ColorMode_0   LCD_ARGB1555   
//#define	ColorMode_0   LCD_ARGB4444
//#define	ColorMode_0   LCD_RGB888  
//#define	ColorMode_0   LCD_ARGB8888   

#if  LCD_NUM_LAYERS == 2		

//	#define	ColorMode_1   LCD_RGB565   	//定义层1的颜色格式
//	#define	ColorMode_1   LCD_ARGB1555   
//	#define	ColorMode_1   LCD_ARGB4444   
// #define	ColorMode_1   LCD_RGB888   
	#define	ColorMode_1   LCD_ARGB8888   
	
#endif


#if ( ColorMode_0 == LCD_RGB565 || ColorMode_0 == LCD_ARGB1555 || ColorMode_0 ==LCD_ARGB4444 )
	#define BytesPerPixel_0		2		//16位色模式每个像素占2字节
#elif ColorMode_0 == LCD_RGB888
	#define BytesPerPixel_0		3		//24位色模式每个像素占3字节
#else
	#define BytesPerPixel_0		4		//32位色模式每个像素占4字节
#endif	

#if LCD_NUM_LAYERS == 2

	#if ( ColorMode_1 == LCD_RGB565 || ColorMode_1 == LCD_ARGB1555 || ColorMode_1 == LCD_ARGB4444 )
		#define BytesPerPixel_1		2	//16位色模式每个像素占2字节
	#elif ColorMode_1 == LCD_RGB888	
		#define BytesPerPixel_1		3	//24位色模式每个像素占3字节
	#else	
		#define BytesPerPixel_1		4	//32位色模式每个像素占4字节
	#endif	

	#define LCD_MemoryAdd_OFFSET   LCD_HOR * LCD_VER * BytesPerPixel_0 	 //第二层的显存的偏移地址 

#endif
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
int8_t core_ltdc_init(void)
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


	LTDC_Layer_InitTypeDef LTDC_Layer_InitStruct = {0}; 

	/*---------------------------------- layer0 显示配置 --------------------------------*/

	LTDC_Layer_InitStruct.LTDC_HorizontalStart 	= HBP + 1;
	LTDC_Layer_InitStruct.LTDC_HorizontalStop  	= (LCD_HOR + HBP);
	LTDC_Layer_InitStruct.LTDC_VerticalStart   	=  VBP + 1;
	LTDC_Layer_InitStruct.LTDC_VerticalStop    	= (LCD_VER + VBP);
	LTDC_Layer_InitStruct.LTDC_CFBLineNumber 		= LCD_VER; 					//显示区域的行数
	LTDC_Layer_InitStruct.LTDC_PixelFormat     	= ColorMode_0;	//像素格式设置
	
// 配置 layer0 的恒定透明度，最终写入 LTDC_LxCACR 寄存器 
//	需要注意的是，这个参数是直接配置整个 layer0 的透明度，这里设置为255即不透明 
	LTDC_Layer_InitStruct.LTDC_ConstantAlpha 		= 255; // 取值范围0~255，255表示不透明，0表示完全透明

// 设置 layer0 的层混合系数，最终写入 LTDC_LxBFCR 寄存器 
// 该参数用于设置 layer0 和 底层背景 之间的颜色混合系数，计算公式为 ：
// 混合后的颜色 =  BF1 * layer0的颜色 + BF2 * 底层背景的颜色
// 如果 layer0 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
//	更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
	
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_1	= LTDC_BlendingFactor1_CA;    // 混合系数1
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 	= LTDC_BlendingFactor2_CA;    // 混合系数2
	
// layer0 的显存地址，本例程使用外部的SDRAM作为显存，起始地址0xD0000000，SDRAM大小为32M
// layer0 显存大小等于 = LCD_HOR * LCD_HOR * BytesPerPixel_0（每个像素所占字节大小）
// 因为 SDRAM 大小为32M，用户设置的区域一定不能超过这个值！		
	LTDC_Layer_InitStruct.LTDC_CFBStartAdress 	= LCD_MemoryAdd; 				//第一层的起始地址

// 配置 layer0 的初始默认颜色，包括A,R,G,B 的值 ，最终写入 LTDC_LxDCCR 寄存器 
	LTDC_Layer_InitStruct.LTDC_DefaultColorAlpha = 0;	// 初始颜色，A
	LTDC_Layer_InitStruct.LTDC_DefaultColorRed 	= 0;  //	初始颜色，R
 	LTDC_Layer_InitStruct.LTDC_DefaultColorGreen = 0;  //	初始颜色，G
	LTDC_Layer_InitStruct.LTDC_DefaultColorBlue 	= 0; 	//	初始颜色，B   
 
   
#if ( ColorMode_0 == LCD_RGB565 || ColorMode_0 == LCD_ARGB1555 || ColorMode_0 == LCD_ARGB4444 ) //判断颜色格式
	
		LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_HOR * 2) + 3);	 //每行的像素占的总字节数
		LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_HOR * 2); 				 //行间距，某像素的起始处到下一行的起始处的增量
	
#elif ( ColorMode_0 == LCD_RGB888 || ColorMode_0 == LCD_ARGB8888  )	//这里ARGB8888和RGB888使用相同的计算方式
	
		LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_HOR * 4) + 3);	//每行的像素占的总字节数
		LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_HOR * 4);  			   //行间距，某像素的起始处到下一行的起始处的增量
	
		LTDC_DitherCmd(ENABLE);		//使能颜色抖动，24位以上的颜色必须打开，否则无法达到相应的效果
	
#endif	

	LTDC_LayerInit(LTDC_Layer1, &LTDC_Layer_InitStruct);	//初始化层0
 	LTDC_LayerCmd(LTDC_Layer1, ENABLE);  //使能层0
	LTDC_ReloadConfig(LTDC_IMReload); //重新载入参数
	
/*---------------------------------- layer1 显示配置 --------------------------------*/

#if ( LCD_NUM_LAYERS == 2 )	//当定义了双层时

// 设置 layer1 的层混合系数，最终写入 LTDC_LxBFCR 寄存器 
// 该参数用于设置 layer1 和 (layer0+背景）之间的颜色混合系数，计算公式为 ：
// 混合后的颜色 =  BF1 * layer1的颜色 + BF2 * (layer0+背景混合后的颜色）
// 如果 layer1 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
//	更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_1 	= LTDC_BlendingFactor1_PAxCA;  
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 	= LTDC_BlendingFactor2_PAxCA;

// layer1 的显存地址，本例程使用外部的SDRAM作为显存，起始地址0xD0000000，SDRAM大小为32M
// 由于 layer0 会占用一部分显存，因此设置 layer1 显存时，需要进行一定偏移
	LTDC_Layer_InitStruct.LTDC_CFBStartAdress 	= LCD_MemoryAdd + LCD_MemoryAdd_OFFSET; //层2的起始地址
	
	LTDC_Layer_InitStruct.LTDC_PixelFormat 		= ColorMode_1;		//像素格式设置
	
	#if	 ( ColorMode_1 == LCD_RGB565 || ColorMode_1 == LCD_ARGB1555 || ColorMode_1 == LCD_ARGB4444 ) //判断颜色格式
	
		LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_HOR * 2) + 3);	//每行的像素占的总字节数
		LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_HOR * 2);  				//行间距，某像素的起始处到下一行的起始处的增量
	
	#elif  ( ColorMode_1 == LCD_RGB888 || ColorMode_1 == LCD_ARGB8888  )	 //这里ARGB8888和RGB888使用相同的计算方式
	
		LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_HOR * 4) + 3);	//每行的像素占的总字节数
		LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_HOR * 4); 			   //行间距，某像素的起始处到下一行的起始处的增量
	
		LTDC_DitherCmd(ENABLE);		//使能颜色抖动，24位以上的颜色必须打开，否则无法达到相应的效果

	#endif	
	
	LTDC_LayerInit(LTDC_Layer2, &LTDC_Layer_InitStruct);	//初始化层1
	LTDC_LayerCmd(LTDC_Layer2, ENABLE);  //使能层1
	LTDC_ReloadConfig(LTDC_IMReload); //重新载入参数
		
#endif


    return 0;
}

int8_t core_ltdc_deinit(void)
{
    RCC_AHB1PeriphClockCmd(LCD_GPIO_CLK, DISABLE); 

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
