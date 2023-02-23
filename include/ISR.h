#ifndef ISR_GUARD
#define ISR_GUARD

    /** @file ISR.h
        @brief Interrupt Service Routines
        This file needs to be included in file with "main" function. ISRs are kept separated here for the purpose of clarity.
    */

    #include "UART_TX.h"
    #include "config.h"
    #include "distance_sensor_drv.h"

    /**
     * @brief Interrupt routine executed when ADC completes conversion
     */
    ISR(ADC_vect){  
        // volatile uint16_t adc_val = ADCW;
        DSD_ConversionCallback();
    }

    /**
     * @brief
     */
    ISR(TIMER0_OVF_vect){  
    }

    #if 0
    /**
     * @brief Interrupt routine for USART receive complete bit
     * Reads a single character from UDR and calls function handle this data
     */
    ISR(USART_RXC_vect){
        char c = (char)UDR0;
        serial_on_receive(c);
    }
    #endif

    
#endif /* ISR_GUARD */
