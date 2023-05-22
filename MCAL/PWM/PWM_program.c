#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include <util\delay.h>


#include "PWM_interface.h"
#include "PWM_private.h"
#include "PWM_cfg.h"

void TIM1_InitNonInvertedPWM(u8 Channel,u32 Freq){
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
	ICR1L=Freq;
	/*Set Prescaler */
	TCCR1B &=PRESCALER_MASK;
	TCCR1B |=TIM0_PRESCALER_8;

}
void TIM1_voidRunPWM(u8 Channel,u16 CompMatch){
	if(Channel==CHANNEL_A)
	{
		OCR1AL=CompMatch;
	}
	else if (Channel==CHANNEL_B){
		OCR1BL=CompMatch;
	}
}
void TIM1_PWMvoidSetDutyCycle(u8 Channel,ul32 DutyCycle,ul32 Freq){
	if(Channel==CHANNEL_A){
		OCR1AL=((DutyCycle*Freq)/100);
	}
	else if (Channel==CHANNEL_B){
		OCR1BL=((DutyCycle*Freq)/100);
	}
}
