#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include <util\delay.h>

#include "TIM1_cfg.h"
#include "TIM1_interface.h"
#include "TIM1_private.h"



void TIMR1_voidRunServo(void){
	//set compare output mode
	SET_BIT(TCCR1A,COM_A1);
	CLR_BIT(TCCR1A,COM_A0);
	//set wave generation mode
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);

	//set top value in ICR
	ICR1=20000;
	//set prescaler
	TCCR1B &=PRESCALER_MASK;
	TCCR1B |=TIM0_PRESCALER_8;
}
void TIMR1_voidSetAngel(u16 Copy_u8OnValue){
	OCR1A=Copy_u8OnValue;
}

