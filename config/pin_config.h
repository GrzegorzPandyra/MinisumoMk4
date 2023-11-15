#ifndef PIN_CONFIG_GUARD
#define PIN_CONFIG_GUARD

/* Port configuration registers
 * DDRx - direction ports, write 1 to set pin as output, 0 for input
 * PORTx - used to output the value for output port
 * PINx - used to read the value of an input pin. 
*/

#define IR_TRIGGER_PIN PD5
#define IR_PORT PIND

#define BUZZER_PIN PD2
#define BUZZER_DDRx DDRD
#define BUZZER_PORTx PORTD

#endif /* PIN_CONFIG_GUARD */
