#ifndef UART_TX_GUARD
#define UART_TX_GUARD

/*! @file UART_TX.h
    @brief API for serial communication
    Interface file for other components to access serial communication between MCU and PC. 
*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <logger_progmem.h>

#define IRRELEVANT_ID 0xFFU

/**
 * @brief Structure describing the log
 */
typedef struct Log_Tag{
    const char *filename;
    const uint32_t line_num;
    const Progmem_Table_Index_T log_type;
    const Progmem_Table_Index_T msg_id;
    const char *msg_str;
} Log_T;

/** Logging API */
#define pack_log(type, msg_id, msg_str)  (Log_T){__FILE__, __LINE__, type, msg_id, msg_str}

#define log_info(str)   logger_log(pack_log(PGM_INFO, IRRELEVANT_ID, str))
#define log_info_P(id)  logger_log(pack_log(PGM_INFO, id           , NULL))
                          
// #define log_warn(str)   (logger_log( get_metadata(WARNING), str ))
// #define log_warn_P(id)  copy_to_ram(id); 
//                         logger_log(get_metadata(WARNING), flash_to_ram_buffer.data)
// #define log_err(str)    (logger_log( get_metadata(ERROR), str ))
// #define log_err_P(id)   copy_to_ram(id); 
//                         logger_log(get_metadata(ERROR), flash_to_ram_buffer.data)

// #define log_raw_string(str) logger_log_raw_string(str)

// #define log_data_1(format, arg1)                                            sprintf(flash_to_ram_buffer.data, format, arg1);
//                                                                             logger_log(get_metadata(INFO), flash_to_ram_buffer.data)
// #define log_data_2(format, arg1, arg2)                                      sprintf(flash_to_ram_buffer.data, format, arg1, arg2);
//                                                                             logger_log(get_metadata(INFO), flash_to_ram_buffer.data)
// #define log_data_3(format, arg1,arg2, arg3)                                 sprintf(flash_to_ram_buffer.data, format, arg1, arg2, arg3);
//                                                                             logger_log(get_metadata(INFO), flash_to_ram_buffer.data)
// #define log_data_4(format, arg1, arg2, arg3, arg4)                          sprintf(flash_to_ram_buffer.data, format, arg1, arg2, arg3, arg4);
//                                                                             logger_log(get_metadata(INFO), flash_to_ram_buffer.data)
// #define log_data_5(format, arg1, arg2, arg3, arg4, arg5)                    sprintf(flash_to_ram_buffer.data, format, arg1, arg2, arg3, arg4, arg5);
//                                                                             logger_log(get_metadata(INFO), flash_to_ram_buffer.data)
// #define log_data_6(format, arg1, arg2, arg3, arg4, arg5, arg6)              sprintf(flash_to_ram_buffer.data, format, arg1, arg2, arg3, arg4, arg5, arg6);
//                                                                             logger_log(get_metadata(INFO), flash_to_ram_buffer.data)
// #define log_data_7(format, arg1, arg2, arg3, arg4, arg5, arg6, arg7)        sprintf(flash_to_ram_buffer.data, format, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
//                                                                             logger_log(get_metadata(INFO), flash_to_ram_buffer.data)
// #define log_data_8(format, arg1, arg2, arg3, arg4, arg5,arg6, arg7, arg8)   sprintf(flash_to_ram_buffer.data, format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
//                                                                             logger_log(get_metadata(INFO), flash_to_ram_buffer.data)                                                                           
                                   
void logger_log(const Log_T log);
void logger_log_raw_string(const char *str);
void logger_transmit(void);
#endif /* UART_TX_GUARD */
