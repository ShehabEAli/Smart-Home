#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "SERVO_cfg.h"
#include "SERVO_interface.h"
#include "SERVO_private.h"


void TIM1_InitNonInvertedPWM(u8 Channel){
	/* Set Mode 14 Fast PWM Wave generation  Mode of Timer 1   */
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);

	/*Set (Non Inverting)*/
	if(Channel==CHANNEL_A){
		CLR_BIT(TCCR1A,COM_A0);
		SET_BIT(TCCR1A,COM_A1);
	}
	else if (Channel==CHANNEL_B){
		CLR_BIT(TCCR1A,COM_B0);
		SET_BIT(TCCR1A,COM_B1);
	}
	/*set top value*/
	ICR1=FREQ_50;
	/*Set Prescaler */
	TCCR1B &=PRESCALER_MASK;
	TCCR1B |=TIM0_PRESCALER_8;

}
void TIM1_voidRunPWM(u8 Channel,u16 CompMatch){
	if (Channel == CHANNEL_A)
		{
			OCR1A = CompMatch;
		}
		else if (Channel == CHANNEL_B)
		{
			OCR1B = CompMatch;
		}
}
void Servo_voidRotateServo(u8 Channel,u16 Angel){
	    /*setting the channel*/
		if (Channel == CHANNEL_A)
		{
			OCR1A = ((175UL * (ul32)Angel) / 18UL) + 750UL;
		}
		else if (Channel == CHANNEL_B)
		{
			OCR1B = ((175UL * (ul32)Angel) / 18UL) + 750UL;
		}
}

