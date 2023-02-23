/** @file UIM_UserInputModule.c
*   @brief Reads input from user - mode, start, reset
*/
#include "MCAL.h"
#include "UART_TX.h"
#include "UIM_UserInputModule.h"

/**********************************************************************
* Public functions 
***********************************************************************/

/** @brief Initialize the module
*/
void UIM_Init(void){
    log_info_P(PROGMEM_UIM_INIT);
}