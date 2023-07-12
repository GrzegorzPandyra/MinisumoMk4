#ifndef LOGGER_PROGMEM_GUARD
#define LOGGER_PROGMEM_GUARD
    /*! @file logger_progmem.h
        @brief Declarations needed to access PROGMEM data in flash
    */

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
        PGM_INFO,
        PGM_WARNING,
        PGM_ERROR,
        PGM_DATA
    } Progmem_Table_Index_T;

    /* Global variables */
    extern char data_conversion_buffer[];
    extern const char* const PGM_DATA_LIST[];

#endif /* LOGGER_PROGMEM_GUARD */
