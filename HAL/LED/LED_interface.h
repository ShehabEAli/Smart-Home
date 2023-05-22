/************************************************************************/
/*Author      : Shehab Emad Ali										    */
/*File Name   : LED_interface.h                                         */
/*Layer       : HAL												    */
/*Description : This file contains interfacing parameters of LED module */
/*Date        : 27 March 2023                                           */
/************************************************************************/

/*preprocessor header file guard*/
#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_




/*************************************************************************/
/*************************Functions' prototypes***************************/
/*************************************************************************/
void LED_void_LedInit(u8 Copy_u8PortID , u8 Copy_u8Pin);
void LED_void_LedOn(u8 Copy_u8PortID , u8 Copy_u8Pin);
void LED_void_LedOff(u8 Copy_u8PortID , u8 Copy_u8Pin);
void LED_void_LedToggle(u8 Copy_u8PortID , u8 Copy_u8Pin);

#endif /* LED_INTERFACE_H_ */
