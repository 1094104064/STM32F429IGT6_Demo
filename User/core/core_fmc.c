/**
  ******************************************************************************
  *
  * @file    core_fmc.c
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
#include "core_fmc.h"
/**********************
 *      MACROS
 **********************/

#define SDRAM_DELAY_MS(ms) do {for(uint32_t i = 0; i < (ms) * 1000 * 48; i++);} while(0);


#define SDRAM_Size 	0x02000000  //32M字节

#define FMC_BANK_SDRAM            FMC_Bank2_SDRAM 				 // SDRAM 的bank选择
#define FMC_COMMAND_TARGET_BANK   FMC_Command_Target_bank2
#define SDRAM_BANK_ADDR     ((uint32_t)0xD0000000) 			 // FMC SDRAM 数据基地址

// 寄存器定义

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)      


#define FMC_A0_PORT        GPIOF
#define FMC_A0_PIN         GPIO_Pin_0
#define FMC_A0_PINSOURCE   GPIO_PinSource0
#define FMC_A0_AF          GPIO_AF_FMC

#define FMC_A1_PORT        GPIOF
#define FMC_A1_PIN         GPIO_Pin_1
#define FMC_A1_PINSOURCE   GPIO_PinSource1
#define FMC_A1_AF          GPIO_AF_FMC

#define FMC_A2_PORT        GPIOF
#define FMC_A2_PIN         GPIO_Pin_2
#define FMC_A2_PINSOURCE   GPIO_PinSource2
#define FMC_A2_AF          GPIO_AF_FMC

#define FMC_A3_PORT        GPIOF
#define FMC_A3_PIN         GPIO_Pin_3
#define FMC_A3_PINSOURCE   GPIO_PinSource3
#define FMC_A3_AF          GPIO_AF_FMC

#define FMC_A4_PORT        GPIOF
#define FMC_A4_PIN         GPIO_Pin_4
#define FMC_A4_PINSOURCE   GPIO_PinSource4
#define FMC_A4_AF          GPIO_AF_FMC

#define FMC_A5_PORT        GPIOF
#define FMC_A5_PIN         GPIO_Pin_5
#define FMC_A5_PINSOURCE   GPIO_PinSource5
#define FMC_A5_AF          GPIO_AF_FMC

#define FMC_A6_PORT        GPIOF
#define FMC_A6_PIN         GPIO_Pin_12
#define FMC_A6_PINSOURCE   GPIO_PinSource12
#define FMC_A6_AF          GPIO_AF_FMC

#define FMC_A7_PORT        GPIOF
#define FMC_A7_PIN         GPIO_Pin_13
#define FMC_A7_PINSOURCE   GPIO_PinSource13
#define FMC_A7_AF          GPIO_AF_FMC

#define FMC_A8_PORT        GPIOF
#define FMC_A8_PIN         GPIO_Pin_14
#define FMC_A8_PINSOURCE   GPIO_PinSource14
#define FMC_A8_AF          GPIO_AF_FMC

#define FMC_A9_PORT        GPIOF
#define FMC_A9_PIN         GPIO_Pin_15
#define FMC_A9_PINSOURCE   GPIO_PinSource15
#define FMC_A9_AF          GPIO_AF_FMC


#define FMC_A10_PORT        GPIOG
#define FMC_A10_PIN         GPIO_Pin_0
#define FMC_A10_PINSOURCE   GPIO_PinSource0
#define FMC_A10_AF          GPIO_AF_FMC


#define FMC_A11_PORT        GPIOG
#define FMC_A11_PIN         GPIO_Pin_1
#define FMC_A11_PINSOURCE   GPIO_PinSource1
#define FMC_A11_AF          GPIO_AF_FMC

#define FMC_A12_PORT        GPIOG
#define FMC_A12_PIN         GPIO_Pin_2
#define FMC_A12_PINSOURCE   GPIO_PinSource2
#define FMC_A12_AF          GPIO_AF_FMC

/*数据信号线*/
#define FMC_D0_PORT        GPIOD
#define FMC_D0_PIN         GPIO_Pin_14
#define FMC_D0_PINSOURCE   GPIO_PinSource14
#define FMC_D0_AF          GPIO_AF_FMC

