/**
  ******************************************************************************
  *
  * @file    bsp_w25qxx.c
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
#include "bsp_w25qxx.h"
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
#if W25QXX_DEBUG

static void _bsp_w25qxx_log_add( bsp_w25qxx_t * self, 
                                 const char * file, 
                                 int line, 
                                 const char * func, 
                                 const char * format, 
                                 ... );

#define LOG(self, ...) _bsp_w25qxx_log_add(self, __FILE__, __LINE__, __func__, __VA_ARGS__)

#else 

#define LOG(self, ...)

#endif
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

/**
  * @brief  Read device id
  * @param  self: object
  * @param  device_id: get the id value
  * @retval 0
  */
int8_t bsp_w25qxx_read_device_id(bsp_w25qxx_t * self, uint32_t * device_id)
{
	uint32_t deviceID = 0;
	uint32_t tmp0 = 0;
	uint32_t tmp1 = 0;
	uint32_t tmp2 = 0;
	
    /*!< Enable selected Chip */
	self->spi_interface.set_cs_low();
    
    /*!< Send the command of Read ID */
	self->spi_interface.send_receive_byte(SFLASH_CMD_RDID);
    
    /*!< Receive device ID infomation */
	tmp0 = self->spi_interface.send_receive_byte(SFLASH_CMD_DUMMY);   /**< The first byte of ID*/
	tmp1 = self->spi_interface.send_receive_byte(SFLASH_CMD_DUMMY);   /**< The second byte of ID*/
	tmp2 = self->spi_interface.send_receive_byte(SFLASH_CMD_DUMMY);   /**< The third byte of ID*/
    
    /*!< Disable selected Chip */
	self->spi_interface.set_cs_high();
	
	deviceID = (tmp0 << 16) | (tmp1 << 8) | tmp2;
    LOG(self, "deviceID = 0x%x", deviceID);
	
	*device_id =  deviceID;

    return 0;
}

/**
  * @brief  Enable write
  * @param  self: object
  * @retval 0
  */
int8_t bsp_w25qxx_write_enable(bsp_w25qxx_t * self)
{
    /*!< Enable selected Chip */
	self->spi_interface.set_cs_low();
    
    /*!< Send the command of write enable */
	self->spi_interface.send_receive_byte(SFLASH_CMD_WREN);
    
    /*!< Disable selected Chip */
	self->spi_interface.set_cs_high();

    return 0;
}

/**
  * @brief  Wait for write finish
  * @param  self: object
  * @retval 0
  */
int8_t bsp_w25qxx_wait_for_write_end(bsp_w25qxx_t * self)
{
    uint8_t flg = 0;

    /*!< Enable selected Chip */
    self->spi_interface.set_cs_low();

    /*!< Waiting for the writing to complete */
    self->spi_interface.send_receive_byte(SFLASH_CMD_RDSR);
    do {
        flg = self->spi_interface.send_receive_byte(SFLASH_CMD_DUMMY);
    } while ((flg & SFLASH_WIP_FLAG) == 1);

    /*!< Disable selected Chip */
    self->spi_interface.set_cs_high();

    return 0;
}

/**
  * @brief  Erase sectors
  * @param  self: object
  * @param  sector_addr: sector address
  * @retval 0
  */
int8_t bsp_w25qxx_erase_sector(bsp_w25qxx_t * self, uint32_t sector_addr)
{
    /*!< Enable write */
    bsp_w25qxx_write_enable(self);
    
    /*!< Enable selected Chip */
    self->spi_interface.set_cs_low();
    
    /*!< Send the command of erase sector */
    self->spi_interface.send_receive_byte(SFLASH_CMD_SECTOR_ERASE);
    
    /*!< Send the high 8-bit address of sector */
    self->spi_interface.send_receive_byte((sector_addr & 0xFF0000) >> 16);
    
    /*!< Send the middle 8-bit address of sector */
    self->spi_interface.send_receive_byte((sector_addr & 0xFF00) >> 8);
    
    /*!< Send the low 8-bit address of sector */
    self->spi_interface.send_receive_byte((sector_addr & 0xFF));
    
    /*!< Disable selected Chip */
    self->spi_interface.set_cs_high();
    
    /*!< Wait for the device internal write operation to complete */
    bsp_w25qxx_wait_for_write_end(self);

    return 0;
}

/**
  * @brief  Erase 32k block
  * @param  self: object
  * @param  block_addr: block address
  * @retval 0
  */
