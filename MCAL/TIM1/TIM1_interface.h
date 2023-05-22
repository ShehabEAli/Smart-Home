/***********************************************************************/
/****************   Author   : Shehab Emad Ali   ***********************/
/****************   File Name: TMI1_interface.h  ***********************/
/****************   Layer    : MCAL	             ***********************/
/****************   Date     : 7 April 2023      ***********************/
/*Description :This file contains interfacing parameters of TMI0 module*/
/***********************************************************************/



/*************************************************************************/
/*************************Functions' prototypes***************************/
/*************************************************************************/


/*This function shall start timer0*/

void TIMR1_voidRunServo(void);
void TIMR1_voidSetAngel(u16 Copy_u8OnValue);
