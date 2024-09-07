/**
  ******************************************************************************
  *
  * @file    core_hwiic.c
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
#include "core_hwiic.h"
#include "log.h"
/**********************
 *      MACROS
 **********************/
#define IIC             I2C1
#define IIC_GPIO_CLK    RCC_AHB1Periph_GPIOB
#define IIC_PERIPH_CLK  RCC_APB1Periph_I2C1
#define IIC_PORT        GPIOB

#define IIC_SCL_PIN     GPIO_Pin_6
#define IIC_SCL_PIN_SRC GPIO_PinSource6

#define IIC_SDA_PIN     GPIO_Pin_7
#define IIC_SDA_PIN_SRC GPIO_PinSource7

#define IIC_TIME_OUT    1000 * 4800     

#define LOG(...)        LOG_INFO(__VA_ARGS__)
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

/**
  * @brief  Initialize hardware i2c
  * @param  None
  * @retval NULL
  */
int8_t core_hwiic_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    I2C_InitTypeDef I2c_InitStructure = {0};

    RCC_AHB1PeriphClockCmd(IIC_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(IIC_PERIPH_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	

	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN | IIC_SDA_PIN;
	GPIO_Init(IIC_PORT, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, IIC_SCL_PIN_SRC, GPIO_AF_I2C1);
    GPIO_PinAFConfig(GPIOB, IIC_SDA_PIN_SRC, GPIO_AF_I2C1);

    I2c_InitStructure.I2C_Mode                  = I2C_Mode_I2C;
    I2c_InitStructure.I2C_ClockSpeed            = 100000;
    I2c_InitStructure.I2C_DutyCycle             = I2C_DutyCycle_16_9;
    I2c_InitStructure.I2C_Ack                   = I2C_Ack_Enable;
    I2c_InitStructure.I2C_AcknowledgedAddress   = I2C_AcknowledgedAddress_7bit;
    I2c_InitStructure.I2C_OwnAddress1           = 0x00;
    I2C_Init(IIC, &I2c_InitStructure);

    I2C_Cmd(IIC, ENABLE);

    return 0;
}

int8_t core_hwiic_deinit(void)
{
    RCC_AHB1PeriphClockCmd(IIC_GPIO_CLK, DISABLE);
    RCC_APB1PeriphClockCmd(IIC_PERIPH_CLK, DISABLE);

    return 0;
}

int8_t core_hwiic_buf_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len)
{
    uint32_t ticks = 0;

    while(I2C_GetFlagStatus(IIC, I2C_FLAG_BUSY)) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Get busy flag failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_GenerateSTART(IIC, ENABLE);
    while(I2C_CheckEvent(IIC, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Generate start failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_Send7bitAddress(IIC, dev_addr, I2C_Direction_Transmitter);
    while(I2C_CheckEvent(IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Send write device address failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_SendData(IIC, reg_addr);
    while (I2C_CheckEvent(IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Send reg address failed!");
            return -1;
        }
    }

    ticks = 0;

    for(uint32_t i = 0; i < len; i++) {
        I2C_SendData(IIC, *pbuf);

        while (I2C_CheckEvent(IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS) {
            ticks++;
            if(ticks >= IIC_TIME_OUT) {
                LOG("Send data failed!");
                return -1;
            }
        }

        pbuf++;
        ticks = 0;
    }

    ticks = 0;

    I2C_GenerateSTOP(IIC, ENABLE);
    while(I2C_GetFlagStatus(IIC, I2C_FLAG_BUSY)) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Get busy flag failed!");
            return -1;
        }
    }

    return 0;
}

int8_t core_hwiic_buf_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len)
{
    uint32_t ticks = 0;

    while(I2C_GetFlagStatus(IIC, I2C_FLAG_BUSY)) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Get busy flag failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_GenerateSTART(IIC, ENABLE);
    while(I2C_CheckEvent(IIC, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Generate start failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_Send7bitAddress(IIC, dev_addr, I2C_Direction_Transmitter);
    while(I2C_CheckEvent(IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Send write device address failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_SendData(IIC, reg_addr);
    while (I2C_CheckEvent(IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Send reg address failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_GenerateSTOP(IIC, ENABLE);
    while(I2C_GetFlagStatus(IIC, I2C_FLAG_BUSY)) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Get busy flag failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_GenerateSTART(IIC, ENABLE);
    while(I2C_CheckEvent(IIC, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Generate start failed!");
            return -1;
        }
    }

    ticks = 0;

    I2C_Send7bitAddress(IIC, dev_addr + 1, I2C_Direction_Receiver);
    while(I2C_CheckEvent(IIC, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("Send read device address failed!");
            return -1;
        }
    }

    ticks = 0;

    while(len--) {
        if(len == 0) {
            I2C_AcknowledgeConfig(IIC, DISABLE);
            I2C_GenerateSTOP(IIC, ENABLE);
        }

        while(I2C_CheckEvent(IIC, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS) {
            ticks++;
            if(ticks >= IIC_TIME_OUT) {
                LOG("Read data failed!");
                return -1;
            }
        }

        *pbuf = I2C_ReceiveData(IIC);
        pbuf++;
        ticks = 0;
    }

    I2C_AcknowledgeConfig(IIC, ENABLE);

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/******************************* (END OF FILE) *********************************/
