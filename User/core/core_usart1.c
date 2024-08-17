/**
  ******************************************************************************
  *
  * @file    core_usart1.c
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
#include "core_usart1.h"
/**********************
 *      MACROS
 **********************/
#define USART1_TX_CLK       RCC_AHB1Periph_GPIOA
#define USART1_TX_PORT      GPIOA
#define USART1_TX_PIN       GPIO_Pin_9
#define USART1_TX_PINSRC    GPIO_PinSource9

#define USART1_RX_CLK       RCC_AHB1Periph_GPIOA
#define USART1_RX_PORT      GPIOA
#define USART1_RX_PIN       GPIO_Pin_10
#define USART1_RX_PINSRC    GPIO_PinSource10    

#define	RECEIVE_BUF_SIZE	1024
/*********************
 *      DEFINES
 *********************/
typedef enum {
    USART1_BAUD_LOW     = 9600,
    USART1_BAUD_MID     = 115200,
    USART1_BAUD_HIGH    = 230400,
}Usart1ComBaud_TypeDef_E;

/**
* @brief  Usart receive info structure definition
*/
typedef struct _usart1_rec_t{
    uint8_t  buf[RECEIVE_BUF_SIZE];
    uint8_t  flg;
    uint16_t cnt;
}usart1_rec_t;

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static usart1_rec_t s_Usart1RecInfo;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
int8_t core_usart1_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    
    /*!< Enable the Usart1 GPIO clock */
    RCC_AHB1PeriphClockCmd(USART1_TX_CLK | USART1_RX_CLK, ENABLE); 
    
    /*!< Enable the Usart1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  
    
    
    /*!< GPIO_InitStructure members configuration*/
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;       
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;    
    
    /*!< Usart1 TX pin configuration */
    GPIO_InitStructure.GPIO_Pin   = USART1_TX_PIN;	 
    GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);	
                                                
    /*!< Usart1 RX pin configuration */
    GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;	
    GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);		

    /*!< Connect Usart1 to AF7 */
    GPIO_PinAFConfig(USART1_TX_PORT, USART1_TX_PINSRC, GPIO_AF_USART1); 
    GPIO_PinAFConfig(USART1_RX_PORT, USART1_RX_PINSRC, GPIO_AF_USART1);
    
    
    /*!< USART_InitStructure members configuration*/
    USART_InitStructure.USART_BaudRate 	          = USART1_BAUD_HIGH;               /**< Setup by the user*/
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            /**< Data length 8 bits*/
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;               /**< 1 stop bit*/
    USART_InitStructure.USART_Parity              = USART_Parity_No ;               /**< No parity check*/
    USART_InitStructure.USART_Mode 	              = USART_Mode_Rx | USART_Mode_Tx;  /**< Full duplex communication*/
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /**< No hardware flow control*/
    USART_Init(USART1, &USART_InitStructure); 
    
    /*!< Enable Usart1 */
    USART_Cmd(USART1, ENABLE);	
    

    /*!< interrupt priority divide into groups */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

    /*!< NVIC_InitStructure members configuration */
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;     /**< Enable Usart1 interrupt Channel*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;               /**< PreemptionPriority 3*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;               /**< SubPriority 1*/
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;          /**< Enable interrupt*/
    NVIC_Init(&NVIC_InitStructure); 
    
    /*!< Enable the receive disrupt of Usart1 */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
    
    return 0;
}

int8_t core_usart1_deinit(void)
{
    /*!< Disable the Usart1 GPIO clock */
    RCC_AHB1PeriphClockCmd(USART1_TX_CLK | USART1_RX_CLK, DISABLE); 
    
    /*!< Disable the Usart1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);  
    
    return 0;
}

void core_usart1_receive_proc(void)
{
    static uint16_t i; 

    /*!< Data Receiving Buffer */
    s_Usart1RecInfo.buf[i] = USART_ReceiveData(USART1);	
    
    /*!< Whether there is a frame of data */
    if((s_Usart1RecInfo.buf[i] == 0x0A) && (s_Usart1RecInfo.buf[i - 1] == 0x0D)) {
        s_Usart1RecInfo.flg = 1;	    /**< Received a frame of data*/
        s_Usart1RecInfo.cnt = i;       /**< Count the frame data size*/
        i = 0;                              /**< Buffer refresh*/
    }
    else {			
        i++;		                        /**< Buffer increase*/
    }
    
    /*!< Out of buffer and refresh */
    if(i > RECEIVE_BUF_SIZE) i = 0;
}

void core_usart1_receive_cb(void)
{
    /*!< Data reception completed */
    if(s_Usart1RecInfo.flg) {
		
        printf("[ %s ]:  ", __func__);
        /*!< Send the received data */
        for(uint16_t i = 0; i <= s_Usart1RecInfo.cnt; i++) {
            
            /*!< Send single byte */
            USART_SendData(USART1, s_Usart1RecInfo.buf[i]);  
            
            /*!< Waiting for sending to complete */
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);			
        }		
        
        /*!< Completion of sending */
        s_Usart1RecInfo.flg = 0;
    }
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
    
    
/**********************
 *   STATIC FUNCTIONS
 **********************/


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


/******************************* (END OF FILE) *********************************/

