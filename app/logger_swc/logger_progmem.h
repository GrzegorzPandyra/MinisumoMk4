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
        PGM_MDRV_INIT,
        PGM_I2C_INIT,
        PGM_LSD_INIT,
        PGM_DSD_INIT,
        PGM_UIDRV_INIT,
        PGM_ADC_INIT,
        PGM_TIMER_INIT,
        PGM_CSD_INIT,
        PGM_BEH_INIT,
        PGM_UI_INIT,
        PGM_OS_INIT,
        PGM_INFO,
        PGM_WARNING,
        PGM_ERROR,
        PGM_DATA,
        PGM_OVFL_ERROR,
        PGM_MDRV_DIAG_FORWARD,
        PGM_MDRV_DIAG_BACKWARD,
        PGM_MDRV_DIAG_TURN_RIGHT,
        PGM_MDRV_DIAG_TURN_LEFT,
        PGM_MDRV_DIAG_PWM20,
        PGM_MDRV_DIAG_PWM40,
        PGM_MDRV_DIAG_PWM60,
        PGM_MDRV_DIAG_PWM80,
        PGM_MDRV_DIAG_PWM100,
        PGM_MDRV_DIAG_STOP,
        PGM_SM_INIT,
        PGM_SM_STATE_IDLE,
        PGM_SM_STATE_ARMED,
        PGM_SM_STATE_ATTACK,
        PGM_SM_STATE_LINE_DETECTED,
        PGM_SM_STATE_LINE_CLEARED,
        PGM_SM_STATE_SEARCH,
        PGM_SM_STATE_INVALID,
        PGM_BEH_LD_MODE_STRICT,
        PGM_BEH_LD_MODE_CAREFUL,
        PGM_IRDRV_INIT
    } Progmem_Table_Index_T;

    /* Global variables */
    extern Small_Buffer_T flash_to_ram_buffer;
    extern const char* const PGM_DATA_LIST[];

#endif /* LOGGER_PROGMEM_GUARD */
