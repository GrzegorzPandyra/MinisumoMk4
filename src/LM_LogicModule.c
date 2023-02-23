/** @file LM_LogicModule.c
*   @brief Top-level control, implementation of behaviour algorithm.
*/
#include "UART_TX.h"

/** @brief Initialize the module
*/
void LM_Init(void){
    log_info_P(PROGMEM_LM_INIT);
}
