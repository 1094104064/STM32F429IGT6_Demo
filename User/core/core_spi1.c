/**
  ******************************************************************************
  *
  * @file    core_spi1.c
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
#include "core_spi1.h"
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
int8_t core_spi1_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef  SPI_InitStructure = {0};

    /*!< Enable GPIO clocks */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOG, ENABLE);

    /*!< Enable the SPI clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    /*!< Structure param configuration */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

    /*!< SPI SCK pin configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*!< SPI MOSI pin configuration */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*!< SPI MISO pin configuration */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*!< Configure sFLASH Card CS pin in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    /*!< Connect SPI pins to AF5 */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

    /*!< Deselect the FLASH: Chip Select high */
    GPIOG->BSRRL = GPIO_Pin_3;

    /*!< SPI configuration */
    SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;      /**< Full duplex communication*/
    SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;                      /**< Master mode*/
    SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;                      /**< 8-bit data length*/
    SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;                        /**< information*/
    SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;                       /**< Clock Phase configuration*/
    SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;                         /**< Clock Polarity configuration*/
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;              /**< 2-split frequency*/
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;                     /**< Data transfer high first*/
    SPI_InitStructure.SPI_CRCPolynomial     = 7;                                    /**< This bit is invalid when CRC is disabled*/
    SPI_Init(SPI1, &SPI_InitStructure);

    /*!< Enable the sFLASH_SPI  */
    SPI_Cmd(SPI1, ENABLE);	

    return 0;
}

int8_t core_spi1_deinit(void)
{
    /*!< Disable GPIO clocks */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOG, DISABLE);

    /*!< Disable the SPI clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);
    
    return 0;
}

void core_spi1_chip_selection_pin_high(void)
{
    GPIOG->BSRRL = GPIO_Pin_3;
}

void core_spi1_chip_selection_pin_low(void)
{
    GPIOG->BSRRH = GPIO_Pin_3;
}

uint8_t core_spi1_send_receive_byte(uint8_t byte)
{
	/*!< Loop while DR register in not empty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	/*!< Send byte through the SPI peripheral */
	SPI_I2S_SendData(SPI1, byte);

	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI1);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
	