#define FMC_D1_PORT        GPIOD
#define FMC_D1_PIN         GPIO_Pin_15
#define FMC_D1_PINSOURCE   GPIO_PinSource15
#define FMC_D1_AF          GPIO_AF_FMC

#define FMC_D2_PORT        GPIOD
#define FMC_D2_PIN         GPIO_Pin_0
#define FMC_D2_PINSOURCE   GPIO_PinSource0
#define FMC_D2_AF          GPIO_AF_FMC

#define FMC_D3_PORT        GPIOD
#define FMC_D3_PIN         GPIO_Pin_1
#define FMC_D3_PINSOURCE   GPIO_PinSource1
#define FMC_D3_AF          GPIO_AF_FMC

#define FMC_D4_PORT        GPIOE
#define FMC_D4_PIN         GPIO_Pin_7
#define FMC_D4_PINSOURCE   GPIO_PinSource7
#define FMC_D4_AF          GPIO_AF_FMC

#define FMC_D5_PORT        GPIOE
#define FMC_D5_PIN         GPIO_Pin_8
#define FMC_D5_PINSOURCE   GPIO_PinSource8
#define FMC_D5_AF          GPIO_AF_FMC

#define FMC_D6_PORT        GPIOE
#define FMC_D6_PIN         GPIO_Pin_9
#define FMC_D6_PINSOURCE   GPIO_PinSource9
#define FMC_D6_AF          GPIO_AF_FMC

#define FMC_D7_PORT        GPIOE
#define FMC_D7_PIN         GPIO_Pin_10
#define FMC_D7_PINSOURCE   GPIO_PinSource10
#define FMC_D7_AF          GPIO_AF_FMC

#define FMC_D8_PORT        GPIOE
#define FMC_D8_PIN         GPIO_Pin_11
#define FMC_D8_PINSOURCE   GPIO_PinSource11
#define FMC_D8_AF          GPIO_AF_FMC

#define FMC_D9_PORT        GPIOE
#define FMC_D9_PIN         GPIO_Pin_12
#define FMC_D9_PINSOURCE   GPIO_PinSource12
#define FMC_D9_AF          GPIO_AF_FMC

#define FMC_D10_PORT        GPIOE
#define FMC_D10_PIN         GPIO_Pin_13
#define FMC_D10_PINSOURCE   GPIO_PinSource13
#define FMC_D10_AF          GPIO_AF_FMC

#define FMC_D11_PORT        GPIOE
#define FMC_D11_PIN         GPIO_Pin_14
#define FMC_D11_PINSOURCE   GPIO_PinSource14
#define FMC_D11_AF          GPIO_AF_FMC

#define FMC_D12_PORT        GPIOE
#define FMC_D12_PIN         GPIO_Pin_15
#define FMC_D12_PINSOURCE   GPIO_PinSource15
#define FMC_D12_AF          GPIO_AF_FMC

#define FMC_D13_PORT        GPIOD
#define FMC_D13_PIN         GPIO_Pin_8
#define FMC_D13_PINSOURCE   GPIO_PinSource8
#define FMC_D13_AF          GPIO_AF_FMC

#define FMC_D14_PORT        GPIOD
#define FMC_D14_PIN         GPIO_Pin_9
#define FMC_D14_PINSOURCE   GPIO_PinSource9
#define FMC_D14_AF          GPIO_AF_FMC

#define FMC_D15_PORT        GPIOD
#define FMC_D15_PIN         GPIO_Pin_10
#define FMC_D15_PINSOURCE   GPIO_PinSource10
#define FMC_D15_AF          GPIO_AF_FMC


/*控制信号线*/  
#define FMC_CS_PORT        GPIOH
#define FMC_CS_PIN         GPIO_Pin_6
#define FMC_CS_PINSOURCE   GPIO_PinSource6
#define FMC_CS_AF          GPIO_AF_FMC

#define FMC_BA0_PORT        GPIOG
#define FMC_BA0_PIN         GPIO_Pin_4
#define FMC_BA0_PINSOURCE   GPIO_PinSource4
#define FMC_BA0_AF          GPIO_AF_FMC

#define FMC_BA1_PORT        GPIOG
#define FMC_BA1_PIN         GPIO_Pin_5
#define FMC_BA1_PINSOURCE   GPIO_PinSource5
#define FMC_BA1_AF          GPIO_AF_FMC

