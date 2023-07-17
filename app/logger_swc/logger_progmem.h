#ifndef LOGGER_PROGMEM_GUARD
#define LOGGER_PROGMEM_GUARD
    /*! @file logger_progmem.h
        @brief Declarations needed to access PROGMEM data in flash
    */
    #include <avr/pgmspace.h>
    #include "logger_cfg.h"
    #include "buffer.h"
    
    #define copy_to_ram_data(id) strcpy_P( \
                                            flash_to_ram_buffer.data, \
                                            (const char*)pgm_read_word(&PGM_DATA_LIST[(uint8_t)(id)]) \
                                         )
    #define copy_to_ram_data_length(id) flash_to_ram_buffer.data_length = \
                                        strlen_P( \
                                                    (const char*)pgm_read_word(&PGM_DATA_LIST[(uint8_t)(id)]) \
                                                ) 
    #define copy_to_ram(id) copy_to_ram_data(id); \
                            copy_to_ram_data_length(id)
                            

    /** Indexes related to strings stored in PROGMEM_MESSAGE_LIST */                                                                                            
    typedef enum Progmem_Table_Index_Tag{
        PGM_ECU_INIT = 0,
        PGM_MDRV_INIT,
        PGM_I2C_INIT,
        PGM_LSD_INIT,
        PGM_DSD_INIT,
        PGM_ADC_INIT,
        PGM_TIMER_INIT,
        PGM_CSD_INIT,
        PGM_LM_INIT,
        PGM_UIM_INIT,
        PGM_OS_INIT,
        PGM_INFO,
        PGM_WARNING,
        PGM_ERROR,
        PGM_DATA,
        PGM_OVFL_ERROR
    } Progmem_Table_Index_T;

    /* Global variables */
    extern Small_Buffer_T flash_to_ram_buffer;
    extern const char* const PGM_DATA_LIST[];

#endif /* LOGGER_PROGMEM_GUARD */
