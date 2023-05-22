/***********************************************************************/
/****************   Author   : Shehab Emad Ali   ***********************/
/****************   File Name: PWM_interface.h  ***********************/
/****************   Layer    : MCAL	             ***********************/
/****************   Date     : 7 April 2023      ***********************/
/*Description :This file contains interfacing parameters of TIM0 module*/
/***********************************************************************/

/*preprocessor header file guard*/
#ifndef PWM_PRIVATE_H_
#define PWM_PRIVATE_H_

/****************************************/
/*********  TIM0 Registers   ************/
/****************************************/

#define TCCR1A      (*(volatile u8*)(0x4F))
#define COM_A0			6
#define COM_A1			7
#define COM_B0			4
#define COM_B1			5
#define WGM10           0
#define WGM11           1


#define TCCR1B      (*(volatile u8*)(0x4E))
#define CS12			2
#define CS11			1
#define CS10			0
#define WGM12           3
#define WGM13           4

#define OCR1AH      (*(volatile u8*)(0x4B))
#define OCR1AL     	(*(volatile u8*)(0x4A))
#define OCR1A       (*(volatile u16*)(0x4A))

#define OCR1BH    	(*(volatile u8*)(0x49))
#define OCR1BL      (*(volatile u8*)(0x48))
#define OCR1B     	(*(volatile u16*)(0x48))

#define ICR1H    	(*(volatile u8*)(0x47))
#define ICR1L       (*(volatile u8*)(0x46))
#define ICR1        (*(volatile u16*)(0x46))

#define PRESCALER_MASK				0b11111000
#define TIM0_PRESCALER_8            2
#define TIM0_PRESCALER_64           3
#define TIM0_PRESCALER_256          4
#define TIM0_PRESCALER_1024         5

#endif /* PWM_PRIVATE_H_ */