#define FMC_WE_PORT        GPIOC
#define FMC_WE_PIN         GPIO_Pin_0
#define FMC_WE_PINSOURCE   GPIO_PinSource0
#define FMC_WE_AF          GPIO_AF_FMC

#define FMC_RAS_PORT        GPIOF
#define FMC_RAS_PIN         GPIO_Pin_11
#define FMC_RAS_PINSOURCE   GPIO_PinSource11
#define FMC_RAS_AF          GPIO_AF_FMC

#define FMC_CAS_PORT        GPIOG
#define FMC_CAS_PIN         GPIO_Pin_15
#define FMC_CAS_PINSOURCE   GPIO_PinSource15
#define FMC_CAS_AF          GPIO_AF_FMC

#define FMC_CLK_PORT        GPIOG
#define FMC_CLK_PIN         GPIO_Pin_8
#define FMC_CLK_PINSOURCE   GPIO_PinSource8
#define FMC_CLK_AF          GPIO_AF_FMC

#define FMC_CKE_PORT        GPIOH
#define FMC_CKE_PIN         GPIO_Pin_7
#define FMC_CKE_PINSOURCE   GPIO_PinSource7
#define FMC_CKE_AF          GPIO_AF_FMC

/*UDQM LDQM*/
#define FMC_UDQM_PORT        GPIOE
#define FMC_UDQM_PIN         GPIO_Pin_1
#define FMC_UDQM_PINSOURCE   GPIO_PinSource1
#define FMC_UDQM_AF          GPIO_AF_FMC

