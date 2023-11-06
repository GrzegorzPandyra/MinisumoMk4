/** @file distance_sensor_drv.c
*   @brief Implementation of distance sensor
*/
#include <stddef.h>
#include "utils.h"
#include "distance_sensor_drv.h"
#include "logger_tx.h"
#include "adc.h"

/**********************************************************************
* Macros 
***********************************************************************/
#define MAX_NUM_SAMPLES 5
#define LEFT_DS_PIN PC1
#define RIGHT_DS_PIN PC0
#define RIGHT_DS_ADC_CHANNEL ADC_CHANNEL0
#define LEFT_DS_ADC_CHANNEL ADC_CHANNEL1

#if ENABLE_DS_DIAGNOSTICS
    #define STR_BUFF_LENGTH 80u
    #define DISTANCE_DISPLAY_DIVISOR 15u
#endif

/**********************************************************************
* Typedefs
***********************************************************************/
typedef struct Distance_Sensor_Tag{
    uint16_t samples[MAX_NUM_SAMPLES];
    uint16_t *sample_ptr;
    uint8_t pin;
    Adc_Channel_T channel;
} Distance_Sensor_T;

typedef struct {
    Distance_Sensor_T left_sensor;
    Distance_Sensor_T right_sensor;
    Distance_Sensor_T *active_sensor;
} DSDrv_Mgr_T;

/**********************************************************************
* Private variables
***********************************************************************/
static DSDrv_Mgr_T dsdrv_mgr = {
    .left_sensor  = {{0}, NULL, LEFT_DS_PIN, LEFT_DS_ADC_CHANNEL},
    .right_sensor = {{0}, NULL, RIGHT_DS_PIN, RIGHT_DS_ADC_CHANNEL},
    .active_sensor = NULL
};
/**********************************************************************
* Private functions 
***********************************************************************/

/**
 * @brief Add new sample to sensor buffer
 * @param sensor sensor to add the sample to
 * @param sample value to be added
 */
static void PushSample(Distance_Sensor_T *sensor, uint16_t sample){
    *(sensor->sample_ptr) = sample;
    if(sensor->sample_ptr == &(sensor->samples[MAX_NUM_SAMPLES-1])){
        sensor->sample_ptr = sensor->samples;
    } else {
        sensor->sample_ptr++;
    }
}
/**********************************************************************
* Public functions 
***********************************************************************/

/** @brief Initialize the module
*/
void Dsdrv_Init(void){
    INFO_P(PGM_DSD_INIT);

    /* Set DS pins as input */
    Utils_SetBit((Register_T) &DDRC, LEFT_DS_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T) &DDRC, RIGHT_DS_PIN, BIT_CLEARED);

    /* Initialize sample_ptr */
    dsdrv_mgr.left_sensor.sample_ptr = dsdrv_mgr.left_sensor.samples;
    dsdrv_mgr.right_sensor.sample_ptr = dsdrv_mgr.right_sensor.samples;
    dsdrv_mgr.active_sensor = &dsdrv_mgr.left_sensor;
}

/** @brief Get distance reading as an average of collected samples.
    @return distance to target between <0, ~750>, no specific unit. Highest value achieved around 5cm from target.
*/
Ds_Output_T Dsdrv_GetDistance(void){
    Ds_Output_T result = {0u, 0u};
    for(uint8_t i=0; i<MAX_NUM_SAMPLES; i++){
        result.l_ds_output += dsdrv_mgr.left_sensor.samples[i];
        result.r_ds_output += dsdrv_mgr.right_sensor.samples[i];
    }
    result.l_ds_output /= MAX_NUM_SAMPLES;
    result.r_ds_output /= MAX_NUM_SAMPLES;
    return result;
}

/** 
 * @brief Write new value to sensor buffer. Called in ISR when ADC conversion is finished.
 * @return none
*/
void Dsdrv_ConversionCallback(){
    volatile uint16_t adc_value;

    /* Read sensor value */
    adc_value = ADC_GetValue();

    /* Add new sample to the sample array */
    PushSample(dsdrv_mgr.active_sensor, adc_value);

    /* Switch active sensor */
     switch(dsdrv_mgr.active_sensor->channel){
        case RIGHT_DS_ADC_CHANNEL:
            dsdrv_mgr.active_sensor = &dsdrv_mgr.left_sensor;
            break;
        case LEFT_DS_ADC_CHANNEL:
            dsdrv_mgr.active_sensor = &dsdrv_mgr.right_sensor;
            break;
        default: 
            ERROR("Invalid channel");
            break;
    }
    Adc_SetChannel(dsdrv_mgr.active_sensor->channel);
}

#if ENABLE_DS_DIAGNOSTICS
    void Dsdrv_RunDiagnostics(void){
        char left_str[STR_BUFF_LENGTH] = {'\0'};
        char right_str[STR_BUFF_LENGTH] = {'\0'};
        uint8_t i;
        for(i=0; i<dsdrv_mgr.left_sensor.samples[0]/DISTANCE_DISPLAY_DIVISOR; i++){
            left_str[i] = '=';
        }
        for(i=0; i<dsdrv_mgr.right_sensor.samples[0]/DISTANCE_DISPLAY_DIVISOR; i++){
            right_str[i] = '=';
        }
        /* Alignment to keep display even */
        DATA2(" LEFT DS: %u %s\n", dsdrv_mgr.left_sensor.samples[0],  left_str);
        DATA2("RIGHT DS: %u %s\n", dsdrv_mgr.right_sensor.samples[0], right_str);
    }
#endif