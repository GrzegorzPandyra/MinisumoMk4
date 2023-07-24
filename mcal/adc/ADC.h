#ifndef ADC_GUARD
#define ADC_GUARD

/*! @file ADC.h
    @brief API for Analog-Digital Converter
*/

typedef enum {
    CHANNEL0,
    CHANNEL1
}Adc_Channel_T;

void Adc_Init(void);
void Adc_SetChannel(Adc_Channel_T channel);

#endif /* ADC_GUARD */
