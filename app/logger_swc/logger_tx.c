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
#define MAX_UART_DATA_LENGTH 100
#define MSG_SRC_LENGTH       8
#define MSG_TYPE_LENGTH      8
#define MSG_TYPES_NUM        4
#define DECIMAL              10
#define UINT32_MAX_DIGITS    10
#define OMIT_SLASH 1

#define NULL_CHAR '\0'
#define SLASH_CHAR '/'
#define NEWLINE_CHAR '\n'
#define SPACE_CHAR ' '
#define COLON_CHAR ':'

/* Local static variables */
Large_Buffer_T buffer(logger_tx_buffer); 

/* Local static functions */
static void get_filename_from_path(char *filename, const char *path);
static void logger_serialize(const Log_T metadata, Medium_Buffer_T *serialized_msg);

/**
 * @brief Parses path, looking for last '/' character, then treats the rest as filename. 
 * Function tracks filename length and keeps it at max value MSG_SRC_LENGTH
 * @param filename output buffer for filename
 * @param path     path to be parsed (from __FILE__ attribute)
 */
static void get_filename_from_path(char *filename, const char *path){
    const char *last_slash_ptr = path;
    uint8_t filename_length = 0;
    while(*path != NULL_CHAR){
        if(*path == SLASH_CHAR){
            last_slash_ptr = path;
            filename_length = 0;
        } else {
            filename_length++;
        }
        path++;
    }
    if(filename_length > MSG_SRC_LENGTH){
        filename_length = MSG_SRC_LENGTH;
    }
    memcpy(filename, last_slash_ptr+OMIT_SLASH, filename_length);
}

static void logger_serialize(const Log_T log, Medium_Buffer_T *serialized_msg){

    /* Filename */
    get_filename_from_path((*serialized_msg).data, log.filename);
    (*serialized_msg).data_length += MSG_SRC_LENGTH;
    push(*serialized_msg, COLON_CHAR);

    /* Line number */
    itoa(log.line_num, (*serialized_msg).data + (*serialized_msg).data_length, DECIMAL);
    (*serialized_msg).data_length += DECIMAL;
    push(*serialized_msg, SPACE_CHAR);

    /* Log type */
    copy_to_ram(log.log_type);
    memcpy((*serialized_msg).data + (*serialized_msg).data_length, (const void *) flash_to_ram_buffer.data, flash_to_ram_buffer.data_length);
    (*serialized_msg).data_length += flash_to_ram_buffer.data_length;
    clear(flash_to_ram_buffer);
    push(*serialized_msg, SPACE_CHAR);

    /* Payload */
    if(log.msg_id == IRRELEVANT_ID){

    } else {
        copy_to_ram(log.msg_id);
        memcpy((*serialized_msg).data + (*serialized_msg).data_length, (const void *) flash_to_ram_buffer.data, flash_to_ram_buffer.data_length);
        (*serialized_msg).data_length += flash_to_ram_buffer.data_length;
        clear(flash_to_ram_buffer);
    }

    /* Wrap-up */
    if(log.log_type != PGM_DATA){
        push(*serialized_msg, NEWLINE_CHAR);
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
    Medium_Buffer_T buffer(serialized_message);
    logger_serialize(log, &serialized_message);
    for(uint16_t i=0U; i<serialized_message.data_length; i++){
        #if BUFFERING_ENABLED
            push(logger_tx_buffer, serialized_message.data[i]);
        #else
            Uart_Write(serialized_message.data[i]);
        #endif
    }
}

void logger_transmit(void){
    #if BUFFERING_ENABLED
        for(uint16_t i=0U; i<logger_tx_buffer.data_length; i++){
            Uart_Write(logger_tx_buffer.data[i]);
        }
        clear(logger_tx_buffer);
    #endif
}

/**
 * @brief Print only the string provided in @str (no metadata)
 */
void logger_log_raw_string(const char *str){
}
