/**
  ******************************************************************************
  *
  * @file    dev_console.c
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
#include "dev_console.h"
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
static void dev_console_gpio_init(void);
static void dev_console_nvic_init(void);
static void dev_console_uart_init(uint32_t baud);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void dev_console_init(uint32_t baud)
{
    dev_console_gpio_init();
    dev_console_nvic_init();
    dev_console_uart_init(baud);
}


void dev_console_deinit(void)
{

}

/**
  * @brief  redirect fputc function to use printf.
  * @param  c: character
  * @param  fp: file pointer
  * @retval Returns a character if normal, or EOF if there is an error.
  */
int fputc(int c, FILE *fp)
{
    /*!< Send single byte */
    USART_SendData(USART1, (uint8_t)c);	
    
    /*!< Waiting for sending to complete */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	

    return (c); 
}





/**********************
 *   STATIC FUNCTIONS
 **********************/
static void dev_console_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /*!< Enable the Usart1 GPIO clock */
    RCC_AHB1PeriphClockCmd (DEV_CONSOLE_TX_CLK | DEV_CONSOLE_RX_CLK, ENABLE); 	

    /*!< GPIO_InitStructure members configuration*/
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;       
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;    
    
    /*!< Usart1 TX pin configuration */
    GPIO_InitStructure.GPIO_Pin   = DEV_CONSOLE_TX_PIN;	 
    GPIO_Init(DEV_CONSOLE_TX_PORT, &GPIO_InitStructure);	
                                                
    /*!< Usart1 RX pin configuration */
    GPIO_InitStructure.GPIO_Pin = DEV_CONSOLE_RX_PIN;	
    GPIO_Init(DEV_CONSOLE_RX_PORT, &GPIO_InitStructure);		

    /*!< Connect Usart1 to AF7 */
    GPIO_PinAFConfig(DEV_CONSOLE_TX_PORT, DEV_CONSOLE_TX_PinSource, GPIO_AF_USART1); 
    GPIO_PinAFConfig(DEV_CONSOLE_RX_PORT, DEV_CONSOLE_RX_PinSource, GPIO_AF_USART1);
}

static void dev_console_nvic_init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;	
    
    /*!< interrupt priority divide into groups */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

    /*!< NVIC_InitStructure members configuration */
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;     /**< Enable Usart1 interrupt Channel*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;               /**< PreemptionPriority 3*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;               /**< SubPriority 1*/
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;          /**< Enable interrupt*/
    NVIC_Init(&NVIC_InitStructure); 
}

static void dev_console_uart_init(uint32_t baud)
{
    USART_InitTypeDef USART_InitStructure;
    
    /*!< Enable the Usart1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

    /*!< USART_InitStructure members configuration*/
    USART_InitStructure.USART_BaudRate 	          = baud;                       /**< Setup by the user*/
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            /**< Data length 8 bits*/
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;               /**< 1 stop bit*/
    USART_InitStructure.USART_Parity              = USART_Parity_No ;               /**< No parity check*/
    USART_InitStructure.USART_Mode 	              = USART_Mode_Rx | USART_Mode_Tx;  /**< Full duplex communication*/
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /**< No hardware flow control*/
    USART_Init(USART1, &USART_InitStructure); 
    
    /*!< Enable Usart1 */
    USART_Cmd(USART1, ENABLE);	
    
    /*!< Enable the receive disrupt of Usart1 */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
}
 
/**********************
 *   SPECIAL CONFIG
 **********************/

#if 1

    #pragma import(__use_no_semihosting)
    typedef struct __FILE FILE;

    struct __FILE
    {
        int handle;
    };

    FILE __stdout;

    void _sys_exit(int x)
    {
        x = x;
    }

#endif


#if 0

    __asm (".global __use_no_semihosting\n\t");
    void _sys_exit(int x) 
    {
      x = x;
    }

    void _ttywrch(int ch)
    {
        ch = ch;
    }

    FILE __stdout;

#endif


/******************************* (END OF FILE) *********************************/
