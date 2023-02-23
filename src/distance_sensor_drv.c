/** @file distance_sensor_drv.c
*   @brief Implementation of distance sensor
*/
#include "MCAL.h"
#include "UART_TX.h"
#include "distance_sensor_drv.h"

#define MAX_NUM_SAMPLES 5
#define DS_PIN PC0

typedef struct Distance_Sensor_Tag{
    uint16_t samples[MAX_NUM_SAMPLES];
    uint8_t samples_stored_cnt;
    uint16_t *sample_ptr;
} Distance_Sensor_T;

static Distance_Sensor_T ds_sensor = {{0}, 0, NULL};

/**********************************************************************
* Public functions 
***********************************************************************/

/** @brief Initialize the module
*/
void DSD_Init(void){
    log_info_P(PROGMEM_DSD_INIT);
    /* Set DS pins as input */
    MCAL_SetBit((Register_T) &DDRC, DS_PIN, BIT_CLEARED);
    /* Initialize sample_ptr */
    ds_sensor.sample_ptr = ds_sensor.samples;
}

/** @brief Get distance reading as an average of collected samples.
    @param none
    @return distance (only measure), the higher the value, the closer the target
*/
uint16_t DSD_GetDistance(void){
    uint16_t result = 0;
    for(uint8_t i=0; i<ds_sensor.samples_stored_cnt; i++){
        result += ds_sensor.samples[i];
    }
    return result/(uint16_t)ds_sensor.samples_stored_cnt;
}

/** @brief Write new value to sensor buffer. Called in ISR when ADC conversion is finished.
    @param val New value from ADC
    @return none
*/
void DSD_ConversionCallback(){
    // log_info("!");
    volatile uint32_t val = ADC; //(1<<ADCH)|ADCL;
    // val = val*1024/0x3ff;
    *ds_sensor.sample_ptr = val;

    if(ds_sensor.sample_ptr == &(ds_sensor.samples[MAX_NUM_SAMPLES-1])){
        ds_sensor.sample_ptr = ds_sensor.samples;
    } else {
        ds_sensor.sample_ptr++;
    }

    if(ds_sensor.samples_stored_cnt < MAX_NUM_SAMPLES){
        ds_sensor.samples_stored_cnt++;
    }
}