int8_t bsp_w25qxx_erase_block_32k(bsp_w25qxx_t * self, uint32_t block_addr)
{
    /*!< Enable write */
    bsp_w25qxx_write_enable(self);
    
    /*!< Enable selected Chip */
    self->spi_interface.set_cs_low();
    
    /*!< Send the command of erase 32kb block */
    self->spi_interface.send_receive_byte(SFLASH_CMD_BLOCK_ERASE_32K);
    
    /*!< Send the high 8-bit address of block */
    self->spi_interface.send_receive_byte((block_addr & 0xFF0000) >> 16);
    
    /*!< Send the middle 8-bit address of block */
    self->spi_interface.send_receive_byte((block_addr & 0xFF00) >> 8);
    
    /*!< Send the low 8-bit address of block */
    self->spi_interface.send_receive_byte((block_addr & 0xFF));
    
    /*!< Disable selected Chip */
    self->spi_interface.set_cs_high();
    
    /*!< Wait for the device internal write operation to complete */
    bsp_w25qxx_wait_for_write_end(self);

    return 0;
}

/**
  * @brief  Erase 64k block
  * @param  self: object
  * @param  block_addr: block address
  * @retval 0
  */
int8_t bsp_w25qxx_erase_block_64k(bsp_w25qxx_t * self, uint32_t block_addr)
{
    /*!< Enable write */
    bsp_w25qxx_write_enable(self);
    
    /*!< Enable selected Chip */
    self->spi_interface.set_cs_low();
    
    /*!< Send the command of erase 64kb block */
    self->spi_interface.send_receive_byte(SFLASH_CMD_BLOCK_ERASE_64K);
    
    /*!< Send the high 8-bit address of block */
    self->spi_interface.send_receive_byte((block_addr & 0xFF0000) >> 16);
    
    /*!< Send the middle 8-bit address of block */
    self->spi_interface.send_receive_byte((block_addr & 0xFF00) >> 8);
    
    /*!< Send the low 8-bit address of block */
    self->spi_interface.send_receive_byte((block_addr & 0xFF));
    
    /*!< Disable selected Chip */
    self->spi_interface.set_cs_high();
    
    /*!< Wait for the device internal write operation to complete */
    bsp_w25qxx_wait_for_write_end(self);   
    
    return 0;
}

/**
  * @brief  Erase whole chip
  * @param  self: object
  * @retval 0
  */
int8_t bsp_w25qxx_erase_chip(bsp_w25qxx_t * self)
{
    /*!< Enable write */
    bsp_w25qxx_write_enable(self);
    
    /*!< Enable selected Chip */
    self->spi_interface.set_cs_low();
    
    /*!< Send the command of erase chip */
    self->spi_interface.send_receive_byte(SFLASH_CMD_CHIP_ERASE);
    
    /*!< Disable selected Chip */
    self->spi_interface.set_cs_high();
    
    /*!< Wait for the device internal write operation to complete */
    bsp_w25qxx_wait_for_write_end(self);

    return 0;
}

/**
  * @brief  Write a page
  * @param  self: object
  * @param  buf_ptr: buffer
  * @param  page_addr：page address
  * @param  data_size: buffer length
  * @retval 0
  */
int8_t bsp_w25qxx_page_program( bsp_w25qxx_t * self, 
                                uint8_t * buf_ptr, 
                                uint32_t page_addr, 
                                uint8_t data_size )
{
    /*!< Enable write */
    bsp_w25qxx_write_enable(self);
    
    /*!< Enable selected Chip */
    self->spi_interface.set_cs_low();
    
    /*!< Send the command of write */
    self->spi_interface.send_receive_byte(SFLASH_CMD_PAGE_WR);
    
    /*!< Send the high 8-bit address of page */
    self->spi_interface.send_receive_byte((page_addr & 0xFF0000) >> 16);
    
    /*!< Send the middle 8-bit address of page */
    self->spi_interface.send_receive_byte((page_addr & 0xFF00) >> 8);
    
    /*!< Send the low 8-bit address of page */
    self->spi_interface.send_receive_byte((page_addr & 0xFF));
    
    /*!< Loop Send the data of write */
    while(data_size--) {
        self->spi_interface.send_receive_byte(*buf_ptr);
        buf_ptr++;
    }
    
    /*!< Disable selected Chip */
    self->spi_interface.set_cs_high();
    
    /*!< Wait for the device internal write operation to complete */
    bsp_w25qxx_wait_for_write_end(self);

    return 0;
}

/**
  * @brief  Write buffer
  * @param  self: object
  * @param  write_buf: a buffer to write
  * @param  write_addr: write address
  * @param  write_size: write length
  * @retval 0
  */
int8_t bsp_w25qxx_write_buf( bsp_w25qxx_t * self, 
                             uint8_t * write_buf, 
                             uint32_t write_addr, 
                             uint32_t write_size )
{
    uint32_t end_addr = 0;
    uint32_t current_addr = 0;
    uint32_t current_size = 0;
    
    /*!< c the size of page program */
    current_size = SFLASH_PAGESIZE - (write_addr % SFLASH_PAGESIZE);
    if(current_size > write_size) current_size = write_size;

    /*!< Get the start address and the end address of page program */
    current_addr = write_addr;
    end_addr = write_addr + write_size;

    /*!< Loop Page Programming */
    do {
        bsp_w25qxx_page_program(self, write_buf, current_addr, current_size);
        
        /*!< Calculate the device address next time to write  */
        current_addr += current_size;
        
        /*!< Calculate the data buf address next time to write  */
        write_buf += current_size;
        
        /*!< Calculate the remaining size to be programmed */
        current_size = ((current_addr + SFLASH_PAGESIZE) > end_addr) ? (end_addr - current_addr) : SFLASH_PAGESIZE;
    }while(current_addr < end_addr);

    return 0;
}

