/** @file logger_tx.c
*   @brief Implementation of TX part of logger 
*/
#include "logger_tx.h"
#include "uart_drv.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "buffer.h"

/* Local macro definitions */
#define MSG_SRC_LENGTH 8
#define DECIMAL 10
#define OMIT_SLASH 1
#define ALIGNMENT_COLUMN_IDX 20u

#define NULL_CHAR '\0'
#define SLASH_CHAR '/'
#define NEWLINE_CHAR '\n'
#define SPACE_CHAR ' '
#define COLON_CHAR ':'

/* Local static variables */
#if BUFFERING_ENABLED
    Large_Buffer_T BUFFER(logger_tx_buffer); 
#endif
Medium_Buffer_T BUFFER(logger_data_buffer); 

/* Local static functions */
static void get_filename_from_path(Medium_Buffer_T *buff, const char *path);
static void logger_serialize(const Log_T metadata, Medium_Buffer_T *serialized_msg);
static void align_filename(Medium_Buffer_T *serialized_msg);
static void align_line_number(uint32_t line_num, Medium_Buffer_T *serialized_msg);
static void quick_transmit(Medium_Buffer_T buff);

/**
 * @brief Parses path, looking for last '/' character, then treats the rest as filename. 
 * Function tracks filename length and keeps it at max value MSG_SRC_LENGTH
 * @param filename output buffer for filename
 * @param path     path to be parsed (from __FILE__ attribute)
 */
static void get_filename_from_path(Medium_Buffer_T *buff, const char *path){
    const char *last_slash_ptr = path;
    uint8_t filename_length = 0U;
    while(*path != NULL_CHAR){
        if(*path == SLASH_CHAR){
            last_slash_ptr = path;
            filename_length = 0U;
        } else {
            filename_length++;
        }
        path++;
    }

    memcpy(BUFF_HEAD(*buff), last_slash_ptr+OMIT_SLASH, filename_length);
    buff->data_length += filename_length;
}

static void align_filename(Medium_Buffer_T *serialized_msg){
    char *filename_tail_ptr = BUFF_HEAD(*serialized_msg);
    if(serialized_msg->data_length < ALIGNMENT_COLUMN_IDX){
        for(uint8_t i=ALIGNMENT_COLUMN_IDX; i>=0u; i--){
            if(filename_tail_ptr >= serialized_msg->data){
                serialized_msg->data[i] = *filename_tail_ptr;
            } else {
                serialized_msg->data[i] = SPACE_CHAR;
            }

            if(i==0u){
                break;
            } else {
                filename_tail_ptr--;
            }
        }
    }
    serialized_msg->data_length = ALIGNMENT_COLUMN_IDX;
}

static void align_line_number(uint32_t line_num, Medium_Buffer_T *serialized_msg){
    uint8_t digits = 1u;
    itoa(line_num, BUFF_HEAD(*serialized_msg), DECIMAL);
    /* Check how many digits there is (1-4) */
    for(uint8_t i = 10u; line_num>i; i*=10u){
        digits++;
    }
    /* Overwrite NULL from itoa with spaces */
    serialized_msg->data_length += digits;
    for(uint8_t i = MAX_LINE_NUMBER_DIGITS-digits; i>0u; i--){
        BUFF_PUSH(*serialized_msg, SPACE_CHAR);
    }
}

static void logger_serialize(const Log_T log, Medium_Buffer_T *serialized_msg){
    /* Filename */
    get_filename_from_path(serialized_msg, log.filename);
    align_filename(serialized_msg);
    BUFF_PUSH(*serialized_msg, COLON_CHAR);

    /* Line number */
    align_line_number(log.line_num, serialized_msg);
    BUFF_PUSH(*serialized_msg, COLON_CHAR);

    /* Log type */
    copy_to_ram(log.log_type);
    memcpy(BUFF_HEAD(*serialized_msg), (const void *) flash_to_ram_buffer.data, flash_to_ram_buffer.data_length);
    (*serialized_msg).data_length += flash_to_ram_buffer.data_length;
    BUFF_CLEAR(flash_to_ram_buffer);
    BUFF_PUSH(*serialized_msg, SPACE_CHAR);

    /* Payload */
    if(log.msg_id == ID_NONE){
        memcpy(BUFF_HEAD(*serialized_msg), (const void *) log.msg_str, strlen(log.msg_str));
        (*serialized_msg).data_length += (uint16_t)strlen(log.msg_str);
    } else {
        copy_to_ram(log.msg_id);
        memcpy(BUFF_HEAD(*serialized_msg), (const void *) flash_to_ram_buffer.data, flash_to_ram_buffer.data_length);
        (*serialized_msg).data_length += flash_to_ram_buffer.data_length;
        BUFF_CLEAR(flash_to_ram_buffer);
    }

    /* Wrap-up */
    if(log.log_type != PGM_DATA){
        BUFF_PUSH(*serialized_msg, NEWLINE_CHAR);
    }
}

/**
 * @brief Immediately transmit buffer
 * @param buff 
 */
static void quick_transmit(Medium_Buffer_T buff){
    for(uint16_t i=0U; i<buff.data_length; i++){
        Uart_Write(buff.data[i]);
    }
}

/* Public functions */
/**
 * @brief Send string str via serial
 * Prints logs formatted as below:
 * main.c  :  44      INFO    Hello from ATmega8
 * <source> <line>  <log type>  <Log data (string)>
 * @param str       String to be send. Must be null-terminated
 * @param log  Struct containing file, line and type of log
 */
void logger_log(const Log_T log){
    Medium_Buffer_T BUFFER(serialized_message);
    logger_serialize(log, &serialized_message);

    #if BUFFERING_ENABLED
        /* Errors are reported immediately */
        if(log.log_type == PGM_ERROR){
            quick_transmit(serialized_message);
        } else {
            /* Check if msg will fit in buffer */
            if(BUFF_FREESPACE(logger_tx_buffer) >= serialized_message.data_length){
                for(uint16_t i=0U; i<serialized_message.data_length; i++){
                    BUFF_PUSH(logger_tx_buffer, serialized_message.data[i]);
                }
            } else {
                #if TRANSMIT_WHEN_TX_OVFL
                    logger_transmit();
                #endif
                /* Recursive call */
                ERROR_P(PGM_OVFL_ERROR);
            }

        }
    #else
        quick_transmit(serialized_message);
    #endif
}

void logger_transmit(void){
    #if BUFFERING_ENABLED
        for(uint16_t i=0U; i<logger_tx_buffer.data_length; i++){
            Uart_Write(logger_tx_buffer.data[i]);
        }
        BUFF_CLEAR(logger_tx_buffer);
    #endif
}
