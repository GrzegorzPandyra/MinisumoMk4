#ifndef ISR_GUARD
#define ISR_GUARD

    /** @file ISR.h
        @brief Interrupt Service Routines
        This file needs to be included in file with "main" function. ISRs are kept separated here for the purpose of clarity.
    */
    #include "config.h"
    // #include "DSD_DistanceSensorDrv.h"
    // #include "TMR.h"

    void Task_10ms(void);
    void Task_1ms(void);

    #define TASK_10MS_TOP_VALUE 10

    // static uint32_t task_10ms_counter = 0;

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
        // if(task_10ms_counter == TASK_10MS_TOP_VALUE){
        //     task_10ms_counter = 0;
        //     Task_10ms();
        // } else{
        //     task_10ms_counter++;
        // }
        // Task_1ms();
        // Timer_Clear();
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