/**
  * @brief  Store the read data in the buffer 
  * @param  self: object
  * @param  read_buf: store buffer
  * @param  read_addr: read address
  * @param  read_size: read length
  * @retval 0
  */
int8_t bsp_w25qxx_read_buf( bsp_w25qxx_t * self, 
                            uint8_t * read_buf, 
                            uint32_t read_addr, 
                            uint32_t read_size )
{
    /*!< Enable selected Chip */
    bsp_w25qxx_write_enable(self);
    
    /*!< Send the command of read */
    self->spi_interface.send_receive_byte(SFLASH_CMD_READ);
    
    /*!< Send the high 8-bit address of read */
    self->spi_interface.send_receive_byte((read_addr & 0xFF0000) >> 16);
    
    /*!< Send the middle 8-bit address of read */
    self->spi_interface.send_receive_byte((read_addr & 0xFF00) >> 8);
    
    /*!< Send the low 8-bit address of read */
    self->spi_interface.send_receive_byte((read_addr & 0xFF));
    
    /*!< Loop Read the data */
    while(read_size--) {
        *read_buf = self->spi_interface.send_receive_byte(SFLASH_CMD_DUMMY);
        read_buf++;
    }
    
    /*!< Disable selected Chip */
    self->spi_interface.set_cs_high();

    return 0;
}


int8_t bsp_w25qxx_init( bsp_w25qxx_t * self, 

#if W25QXX_DEBUG
                        void    (* pf_debug_print)             (const char *const fmt, ...),
#endif

                        int8_t  (* pf_spi_init)                (void),
                        int8_t  (* pf_spi_deinit)              (void),
                        void    (* pf_spi_set_cs_high)         (void),
                        void    (* pf_spi_set_cs_low)          (void),
                        uint8_t (* pf_spi_send_receive_byte)   (uint8_t byte))
{   
    memset(self, 0, sizeof(bsp_w25qxx_t));

    self->spi_interface.init                = pf_spi_init;
    self->spi_interface.deinit              = pf_spi_deinit;
    self->spi_interface.set_cs_high         = pf_spi_set_cs_high;
    self->spi_interface.set_cs_low          = pf_spi_set_cs_low;
    self->spi_interface.send_receive_byte   = pf_spi_send_receive_byte;


    if( (self->spi_interface.init               == NULL) ||
        (self->spi_interface.deinit             == NULL) ||
        (self->spi_interface.set_cs_high        == NULL) ||
        (self->spi_interface.set_cs_low         == NULL) ||
        (self->spi_interface.send_receive_byte  == NULL) )
    {
        return -1;
    }

#if W25QXX_DEBUG

    self->debug_print = pf_debug_print;

    if(self->debug_print == NULL) {
        return -3;
    }

#endif

    if(0 != self->spi_interface.init()) {
        LOG(self, "Init Fail!");
        return -2;
    }

    self->read_dev_id           = bsp_w25qxx_read_device_id;
    self->write_enable          = bsp_w25qxx_write_enable;
    self->wait_for_write_end    = bsp_w25qxx_wait_for_write_end;
    self->erase_sector          = bsp_w25qxx_erase_sector;
    self->erase_block_32k       = bsp_w25qxx_erase_block_32k;
    self->erase_block_64k       = bsp_w25qxx_erase_block_64k;
    self->erase_chip            = bsp_w25qxx_erase_chip;
    self->page_program          = bsp_w25qxx_page_program;
    self->write_buf             = bsp_w25qxx_write_buf;
    self->read_buf              = bsp_w25qxx_read_buf;

    LOG(self, "Finished!");

    return 0;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
#if W25QXX_DEBUG
static void _bsp_w25qxx_log_add( bsp_w25qxx_t * self, 
                                 const char * file, 
                                 int line, 
                                 const char * func, 
                                 const char * format, 
                                 ... )
{
    char str[512] = {0};
    char * ptr = &str[0];
    
    va_list args;
    va_start(args, format); 
    
    /*Use only the file name not the path*/
    size_t p;
    for(p = strlen(file); p > 0; p--) {
        if(file[p] == '/' || file[p] == '\\') {
            p++;    /*Skip the slash*/
            break;
        }
    }

    self->debug_print("[%s]\t %s: ", "W25QXX", func);
    
    vsnprintf(str, 255, format, args);
    va_end(args);

    self->debug_print("%s", ptr);
    
    self->debug_print(" \t(in %s line #%d)\n", &file[p], line);
}
#endif


/******************************* (END OF FILE) *********************************/
