#ifndef ADC_GUARD
#define ADC_GUARD

/*! @file ADC.h
    @brief API for Analog-Digital Converter
*/

typedef enum {
    ADC_CHANNEL0,
    ADC_CHANNEL1
}Adc_Channel_T;

void Adc_Init(void);
void Adc_SetChannel(Adc_Channel_T channel);
volatile uint16_t ADC_GetValue(void);

#endif /* ADC_GUARD */
