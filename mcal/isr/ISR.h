#ifndef ISR_GUARD
#define ISR_GUARD

    /** @file ISR.h
        @brief Interrupt Service Routines
        This file needs to be included in file with "main" function. ISRs are kept separated here for the purpose of clarity.
    */
    #include "os.h"
    // #include "DSD_DistanceSensorDrv.h"
    #include "timer0.h"

    /**
     * @brief ISR executed when ADC completes conversion
     */
    ISR(ADC_vect){  
        // DSD_ConversionCallback();
    }

    /**
     * @brief Interrupt for Timer0 overflow
     */
    ISR(TIMER0_OVF_vect){  
    }

    /**
     * @brief ISR executed when Timer0 reaches value in OCR0A
     */
    ISR(TIMER0_COMPA_vect){  
        Os_Run();
        Timer0_Clear();
    }

    #if 0
    /**
     * @brief Interrupt routine for USART receive complete bit
     * Reads a single character from UDR and calls function handle this data
     */
    ISR(USART_RXC_vect){
        // char c = (char)UDR0;
        // serial_on_receive(c);
    }
    #endif

    
#endif /* ISR_GUARD */
