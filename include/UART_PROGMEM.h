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
    } Progmem_Table_Index_T;

    /* Global variables */
    extern char data_conversion_buffer[];
    extern const char* const progmem_string_table[];

#endif /* UART_PROGMEM_GUARD */
