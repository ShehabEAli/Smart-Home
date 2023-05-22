/***************************************************************************/
/*Author      : Shehab Emad Ali										       */
/*File Name   : LED_program.c                                              */
/*Layer       : HAL										  		           */
/*Description : This file contains functions' implementation of LED module */
/*Date        : 27 March 2023                                              */
/***************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_cfg.h"

#include "LED_interface.h"
#include "LED_private.h"
#include "LED_cfg.h"

#include "DIP_interface.h"
#include "DIP_private.h"
#include "DIP_cfg.h"

/******************************************************************************/
/*************************Functions' implementation****************************/
/******************************************************************************/

void LED_void_LedInit(u8 Copy_u8PortID , u8 Copy_u8Pin){
	DIO_voidSetPinDirection( Copy_u8PortID , Copy_u8Pin , DIO_PIN_OUTPUT );
}

void LED_void_LedOn(u8 Copy_u8PortID , u8 Copy_u8Pin){
	DIO_voidSetPinValue( Copy_u8PortID , Copy_u8Pin , DIO_HIGH_PIN );
}

void LED_void_LedOff(u8 Copy_u8PortID , u8 Copy_u8Pin){
	DIO_voidSetPinValue( Copy_u8PortID , Copy_u8Pin , DIO_LOW_PIN );
}

void LED_void_LedToggle(u8 Copy_u8PortID , u8 Copy_u8Pin){
	DIO_voidTogglePinValue(Copy_u8PortID , Copy_u8Pin );
}
