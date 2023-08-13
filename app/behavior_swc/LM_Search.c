/** @file LM_Search.c
*   @brief Sub-module of LM, responsible for searching and moving around when not attacking/repositioning
*/
#include "LM_Search.h"
#include "UART_TX.h"
#include "stdlib.h"

#undef RAND_MAX 
#define RAND_MAX 0x0003
#define RANDOM_SEED 0xFE65
#define MAX_ACTION_VALUE 255

#define INITIAL_FORWARD_ACTION_VALUE 200
#define INITIAL_BACKWARD_ACTION_VALUE 150
#define INITIAL_TURN_ACTION_VALUE 80
#define FORWARD_ACTION_VALUE_INCREMENT 10
#define BACKWARD_ACTION_VALUE_INCREMENT 10
#define TURN_ACTION_VALUE_INCREMENT 5
#define COMMON_INCREMENT_INCREASE 5

typedef struct Action_Tag{
    Direction_T direction;
    uint16_t value;
    uint8_t increment;
} Action_T;

Action_T action_matrix[] = {
    {FORWARD,       INITIAL_FORWARD_ACTION_VALUE,   FORWARD_ACTION_VALUE_INCREMENT  },
    {BACKWARD,      INITIAL_BACKWARD_ACTION_VALUE,  BACKWARD_ACTION_VALUE_INCREMENT },
    {TURN_RIGHT,    INITIAL_TURN_ACTION_VALUE,      TURN_ACTION_VALUE_INCREMENT     },
    {TURN_LEFT,     INITIAL_TURN_ACTION_VALUE,      TURN_ACTION_VALUE_INCREMENT     }
};

typedef struct Tracker_Tag{

} Tracker_T;

/*****************************************************
 * Private functions
 *****************************************************/
static Action_T GetTopAction(){
    uint8_t top_action_index = 0; 
    for(uint8_t i = 1; i < arr_length(action_matrix); i++){
        if(action_matrix[top_action_index].value < action_matrix[i].value){
            top_action_index = i;
        }
    }
    return action_matrix[top_action_index];
}
/*****************************************************
 * Public functions
 *****************************************************/

/** @brief Initialize the module
*/
void LM_Search_Init(void){
    srand(RANDOM_SEED);
}

/**
 * @brief 
 */
Direction_T LM_Search(void){
    Action_T top_action = GetTopAction();
    for(uint8_t i = 0; i < arr_length(action_matrix); i++){
        if(action_matrix[i].direction != top_action.direction){
            action_matrix[i].value += action_matrix[i].increment;
            action_matrix[i].increment += COMMON_INCREMENT_INCREASE;
        } else {
            action_matrix[i].value -= action_matrix[i].increment;
            action_matrix[i].increment -= COMMON_INCREMENT_INCREASE;
        }
    }
    return top_action.direction;
}