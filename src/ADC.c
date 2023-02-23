/*! @file ADC.c
    @brief Analog-Digital Converter
    ADC conversion is triggered using TIMER0 (no Free-Running mode).
*/
#include "MCAL.h"
#include "ADC.h"
#include "UART_TX.h"

/**
 * @brief Initialize the ADC
 */
void ADC_Init(void){
    /* Set prescaler to 128 */
    MCAL_SetBit((Register_T)&ADCSRA, ADPS0, BIT_SET);
    MCAL_SetBit((Register_T)&ADCSRA, ADPS1, BIT_SET);
    MCAL_SetBit((Register_T)&ADCSRA, ADPS2, BIT_SET);

    /* AVCC voltage ref */
    MCAL_SetBit((Register_T)&ADMUX, REFS0, BIT_SET);
    MCAL_SetBit((Register_T)&ADMUX, REFS1, BIT_CLEARED);

    /* Channel 0 */
    MCAL_SetBit((Register_T)&ADMUX, MUX0, BIT_CLEARED);
    MCAL_SetBit((Register_T)&ADMUX, MUX1, BIT_CLEARED);
    MCAL_SetBit((Register_T)&ADMUX, MUX2, BIT_CLEARED);
    MCAL_SetBit((Register_T)&ADMUX, MUX3, BIT_CLEARED);

    /* Autotrigger enable (to enable custom conversion trigger) */
    MCAL_SetBit((Register_T)&ADCSRA, ADATE, BIT_SET);

    /* Enable interrupt on ADC conversion finished */
    MCAL_SetBit((Register_T)&ADCSRA, ADIE, BIT_SET);

    /* Freerunning mode */
    MCAL_SetBit((Register_T)&ADCSRB, ADTS0, BIT_CLEARED);
    MCAL_SetBit((Register_T)&ADCSRB, ADTS1, BIT_CLEARED);
    MCAL_SetBit((Register_T)&ADCSRB, ADTS2, BIT_SET);

    /* Enable ADC*/
    MCAL_SetBit((Register_T)&ADCSRA, ADEN, BIT_SET);
    
    /* Trigger the first conversion */
    MCAL_SetBit((Register_T)&ADCSRA, ADSC , BIT_SET);
    
    log_info_P(PROGMEM_ADC_INIT);
} 