#define FMC_LDQM_PORT        GPIOE
#define FMC_LDQM_PIN         GPIO_Pin_0
#define FMC_LDQM_PINSOURCE   GPIO_PinSource0
#define FMC_LDQM_AF          GPIO_AF_FMC
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
int8_t core_fmc_sdram_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE |       
								  RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH ,ENABLE); 	

	//IO口配置
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;       //配置为复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;   

	//地址线 
	GPIO_PinAFConfig(FMC_A0_PORT,  FMC_A0_PINSOURCE ,  FMC_A0_AF);	
	GPIO_PinAFConfig(FMC_A1_PORT,  FMC_A1_PINSOURCE ,  FMC_A1_AF);	
	GPIO_PinAFConfig(FMC_A2_PORT,  FMC_A2_PINSOURCE ,  FMC_A2_AF);	
	GPIO_PinAFConfig(FMC_A3_PORT,  FMC_A3_PINSOURCE ,  FMC_A3_AF);  
	GPIO_PinAFConfig(FMC_A4_PORT,  FMC_A4_PINSOURCE ,  FMC_A4_AF);  
	GPIO_PinAFConfig(FMC_A5_PORT,  FMC_A5_PINSOURCE ,  FMC_A5_AF);  
	GPIO_PinAFConfig(FMC_A6_PORT,  FMC_A6_PINSOURCE ,  FMC_A6_AF);  
	GPIO_PinAFConfig(FMC_A7_PORT,  FMC_A7_PINSOURCE ,  FMC_A7_AF);	
	GPIO_PinAFConfig(FMC_A8_PORT,  FMC_A8_PINSOURCE ,  FMC_A8_AF);
	GPIO_PinAFConfig(FMC_A9_PORT,  FMC_A9_PINSOURCE ,  FMC_A9_AF);
	GPIO_PinAFConfig(FMC_A10_PORT, FMC_A10_PINSOURCE , FMC_A10_AF);
	GPIO_PinAFConfig(FMC_A11_PORT, FMC_A11_PINSOURCE , FMC_A11_AF);	 
	GPIO_PinAFConfig(FMC_A12_PORT, FMC_A12_PINSOURCE , FMC_A12_AF);	 
	
	GPIO_InitStructure.GPIO_Pin = FMC_A0_PIN; 
	GPIO_Init(FMC_A0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A1_PIN; 
	GPIO_Init(FMC_A1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A2_PIN; 
	GPIO_Init(FMC_A2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A3_PIN; 
	GPIO_Init(FMC_A3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A4_PIN; 
	GPIO_Init(FMC_A4_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A5_PIN; 
	GPIO_Init(FMC_A5_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A6_PIN; 
	GPIO_Init(FMC_A6_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A7_PIN; 
	GPIO_Init(FMC_A7_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A8_PIN; 
	GPIO_Init(FMC_A8_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A9_PIN; 
	GPIO_Init(FMC_A9_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A10_PIN; 
	GPIO_Init(FMC_A10_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A11_PIN; 
	GPIO_Init(FMC_A11_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A12_PIN; 
	GPIO_Init(FMC_A12_PORT, &GPIO_InitStructure);
	
   //数据线
	GPIO_PinAFConfig(FMC_D0_PORT,  FMC_D0_PINSOURCE ,  FMC_D0_AF);  
	GPIO_PinAFConfig(FMC_D1_PORT,  FMC_D1_PINSOURCE ,  FMC_D1_AF);
	GPIO_PinAFConfig(FMC_D2_PORT,  FMC_D2_PINSOURCE ,  FMC_D2_AF);
	GPIO_PinAFConfig(FMC_D3_PORT,  FMC_D3_PINSOURCE ,  FMC_D3_AF);	 
	GPIO_PinAFConfig(FMC_D4_PORT,  FMC_D4_PINSOURCE ,  FMC_D4_AF);	 
	GPIO_PinAFConfig(FMC_D5_PORT,  FMC_D5_PINSOURCE ,  FMC_D5_AF);	 
	GPIO_PinAFConfig(FMC_D6_PORT,  FMC_D6_PINSOURCE ,  FMC_D6_AF);
	GPIO_PinAFConfig(FMC_D7_PORT,  FMC_D7_PINSOURCE ,  FMC_D7_AF);  
	GPIO_PinAFConfig(FMC_D8_PORT,  FMC_D8_PINSOURCE ,  FMC_D8_AF);  
	GPIO_PinAFConfig(FMC_D9_PORT,  FMC_D9_PINSOURCE ,  FMC_D9_AF);  
	GPIO_PinAFConfig(FMC_D10_PORT, FMC_D10_PINSOURCE , FMC_D10_AF);
	GPIO_PinAFConfig(FMC_D11_PORT, FMC_D11_PINSOURCE , FMC_D11_AF);
	GPIO_PinAFConfig(FMC_D12_PORT, FMC_D12_PINSOURCE , FMC_D12_AF);
	GPIO_PinAFConfig(FMC_D13_PORT, FMC_D13_PINSOURCE , FMC_D13_AF);
	GPIO_PinAFConfig(FMC_D14_PORT, FMC_D14_PINSOURCE , FMC_D14_AF);
	GPIO_PinAFConfig(FMC_D15_PORT, FMC_D15_PINSOURCE , FMC_D15_AF);

  
	GPIO_InitStructure.GPIO_Pin = FMC_D0_PIN; 
	GPIO_Init(FMC_D0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D1_PIN; 
	GPIO_Init(FMC_D1_PORT, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = FMC_D2_PIN; 
	GPIO_Init(FMC_D2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D3_PIN; 
	GPIO_Init(FMC_D3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D4_PIN; 
	GPIO_Init(FMC_D4_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D5_PIN; 
	GPIO_Init(FMC_D5_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D6_PIN; 
	GPIO_Init(FMC_D6_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D7_PIN; 
	GPIO_Init(FMC_D7_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D8_PIN; 
	GPIO_Init(FMC_D8_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D9_PIN; 
	GPIO_Init(FMC_D9_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D10_PIN; 
	GPIO_Init(FMC_D10_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D11_PIN; 
	GPIO_Init(FMC_D11_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D12_PIN; 
	GPIO_Init(FMC_D12_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D13_PIN; 
	GPIO_Init(FMC_D13_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D14_PIN; 
	GPIO_Init(FMC_D14_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D15_PIN; 
	GPIO_Init(FMC_D15_PORT, &GPIO_InitStructure);

  
   //控制线
	GPIO_PinAFConfig(FMC_CS_PORT, FMC_CS_PINSOURCE , FMC_CS_AF);  
	GPIO_PinAFConfig(FMC_BA0_PORT, FMC_BA0_PINSOURCE , FMC_BA0_AF); 
	GPIO_PinAFConfig(FMC_BA1_PORT, FMC_BA1_PINSOURCE , FMC_BA1_AF);	
	GPIO_PinAFConfig(FMC_WE_PORT, FMC_WE_PINSOURCE , FMC_WE_AF);	
	GPIO_PinAFConfig(FMC_RAS_PORT, FMC_RAS_PINSOURCE , FMC_RAS_AF); 
	GPIO_PinAFConfig(FMC_CAS_PORT, FMC_CAS_PINSOURCE , FMC_CAS_AF);  
	GPIO_PinAFConfig(FMC_CLK_PORT, FMC_CLK_PINSOURCE , FMC_CLK_AF);  
	GPIO_PinAFConfig(FMC_CKE_PORT, FMC_CKE_PINSOURCE , FMC_CKE_AF);
	GPIO_PinAFConfig(FMC_UDQM_PORT, FMC_UDQM_PINSOURCE , FMC_UDQM_AF);  
	GPIO_PinAFConfig(FMC_LDQM_PORT, FMC_LDQM_PINSOURCE , FMC_LDQM_AF);  
  
	GPIO_InitStructure.GPIO_Pin = FMC_CS_PIN; 
	GPIO_Init(FMC_CS_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_BA0_PIN; 
	GPIO_Init(FMC_BA0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_BA1_PIN;
	GPIO_Init(FMC_BA1_PORT, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = FMC_WE_PIN; 
	GPIO_Init(FMC_WE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_RAS_PIN; 
	GPIO_Init(FMC_RAS_PORT, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = FMC_CAS_PIN; 
	GPIO_Init(FMC_CAS_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_CLK_PIN; 
	GPIO_Init(FMC_CLK_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_CKE_PIN; 
	GPIO_Init(FMC_CKE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_UDQM_PIN; 
	GPIO_Init(FMC_UDQM_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_LDQM_PIN; 
	GPIO_Init(FMC_LDQM_PORT, &GPIO_InitStructure);


	FMC_SDRAMInitTypeDef  FMC_SDRAMInitStructure;
	FMC_SDRAMTimingInitTypeDef  FMC_SDRAMTimingInitStructure; 

	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);	// 开启FMC时钟

	FMC_SDRAMTimingInitStructure.FMC_LoadToActiveDelay    = 2;  // TMRD: min=12ns (2x11.11ns)  
	FMC_SDRAMTimingInitStructure.FMC_ExitSelfRefreshDelay = 7;  // TXSR: min=72ns (7x11.11ns)  
	FMC_SDRAMTimingInitStructure.FMC_SelfRefreshTime      = 4;  // TRAS: min=42ns (4x11.11ns)    
	FMC_SDRAMTimingInitStructure.FMC_RowCycleDelay        = 7;  // TRC:  min=72ns (7x11.11ns)   
	FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime    = 2;  // TWR:  2 Tck 
	FMC_SDRAMTimingInitStructure.FMC_RPDelay              = 2;  // TRP:  18ns => 2x11.11ns             
	FMC_SDRAMTimingInitStructure.FMC_RCDDelay             = 2;  // TRCD: 12ns => 2x11.11ns 

// 标准库配置FMC BAMK2 的 SDRAM时，没有配置 TRCD 参数，会导致SDRAM工作不正常
// 因为ST已经不对标准库进行维护了，所以这个问题一直存在
// 解决方法是，将TRCD参数和TWR参数进行合并，然后调用库函数对TWR进行配置的时候，会一并配置TRCD
	FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime = (FMC_SDRAMTimingInitStructure.FMC_RCDDelay-1)<<8 | FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime ;
	
	
	FMC_SDRAMInitStructure.FMC_Bank 						= FMC_BANK_SDRAM; 					// 选择BANK区
	FMC_SDRAMInitStructure.FMC_ColumnBitsNumber 		= FMC_ColumnBits_Number_9b; 		// 行地址宽度
	FMC_SDRAMInitStructure.FMC_RowBitsNumber 			= FMC_RowBits_Number_13b;			// 列地址线宽度
	FMC_SDRAMInitStructure.FMC_SDMemoryDataWidth 	= FMC_SDMemory_Width_16b; 			// 数据宽度  
	FMC_SDRAMInitStructure.FMC_InternalBankNumber 	= FMC_InternalBank_Number_4;		// bank数量
	FMC_SDRAMInitStructure.FMC_CASLatency 				= FMC_CAS_Latency_3; 				//	CAS 
	FMC_SDRAMInitStructure.FMC_WriteProtection 		= FMC_Write_Protection_Disable; 	// 禁止写保护
	FMC_SDRAMInitStructure.FMC_SDClockPeriod 			= FMC_SDClock_Period_2; 			// 分频
	FMC_SDRAMInitStructure.FMC_ReadBurst 				= FMC_Read_Burst_Enable;			// 突发模式  
	FMC_SDRAMInitStructure.FMC_ReadPipeDelay 			= FMC_ReadPipe_Delay_1; 			// 读延迟
	FMC_SDRAMInitStructure.FMC_SDRAMTimingStruct 	= &FMC_SDRAMTimingInitStructure;

	FMC_SDRAMInit(&FMC_SDRAMInitStructure); 	// 初始化FMC接口


	FMC_SDRAMCommandTypeDef FMC_SDRAMCommandStructure;
	u32 Reg = 0;	// 定义寄存器变量

	FMC_SDRAMCommandStructure.FMC_CommandMode            = FMC_Command_Mode_CLK_Enabled;	// 开启SDRAM时钟 
	FMC_SDRAMCommandStructure.FMC_CommandTarget          = FMC_COMMAND_TARGET_BANK;			// 选择要控制的区域
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber      = 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);  //等待SDRAM空闲 
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);  						 // 配置SDRAM
	SDRAM_DELAY_MS(5); //延时5ms 
	 

	FMC_SDRAMCommandStructure.FMC_CommandMode 			  = FMC_Command_Mode_PALL;			// 预充电命令
	FMC_SDRAMCommandStructure.FMC_CommandTarget 			  = FMC_COMMAND_TARGET_BANK;		// 选择要控制的区域
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber		  = 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);	//等待SDRAM空闲 
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);							// 配置SDRAM
	SDRAM_DELAY_MS(5); //延时5ms 
	
	//自动刷新配置 
	FMC_SDRAMCommandStructure.FMC_CommandMode				  = FMC_Command_Mode_AutoRefresh; // 使用自动刷新
	FMC_SDRAMCommandStructure.FMC_CommandTarget			  = FMC_COMMAND_TARGET_BANK; 		 // 选择要控制的区域
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber 	  = 4;									 // 自动刷新次数
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;    
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);	//等待SDRAM空闲 
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);							// 配置SDRAM

	//寄存器配置 
	Reg  =   (u32)SDRAM_MODEREG_BURST_LENGTH_2     |		
				SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
				SDRAM_MODEREG_CAS_LATENCY_3           |		
				SDRAM_MODEREG_OPERATING_MODE_STANDARD |
				SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	FMC_SDRAMCommandStructure.FMC_CommandMode				  = FMC_Command_Mode_LoadMode;	// 加载模式寄存器命令
	FMC_SDRAMCommandStructure.FMC_CommandTarget          = FMC_COMMAND_TARGET_BANK;		// 选择要控制的区域
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber		  = 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = Reg;									// 寄存器值
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);	//等待SDRAM空闲 
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);							// 配置SDRAM

	FMC_SetRefreshCount(1386);	// 设置刷新计数器 
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);	//等待SDRAM空闲 


    return 0;
}

int8_t core_fmc_sdram_deinit(void)
{
    return 0;
}


int8_t core_fmc_sdram_test(void)
{
    u32 i = 0;				// 计数变量
    u16 ReadData = 0; 	// 读取到的数据
    u8  ReadData_8b;

    for (i = 0; i < SDRAM_Size / 2; i++) {
        *(__IO u16*) (SDRAM_BANK_ADDR + 2 * i) = (u16)i;		// 写入数据
    }

    for(i = 0; i < SDRAM_Size / 2;i++ ) {
        ReadData = *(__IO u16*)(SDRAM_BANK_ADDR + 2 * i );  // 从SDRAM读出数据	
        if( ReadData != (u16)i ) {                          //检测数据，若不相等，跳出函数,返回检测失败结果。
            return -1;	                                    // 返回失败标志
        }
    }

    for (i = 0; i < 255; i++) {
        *(__IO u8*) (SDRAM_BANK_ADDR + i) = (u8)i;
    }	

    for (i = 0; i < 255; i++) {
        ReadData_8b = *(__IO u8*) (SDRAM_BANK_ADDR + i);
        if( ReadData_8b != (u8)i ) {                        //检测数据，若不相等，跳出函数,返回检测失败结果。
            return -2;	                                // 返回失败标志
        }
    }		
    return 0;	 // 返回成功标志
}


/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
