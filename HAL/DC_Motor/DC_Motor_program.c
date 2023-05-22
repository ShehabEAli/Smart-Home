

#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_cfg.h"

#include "DC_Motor_interface.h"
#include "DC_Motor_private.h"
#include "DC_Motor_cfg.h"

/******************************************************************************/
/*************************Functions' implementation****************************/
/******************************************************************************/

void DCM_voidInitial(u8 Copy_u8PortID , u8 Copy_u8Pin1 ,u8 Copy_u8Pin2){
	DIO_voidSetPinDirection(Copy_u8PortID,Copy_u8Pin1,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(Copy_u8PortID,Copy_u8Pin2,DIO_PIN_OUTPUT);
}

void DCM_voidRotateCW(u8 Copy_u8PortID , u8 Copy_u8Pin1 ,u8 Copy_u8Pin2){
	DIO_voidSetPinValue(Copy_u8PortID,Copy_u8Pin1,DIO_HIGH_PIN);
	DIO_voidSetPinValue(Copy_u8PortID,Copy_u8Pin2,DIO_LOW_PIN);
}
void DCM_voidRotateCCW(u8 Copy_u8PortID , u8 Copy_u8Pin1 ,u8 Copy_u8Pin2){
	DIO_voidSetPinValue(Copy_u8PortID,Copy_u8Pin2,DIO_HIGH_PIN);
	DIO_voidSetPinValue(Copy_u8PortID,Copy_u8Pin1,DIO_LOW_PIN);
}
void DCM_voidStopRotate(u8 Copy_u8PortID , u8 Copy_u8Pin1 ,u8 Copy_u8Pin2){
	DIO_voidSetPinValue(Copy_u8PortID,Copy_u8Pin1,DIO_LOW_PIN);
	DIO_voidSetPinValue(Copy_u8PortID,Copy_u8Pin2,DIO_LOW_PIN);
}
