/***********************************************************************/
/****************   Author   : Shehab Emad Ali   ***********************/
/****************   File Name: SERVO_interface.h  **********************/
/****************   Layer    : HAL	             ***********************/
/****************   Date     : 13 April 2023     ***********************/
/*Description :This file contains interfacing parameters of TIM1 module*/
/***********************************************************************/

/*macros for channel A and B*/
#define CHANNEL_A		1
#define CHANNEL_B		2

/*setting configurable frequancies leading
  into periodic time with out floating points*/
#define FREQ_20			50000
#define FREQ_40			25000
#define FREQ_50			20000
#define FREQ_100		10000
#define FREQ_200		5000
#define FREQ_250		4000
#define FREQ_500		2000
#define FREQ_1000		1000
#define FREQ_2000		500
#define FREQ_2500		400
#define FREQ_5000		200
#define FREQ_10000		100
#define FREQ_20000		50
#define FREQ_50000		20

/*************************************************************************/
/*************************Functions' prototypes***************************/
/*************************************************************************/


/*This function shall start PWM with TIM1*/

void TIM1_InitNonInvertedPWM(u8 Channel);
void TIM1_voidRunPWM(u8 Channel,u16 CompMatch);
void TIM1_PWMvoidSetDutyCycle(u8 Channel,ul32 DutyCycle,ul32 Freq);
void Servo_voidRotateServo(u8 Channel,u16 Angel);
