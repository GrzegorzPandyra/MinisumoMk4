#ifndef UART_PROGMEM_GUARD
#define UART_PROGMEM_GUARD
    /*! @file serial_progmem.h
        @brief Declarations needed to access PROGMEM data in flash
    */

    /** Indexes related to strings stored in progmem_string_table */                                                                                            
    typedef enum Progmem_Table_Index_Tag{
        PROGMEM_ECU_INIT = 0,
        PROGMEM_MDRV_INIT,
        PROGMEM_I2C_INIT,
        PROGMEM_LSD_INIT,
        PROGMEM_DSD_INIT,
        PROGMEM_ADC_INIT,
        PROGMEM_TIMER_INIT,
        PROGMEM_CSD_INIT,
        PROGMEM_LM_INIT,
    } Progmem_Table_Index_T;

    /* Global variables */
    extern char data_conversion_buffer[];
    extern const char* const progmem_string_table[];

#endif /* UART_PROGMEM_GUARD */
