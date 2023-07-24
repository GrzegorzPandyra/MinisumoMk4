#ifndef LOGGER_TX_GUARD
#define LOGGER_TX_GUARD

/*! @file logger_tx.h
    @brief API for logging data
    Interface file for other components to access communication between MCU and PC. 
*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <logger_progmem.h>

#define ID_NONE 0xFFU

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

extern Medium_Buffer_T logger_data_buffer;

/** Logging API */
#define PACK_LOG(type, msg_id, msg_str)  (Log_T){__FILE__, __LINE__, type, msg_id, msg_str}

#if LOGGING_ENABLED

    #define INFO(str)   logger_log(PACK_LOG(PGM_INFO, ID_NONE, str))
    #define INFO_P(id)  logger_log(PACK_LOG(PGM_INFO, id     , NULL))

    #define WARNING(str)   logger_log(PACK_LOG(PGM_WARNING, ID_NONE, str))
    #define WARNING_P(id)  logger_log(PACK_LOG(PGM_WARNING, id     , NULL))

    #define ERROR(str)   logger_log(PACK_LOG(PGM_ERROR, ID_NONE, str))
    #define ERROR_P(id)  logger_log(PACK_LOG(PGM_ERROR, id     , NULL))                          

#define DATA1(format, arg1)                                            sprintf(logger_data_buffer.data, format, arg1); \
                                                                       logger_log(PACK_LOG(PGM_DATA, ID_NONE, logger_data_buffer.data))
#define DATA2(format, arg1, arg2)                                      sprintf(logger_data_buffer.data, format, arg1, arg2); \
                                                                       logger_log(PACK_LOG(PGM_DATA, ID_NONE, logger_data_buffer.data))
#define DATA3(format, arg1,arg2, arg3)                                 sprintf(logger_data_buffer.data, format, arg1, arg2, arg3); \
                                                                       logger_log(PACK_LOG(PGM_DATA, ID_NONE, logger_data_buffer.data))
#define DATA4(format, arg1, arg2, arg3, arg4)                          sprintf(logger_data_buffer.data, format, arg1, arg2, arg3, arg4); \
                                                                       logger_log(PACK_LOG(PGM_DATA, ID_NONE, logger_data_buffer.data))
#define DATA5(format, arg1, arg2, arg3, arg4, arg5)                    sprintf(logger_data_buffer.data, format, arg1, arg2, arg3, arg4, arg5); \
                                                                       logger_log(PACK_LOG(PGM_DATA, ID_NONE, logger_data_buffer.data))
#define DATA6(format, arg1, arg2, arg3, arg4, arg5, arg6)              sprintf(logger_data_buffer.data, format, arg1, arg2, arg3, arg4, arg5, arg6); \
                                                                       logger_log(PACK_LOG(PGM_DATA, ID_NONE, logger_data_buffer.data))
#define DATA7(format, arg1, arg2, arg3, arg4, arg5, arg6, arg7)        sprintf(logger_data_buffer.data, format, arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
                                                                       logger_log(PACK_LOG(PGM_DATA, ID_NONE, logger_data_buffer.data))
#define DATA8(format, arg1, arg2, arg3, arg4, arg5,arg6, arg7, arg8)   sprintf(logger_data_buffer.data, format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
                                                                       logger_log(PACK_LOG(PGM_DATA, ID_NONE, logger_data_buffer.data))                                                                           

#else
    #define INFO(str)   
    #define INFO_P(id)
    #define WARNING(str)
    #define WARNING_P(id)
    #define ERROR(str)
    #define ERROR_P(id)  
#endif

void logger_log(const Log_T log);
void logger_log_raw_string(const char *str);
void logger_transmit(void);
#endif /* LOGGER_TX_GUARD */
