/**
  ******************************************************************************
  *
  * @file    bsp_w25qxx.h
  * @author  GarMing
  * @brief   Header file of bsp_w25qxx module.
  *
  ******************************************************************************
  **/
  
#ifndef _BSP_W25QXX_H
#define _BSP_W25QXX_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
/*********************
 *      DEFINES
 *********************/
#define W25QXX_DEBUG    1

#define SFLASH_WIP_FLAG           0x01  /**< Write In Progress (WIP) flag*/

#define SFLASH_PAGESIZE           256  /**< Page size, unit: bytes*/

/** @defgroup w25qxx status  
  * @{
  */ 
enum {
     SFLASH_OK           = 0,   /**< Normal communication*/
     SFLASH_ERROR           ,   /**< information*/
     SFLASH_ERROR_INIT      ,   /**< Initialisation error*/
     SFLASH_ERROR_WREN      ,   /**< Write enable error*/
     SFLASH_ERROR_WAIT      ,   /**< Wait error and non-responsive*/
     SFLASH_ERROR_ERASE     ,   /**< Erase error*/
     SFLASH_ERROR_TRAN      ,   /**< Transmission error*/
     SFLASH_ERROR_MEMMAP    ,   /**< Memory mapping error*/
};
/**
  * @}
  */ 
 

/** @defgroup w25qxx command  
  * @{
  */ 
enum {
     SFLASH_CMD_PAGE_WR             = 0x02,     /**< Write to Memory instruction*/
     SFLASH_CMD_READ                = 0x03,     /**< Read from Memory instruction*/
     SFLASH_CMD_WRSR                = 0x01,     /**< Write Status Register instruction*/
     SFLASH_CMD_WREN                = 0x06,     /**< Write enable instruction*/
     SFLASH_CMD_RDSR                = 0x05,     /**< Read Status Register instruction*/
     SFLASH_CMD_RDID                = 0x9F,     /**< Read identification*/
     SFLASH_CMD_SECTOR_ERASE        = 0x20,     /**< Sector erase, 4kbytes*/
     SFLASH_CMD_BLOCK_ERASE_32K     = 0x52,     /**< Block erase, 32kbytes*/
     SFLASH_CMD_BLOCK_ERASE_64K     = 0xD8,     /**< Block erase, 64kbytes*/
     SFLASH_CMD_CHIP_ERASE          = 0xC7,     /**< Chip erase*/
     SFLASH_CMD_DUMMY               = 0xA5,     /**< Can be any value, mainly for read operations*/
};
/**
  * @}
  */ 
 

/** @defgroup Device type  
  * @{
  */ 
enum {
    SFLASH_W25Q64_ID    = 0XEF4017,          /**< W25Q64 Device ID*/
    SFLASH_W25Q128_ID   = 0XEF4018,          /**< W25Q128 Device ID*/
};
/**
  * @}
  */ 

/**********************
 *      TYPEDEFS
 **********************/

/** 
* @brief   spi interface object
*/ 
typedef struct _w25qxx_spi_interface_t {
    int8_t  (* init)                (void);
    int8_t  (* deinit)              (void);
    void    (* set_cs_high)         (void);
    void    (* set_cs_low)          (void);
    uint8_t (* send_receive_byte)   (uint8_t byte);
}w25qxx_spi_interface_t;

/** 
* @brief   w25qxx object
*/ 
typedef struct _bsp_w25qxx_t {
    w25qxx_spi_interface_t spi_interface;
    int8_t (* read_dev_id)          (struct _bsp_w25qxx_t * self, uint32_t * device_id);
    int8_t (* write_enable)         (struct _bsp_w25qxx_t * self);
    int8_t (* wait_for_write_end)   (struct _bsp_w25qxx_t * self);
    int8_t (* erase_sector)         (struct _bsp_w25qxx_t * self, uint32_t sector_addr);
    int8_t (* erase_block_32k)      (struct _bsp_w25qxx_t * self, uint32_t block_addr);
    int8_t (* erase_block_64k)      (struct _bsp_w25qxx_t * self, uint32_t block_addr);
    int8_t (* erase_chip)           (struct _bsp_w25qxx_t * self);
    int8_t (* page_program)         (struct _bsp_w25qxx_t * self, uint8_t * pbuf, uint32_t page_addr, uint8_t data_size);
    int8_t (* write_buf)            (struct _bsp_w25qxx_t * self, uint8_t * write_buf, uint32_t write_addr, uint32_t write_size);
    int8_t (* read_buf)             (struct _bsp_w25qxx_t * self, uint8_t * read_buf, uint32_t read_addr, uint32_t read_size);

#if W25QXX_DEBUG
    void   (* debug_print)          (const char *const fmt, ...);
#endif
}bsp_w25qxx_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/
int8_t bsp_w25qxx_init( bsp_w25qxx_t * self, 

#if W25QXX_DEBUG
                        void    (* pf_debug_print)             (const char *const fmt, ...),
#endif

                        int8_t  (* pf_spi_init)                (void),
                        int8_t  (* pf_spi_deinit)              (void),
                        void    (* pf_spi_set_cs_high)         (void),
                        void    (* pf_spi_set_cs_low)          (void),
                        uint8_t (* pf_spi_send_receive_byte)   (uint8_t byte) );
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_BSP_W25QXX_H*/


/******************************* (END OF FILE) *********************************/
