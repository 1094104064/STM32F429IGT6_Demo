/**
  ******************************************************************************
  *
  * @file    core_swiic.c
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
#include "core_swiic.h"
#include "log.h"
/**********************
 *      MACROS
 **********************/
#define IIC_WR        0
#define IIC_RD        1

#define IIC_CLK       RCC_AHB1Periph_GPIOB
#define IIC_PORT      GPIOB
#define IIC_SCL_PIN   GPIO_Pin_6
#define IIC_SDA_PIN   GPIO_Pin_7

#define IIC_SCL_1     IIC_PORT->BSRRL = IIC_SCL_PIN
#define IIC_SCL_0     IIC_PORT->BSRRH = IIC_SCL_PIN

#define IIC_SDA_1     IIC_PORT->BSRRL = IIC_SDA_PIN
#define IIC_SDA_0     IIC_PORT->BSRRH = IIC_SDA_PIN


#define IIC_DELAY_PERIOD    (1000 * 48)
#define IIC_DELAY_MS(ms)    do {for(uint32_t i = 0; i < (ms) * IIC_DELAY_PERIOD; i++);} while(0);
#define IIC_TIME_OUT        1000

#define LOG(...)      LOG_INFO(__VA_ARGS__)

/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/
static int8_t _core_swiic_is_sda_1(void);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

int8_t core_swiic_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    /*!< Enable the GPIO clock */
    RCC_AHB1PeriphClockCmd(IIC_CLK, ENABLE);

    /*!< GPIO_InitStructure members configuration*/
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
    GPIO_InitStructure.GPIO_Pin   = IIC_SCL_PIN | IIC_SDA_PIN;
    GPIO_Init(IIC_PORT, &GPIO_InitStructure);

    return 0;
}

int8_t core_swiic_deinit(void)
{
    /*!< Disable the GPIO clock */
    RCC_AHB1PeriphClockCmd(IIC_CLK, DISABLE);

    return 0;
}

void core_swiic_delay_test(void)
{
    for(;;) {
        IIC_SCL_1;
        IIC_DELAY_MS(1);
        IIC_SCL_0;
        IIC_DELAY_MS(1);
    }
}

int8_t core_swiic_start(void)
{
    /*!< When the SCL is on high power, 
    a down edge appears in the SDA to indicate the I2C bus start signal */
    IIC_SDA_1;
    IIC_SCL_1;
    IIC_DELAY_MS(2);
    IIC_SDA_0;
    IIC_DELAY_MS(2);
    IIC_SCL_0;
    IIC_DELAY_MS(2);

    return 0;
}

int8_t core_swiic_stop(void)
{
    /*!< When the SCL is on high power, 
    an up edge appears in the SDA to indicate the I2C bus stop signal */
    IIC_SDA_0;
    IIC_SCL_1;
    IIC_DELAY_MS(2);
    IIC_SDA_1;  

    return 0;
}

int8_t core_swiic_send_byte(uint8_t byte)
{
    /*!< Send the high byte bit7 first */
    for(uint8_t i = 0; i < 8; i++) {

        if(byte & 0x80) 
            IIC_SDA_1;
        else            
            IIC_SDA_0;

        IIC_DELAY_MS(2);
        IIC_SCL_1;
        IIC_DELAY_MS(2);
        IIC_SCL_0;

        if(7 == i) IIC_SDA_1;   /**< Release bus*/

        byte <<= 1;             /**< Move one bit to the left*/
        IIC_DELAY_MS(2);
    }

    return 0;
}

uint8_t core_swiic_read_byte(void)
{
    uint8_t val = 0;

    /*!< Read the first bit as the data bit7 */
    for(uint8_t i = 0; i < 8; i++) {
        val <<= 1;
        IIC_SCL_1;
        IIC_DELAY_MS(2);

        if(_core_swiic_is_sda_1()) val++;

        IIC_SCL_0;
        IIC_DELAY_MS(2);
    }
    return val;
}

uint8_t core_swiic_wait_ack(void)
{
    uint8_t val;

    IIC_SDA_1;                      /**< CPU releases the SDA bus*/
    IIC_DELAY_MS(2);
    IIC_SCL_1;                      /**< CPU set the SCL to high, the device will return ACK response*/
    IIC_DELAY_MS(2);

    if(_core_swiic_is_sda_1()) val = 1;  

    else val = 0;
    IIC_SCL_0;
    IIC_DELAY_MS(2);
    
    return val;
}

int8_t core_swiic_generate_ack(void)
{
    IIC_SDA_0;      /**< CPU set the SDA to low*/
    IIC_DELAY_MS(2);
    IIC_SCL_1;      /**< CPU generate a clock*/
    IIC_DELAY_MS(2);
    IIC_SCL_0;
    IIC_DELAY_MS(2);
    IIC_SDA_1;      /**< CPU releases the SDA bus*/

    return 0;
}

int8_t core_swiic_generate_nack(void)
{
    IIC_SDA_1;      /**< CPU set the SDA to high*/
    IIC_DELAY_MS(2);
    IIC_SCL_1;      /**< CPU generate a clock*/
    IIC_DELAY_MS(2);
    IIC_SCL_0;
    IIC_DELAY_MS(2); 

    return 0;
}

int8_t core_swiic_buf_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len)
{
    uint32_t ticks = 0;

    core_swiic_start();

    core_swiic_send_byte(dev_addr);
    while(core_swiic_wait_ack()) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("send write device address failed!");
            return -1;
        }
    }

    ticks = 0;

    core_swiic_send_byte(reg_addr);
    while(core_swiic_wait_ack()) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("send reg address failed!");
            return -1;
        }
    }

    ticks = 0;

    for(uint32_t i = 0; i < len; i++) {
        core_swiic_send_byte(*pbuf);
        while(core_swiic_wait_ack()) {
            ticks++;
            if(ticks >= IIC_TIME_OUT) {
                LOG("send data failed!");
                return -1;
            }
        }
        pbuf++;
        ticks = 0;
    }

    core_swiic_stop();

    return 0;
}

int8_t core_swiic_buf_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t * pbuf, uint16_t len)
{
    uint32_t ticks = 0;

    core_swiic_start();

    core_swiic_send_byte(dev_addr);
    while(core_swiic_wait_ack()) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("send write device address failed!");
            return -1;
        }
    }

    ticks = 0;

    core_swiic_send_byte(reg_addr);
    while(core_swiic_wait_ack()) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("send reg address failed!");
            return -1;
        }
    }

    ticks = 0;

    core_swiic_start();
    core_swiic_send_byte(dev_addr + 1);
    while(core_swiic_wait_ack()) {
        ticks++;
        if(ticks >= IIC_TIME_OUT) {
            LOG("send read device address failed!");
            return -1;
        }
    }

    for(uint32_t i = 0; i < (len - 1); i++){
        *pbuf = core_swiic_read_byte();
        pbuf++;
    }

    *pbuf = core_swiic_read_byte();
    core_swiic_generate_nack();

    core_swiic_stop();

    return 0;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
  * @brief  Check whether SDA is High
  * @param  None
  * @retval 1 High, 0 Low
  */
static int8_t _core_swiic_is_sda_1(void)
{
    if((IIC_PORT->IDR & IIC_SDA_PIN) != 0) 
        return 1;
    else 
        return 0;    
}




/******************************* (END OF FILE) *********************************/
