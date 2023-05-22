/*preprocessor header file guard*/
//#ifndef UART_cfg_H_
//#define UART_cfg_H_


#define REGISTER_SELECT 1
#define OPERATION_MODE  0


#define STOP_1BIT     0
#define STOP_2BIT     1

#define MODE_TRANSMITTER   0b00010000
#define MODE_RECIEVER      0b00001000
#define MODE_FULL_DUPLIX   0b00011000

#define PARITY_DISABLED    0b00000000
#define PARITY_RESERVED    0b00010000
#define PARITY_EVEN        0b00001000
#define PARITY_ODD         0b00011000



//
//#endif /* UART_cfg_H_ */
