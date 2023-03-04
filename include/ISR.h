#ifndef ISR_GUARD
#define ISR_GUARD

    /** @file ISR.h
        @brief Interrupt Service Routines
        This file needs to be included in file with "main" function. ISRs are kept separated here for the purpose of clarity.
    */

    #include "UART_TX.h"
    #include "config.h"
    #include "DSD_DistanceSensorDrv.h"
    #include "TMR.h"

    void Task_10ms(void);

    #define TASK_10MS_TOP_VALUE 10

    static uint32_t task_10ms_counter = 0;

    /**
     * @brief 
     */
    ISR(ADC_vect){  
        DSD_ConversionCallback();
    }

    /**
     * @brief
     */
    ISR(TIMER0_OVF_vect){  
    }

    /**
     * @brief 
     */
    ISR(TIMER0_COMPA_vect){  
        if(task_10ms_counter == TASK_10MS_TOP_VALUE){
            task_10ms_counter = 0;
            Task_10ms();
        } else{
            task_10ms_counter++;
        }
        Timer_Clear();
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
