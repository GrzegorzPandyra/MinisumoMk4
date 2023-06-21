/*! @file ADC.c
    @brief Analog-Digital Converter
    ADC conversion is triggered using TIMER0 (no Free-Running mode).
*/
#include "utils.h"
#include "adc.h"
#ifdef LOGGING_ENABLED
    #include "logging.h"
#endif

/**
 * @brief Initialize the ADC
 */
void ADC_Init(void){
    /* Set prescaler to 128 */
    Utils_SetBit((Register_T)&ADCSRA, ADPS0, BIT_SET);
    Utils_SetBit((Register_T)&ADCSRA, ADPS1, BIT_SET);
    Utils_SetBit((Register_T)&ADCSRA, ADPS2, BIT_SET);

    /* AVCC voltage ref */
    Utils_SetBit((Register_T)&ADMUX, REFS0, BIT_SET);
    Utils_SetBit((Register_T)&ADMUX, REFS1, BIT_CLEARED);

    /* Channel 0 */
    Utils_SetBit((Register_T)&ADMUX, MUX0, BIT_CLEARED);
    Utils_SetBit((Register_T)&ADMUX, MUX1, BIT_CLEARED);
    Utils_SetBit((Register_T)&ADMUX, MUX2, BIT_CLEARED);
    Utils_SetBit((Register_T)&ADMUX, MUX3, BIT_CLEARED);

    /* Autotrigger enable (to enable custom conversion trigger) */
    Utils_SetBit((Register_T)&ADCSRA, ADATE, BIT_SET);

    /* Enable interrupt on ADC conversion finished */
    Utils_SetBit((Register_T)&ADCSRA, ADIE, BIT_SET);

    /* Freerunning mode */
    Utils_SetBit((Register_T)&ADCSRB, ADTS0, BIT_CLEARED);
    Utils_SetBit((Register_T)&ADCSRB, ADTS1, BIT_CLEARED);
    Utils_SetBit((Register_T)&ADCSRB, ADTS2, BIT_SET);

    /* Enable ADC*/
    Utils_SetBit((Register_T)&ADCSRA, ADEN, BIT_SET);
    
    /* Trigger the first conversion */
    Utils_SetBit((Register_T)&ADCSRA, ADSC , BIT_SET);
    
    #ifdef LOGGING_ENABLED
        log_info_P(PROGMEM_ADC_INIT);
    #endif
} 
