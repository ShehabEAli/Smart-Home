/************************************************************************/
/*Author      : Shehab Emad Ali										    */
/*File Name   : DIO_interface.h                                         */
/*Layer       : MCAL												    */
/*Description : This file contains interfacing parameters of DIO module */
/*Date        : 22 March 2023                                           */
/************************************************************************/

/*preprocessor header file guard*/
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/*************************************************************************/
/*************************Interfacing macros******************************/
/*************************************************************************/

/*Possible port IDs*/
#define DIO_PORTA              0
#define DIO_PORTB              1
#define DIO_PORTC              2
#define DIO_PORTD              3

/*Possible pin number*/
#define DIO_PIN0               0
#define DIO_PIN1               1
#define DIO_PIN2               2
#define DIO_PIN3               3
#define DIO_PIN4               4
#define DIO_PIN5               5
#define DIO_PIN6               6
#define DIO_PIN7               7

/*Possible pins directions*/
#define DIO_PIN_OUTPUT         1
#define DIO_PIN_INPUT_FLOAT    2
#define DIO_PIN_INPUT_PULLUP   3

/*possible output pins values*/
#define DIO_LOW_PIN            0
#define DIO_HIGH_PIN           1

/*possible port directions*/
#define DIO_PORT_OUTPUT        0
#define DIO_PORT_INPUT_FLOAT   1
#define DIO_PORT_INPUT_PULLUP  2


/*************************************************************************/
/*************************Functions' prototypes***************************/
/*************************************************************************/

/*this function shall set the direction of a specific pin*/
void DIO_voidSetPinDirection(u8 Copy_u8PortID , u8 Copy_u8Pin , u8 Copy_u8PinDirection);

/*this function shall set the value of any output pin*/
void DIO_voidSetPinValue(u8 Copy_u8PortID , u8 Copy_u8Pin , u8 Copy_u8PinValue );

/*this function is to set the direction of a specific port*/
void DIO_voidSetPortDirection(u8 Copy_u8PortID , u8 Copy_u8PinDirection);

/*this function is to set the value of a specific output port*/
/*return : error state
 * 0 -> ok   & 1-> invalid port ID & 2->value out of range   */
u8 DIO_u8SetPortValue(u8 Copy_u8PortID  , u8 Copy_u8PortValue);

/*this function is to toggle the pin value*/
void DIO_voidTogglePinValue(u8 Copy_u8PortID , u8 Copy_u8Pin);

/*this function is to get the value of an input pin*/
u8 DIO_voidGetPinValue(u8 Copy_u8PinID , u8 Copy_u8Pin );

#endif /* DIO_INTERFACE_H_ */
