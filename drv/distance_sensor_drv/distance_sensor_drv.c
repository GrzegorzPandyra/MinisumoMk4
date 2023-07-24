/** @file distance_sensor_drv.c
*   @brief Implementation of distance sensor
*/
#include <stddef.h>
#include "utils.h"
#include "distance_sensor_drv.h"
#include "logger_tx.h"
#include "adc.h"

#define MAX_NUM_SAMPLES 5
#define LEFT_DS_PIN PC0
#define RIGHT_DS_PIN PC1

typedef struct Distance_Sensor_Tag{
    uint16_t samples[MAX_NUM_SAMPLES];
    uint8_t samples_stored_cnt;
    uint16_t *sample_ptr;
    uint8_t pin;
    Adc_Channel_T channel;
} Distance_Sensor_T;

static Distance_Sensor_T ds_left = {{0}, 0, NULL, LEFT_DS_PIN, CHANNEL0};
static Distance_Sensor_T ds_right = {{0}, 0, NULL, RIGHT_DS_PIN, CHANNEL1};
static Distance_Sensor_T *active_ds = NULL;

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
    ds_left.sample_ptr = ds_left.samples;
    ds_right.sample_ptr = ds_right.samples;
    active_ds = &ds_left;
}

/** @brief Get distance reading as an average of collected samples.
    @param none
    @return distance (only measure), the higher the value, the closer the target
*/
uint16_t Dsdrv_GetDistance(void){
    // uint16_t result = 0;
    // for(uint8_t i=0; i<ds_sensor.samples_stored_cnt; i++){
    //     result += ds_sensor.samples[i];
    // }
    // return result/(uint16_t)ds_sensor.samples_stored_cnt;
}

/** @brief Write new value to sensor buffer. Called in ISR when ADC conversion is finished.
    @return none
*/
void Dsdrv_ConversionCallback(){
    volatile uint16_t adc_value = Utils_ReadRegister16((Register16_T)&ADC);
    *(active_ds->sample_ptr) = adc_value;

    if(active_ds->sample_ptr == &(active_ds->samples[MAX_NUM_SAMPLES-1])){
        active_ds->sample_ptr = active_ds->samples;
    } else {
        active_ds->sample_ptr++;
    }

    if(active_ds->samples_stored_cnt < MAX_NUM_SAMPLES){
        active_ds->samples_stored_cnt++;
    }

     switch(active_ds->channel){
        case CHANNEL0:
            active_ds = &ds_right;
            Adc_SetChannel(CHANNEL1);
        break;
        case CHANNEL1:
            active_ds = &ds_left;
            Adc_SetChannel(CHANNEL0);
        break;
        default: 
        break;
    }
}

#if ENABLE_DS_DIAGNOSTICS
    void Dsdrv_RunDiagnostics(void){
        char left_str[50] = {'\0'};
        char right_str[50] = {'\0'};
        uint8_t i;
        for(i=0; i<*(ds_left.sample_ptr)/10; i++){
            left_str[i] = '=';
        }
        for(i=0; i<*(ds_right.sample_ptr)/10; i++){
            right_str[i] = '=';
        }
        DATA2("LEFT DS : %d %s\n", *(ds_left.sample_ptr),  left_str);
        DATA2("RIGHT DS: %d %s\n", *(ds_right.sample_ptr), right_str);
    }
#endif