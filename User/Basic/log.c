/**
  ******************************************************************************
  *
  * @file    log.c
  * @author  GarMing
  * @brief   This file provides debug log functions to output logs with
  *           detailed information:
  *			  + LOG add content 
  *
  @verbatim
  ==============================================================================
                        ##### How to use #####
  ==============================================================================
    [..]
    To make it work, you should do as follows:
    
    (#) Include the header files: log.h, for example: #include "log.h".

    (#) Enable the define "USE_DEBUG_LOG" in header files, 
        to give it a value of 1.

    (#) Set the level of log, define the "LOG_LEVEL" in header files
        (##) There are six levels of log you can set. 
             LOG_LEVEL_TRACE is the lowest, LOG_LEVEL_NONE is the highest level. 
             (+++) LOG_LEVEL_TRACE all levels of log are valid
             (+++) LOG_LEVEL_USER  just the LOG_USER can be used
             (+++) LOG_LEVEL_NONE  all levels of log are invalid

    (#) Use the macro in log.h, for example: LOG_USER(""),
        (##) You can put the content what you need to output inside 
             double quotes, just like "printf".

     *** log macros list ***
     ==================================
     [..]
       Below the list of the macros you can use.
     
       (+) @ref LOG_TRACE
       (+) @ref LOG_INFO
       (+) @ref LOG_WARN
       (+) @ref LOG_ERROR
       (+) @ref LOG_USER

  @endverbatim
  
  ******************************************************************************
  * @attention
  *
  * Version: 00.00.00.01
  *
  * If the project does not support "printf", look for an alternative.
  *
  * If your compiler is ac5, you may use:
        ===================================
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
        ===================================
  *
  * If your compiler is ac6, you may use:
        ===================================
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
        ===================================
  *
  ******************************************************************************
  **/
  
  
/*********************
 *      INCLUDES
 *********************/
#include <stdarg.h>
#include "log.h" 
#if USE_DEBUG_LOG 
 
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
 
/**
  * @brief  Add a log
  * @param  level: the level of log. (From `LOG_LEVEL_TYPE_E` enum)
  * @param  file: name of the file when the log added
  * @param  line: line number in the source code where the log added
  * @param  func: name of the function when the log added
  * @param  format: printf-like format string
  * @param  ...: parameters for `format`
  * @retval NULL
  */
void _log_generate_info(int level, 
						const char * file, 
						int line, 
						const char * func, 
						const char * format, 
						...)
{
	static const char * l_prefix[] = {"Trace", "Info", "Warn", "Error", "User"};
	
	if(level >= LOG_LEVEL) {
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

		printf("[%s]\t %s: ", l_prefix[level], func);	
		vprintf(format, args);
		printf(" \t(in %s line #%d)\n", &file[p], line);
		
		
		va_end(args);
	}
}




/**********************
 *   STATIC FUNCTIONS
 **********************/


#endif /*USE_DEBUG_LOG*/

/******************************* (END OF FILE) *********************************/


