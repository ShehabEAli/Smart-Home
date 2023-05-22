/************************************************************************/
/*Author      : Shehab Emad Ali										    */
/*File Name   : DC_Motor_interface.h                                    */
/*Layer       : HAL												        */
/*Description : This file contains interfacing parameters of DCM module */
/*Date        : 22 March 2023                                           */
/************************************************************************/

/*preprocessor header file guard*/
#ifndef DC_Motor_INTERFACE_H_
#define DC_Motor_INTERFACE_H_





/*************************************************************************/
/*************************Functions' prototypes***************************/
/*************************************************************************/
void DCM_voidInitial(u8 Copy_u8PortID , u8 Copy_u8Pin1 ,u8 Copy_u8Pin2);
void DCM_voidRotateCW(u8 Copy_u8PortID , u8 Copy_u8Pin1 ,u8 Copy_u8Pin2);
void DCM_voidRotateCCW(u8 Copy_u8PortID , u8 Copy_u8Pin1 ,u8 Copy_u8Pin2);
void DCM_voidStopRotate(u8 Copy_u8PortID , u8 Copy_u8Pin1 ,u8 Copy_u8Pin2);


#endif /* DC_Motor_INTERFACE_H_ */
