/**
  ******************************************************************************
  *
  * @file    log.h
  * @author  GarMing
  * @brief   Header file of LOG module.
  *
  ******************************************************************************
  **/
  
#ifndef _LOG_H
#define _LOG_H

/*********************
 *      DEFINES
 *********************/
#define USE_DEBUG_LOG 1

 
#if USE_DEBUG_LOG
/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**********************
 *      TYPEDEFS
 **********************/
 
/**
* @brief  Log level type definition
*/
 typedef enum {
	 LOG_LEVEL_TRACE = 0,	/**< A lot of logs to give detailed information*/
	 LOG_LEVEL_INFO     ,	/**< Log important events*/
	 LOG_LEVEL_WARN     ,	/**< Log if something unwanted happened but didn't caused problem*/
	 LOG_LEVEL_ERROR    ,	/**< Only critical issue, when the system may fail*/
	 LOG_LEVEL_USER     ,	/**< Custom logs from the user*/
	 LOG_LEVEL_NONE     ,	/**< Do not log anything*/
} LOG_LEVEL_TYPE_E;
 
#define LOG_LEVEL LOG_LEVEL_TRACE

/**********************
* GLOBAL PROTOTYPES
**********************/

/**
* @brief  Add a log
*/
void _log_generate_info(int level, 
						const char * file, 
						int line, 
						const char * func, 
						const char * format, 
						...);

/**********************
 *      MACROS
 **********************/
#ifndef LOG_TRACE
#	if LOG_LEVEL <= LOG_LEVEL_TRACE
#		define LOG_TRACE(...) _log_generate_info(LOG_LEVEL_TRACE, __FILE__, __LINE__, __func__, __VA_ARGS__)
#	else
#		define LOG_TRACE(...)
#	endif
#endif

#ifndef LOG_INFO
#	if LOG_LEVEL <= LOG_LEVEL_INFO
#		define LOG_INFO(...) _log_generate_info(LOG_LEVEL_INFO, __FILE__, __LINE__, __func__, __VA_ARGS__)
#	else
#		define LOG_INFO(...)
#	endif
#endif

#ifndef LOG_WARN
#	if LOG_LEVEL <= LOG_LEVEL_WARN
#		define LOG_WARN(...) _log_generate_info(LOG_LEVEL_WARN, __FILE__, __LINE__, __func__, __VA_ARGS__)
#	else
#		define LOG_WARN(...)
#	endif
#endif

#ifndef LOG_ERROR
#	if LOG_LEVEL <= LOG_LEVEL_ERROR
#		define LOG_ERROR(...) _log_generate_info(LOG_LEVEL_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)
#	else
#		define LOG_ERROR(...)
#	endif
#endif

#ifndef LOG_USER
#	if LOG_LEVEL <= LOG_LEVEL_USER
#		define LOG_USER(...) _log_generate_info(LOG_LEVEL_USER, __FILE__, __LINE__, __func__, __VA_ARGS__)
#	else
#		define LOG_USER(...)
#	endif
#endif

#else /*USE_DEBUG_LOG*/

/**
* @brief  Do nothing if `USE_DEBUG_LOG 0`
*/
#define LOG_TRACE(format, ...)
#define LOG_INFO(format, ... )
#define LOG_WARN(format, ... )
#define LOG_ERROR(format, ...)
#define LOG_USER(format, ... )


#endif /*USE_DEBUG_LOG*/





#endif /*_LOG_H*/

/******************************* (END OF FILE) *********************************/
