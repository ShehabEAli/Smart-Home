/**********************************************************/
/*           Author  : Shehab Emad Ali                    */
/*           Layer   : MCAL                               */
/*           Version : 1.00                               */
/*           SWC     : ADC                                */
/**********************************************************/

#include "BIT_MATHS.h"
#include "STD_TYPES.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_cfg.h"

/****************************************************************************************/
/************************************Global Variables************************************/
/****************************************************************************************/

/*Global pointer to function to set end of conversion interrupt of call back*/
void(*Global_ptrEndOfConversion)(void)=NULL;
u8* Global_u8Reading=NULL;
/*Global pointer to Start Chain Conversion   */
static u8* ADC_pu8ChannelArr=NULL;
static u16* ADC_pu8ResultArr=NULL;
static u8* ADC_u8ChannelLength=NULL;
static void(*ADC_pvNotificationFunc)(void)=NULL;
static u8 ADC_u8ChannelIndex;
static u8 ADC_u8State=ADC_u8_IDLE;
/***********************************************************************************************/
/***********************************Functions' Implementation***********************************/
/***********************************************************************************************/
void ADC_voidInit(void){

	/*set reference voltage */
#if ADC_u8_REF_SELECTION==AREF
	/*set reference voltage ->AREF */
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_u8_REF_SELECTION==AVCC
	/*set reference voltage ->AVCC */
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_u8_REF_SELECTION==INTERNAL_2_56v
	/*set reference voltage ->INTERNAL_2_56v */
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error"Wrong ADC_u8_REF_SELECTION Configuration"

#endif

	/*set bit adjust*/
#if ADC_MODE==_8_bits
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_MODE==_10_bits
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error"Wrong ADC_u8_REF_SELECTION Configuration"
#endif

	/*Set Prescaler Configuration*/
	ADCSRA &=PRESCALER_MASK;
	ADCSRA |=PRESCALER_SELECTION;

	/*Enable ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}
u16 ADC_u16StartConversionSync(u8 Copy_u8Channel){

	/*Creating Local Variable to store the reading*/
	u8 LocalVar_u8Reading = 0;

	/** Set ADC Required Channel **/
	ADMUX &= MUX_MASK;
	ADMUX |= Copy_u8Channel;

	/*Start Conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

	/*Busy Waiting(polling) until the conversion Completes */
	while(GET_BIT(ADCSRA,ADCSRA_ADIF)==0);

	/*Clear The interrupt flag*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);

#if ADC_MODE==_8_bits
	LocalVar_u8Reading=ADCH;       //Read ADCH

#elif ADC_MODE==_10_bits           //Read ADC
	LocalVar_u8Reading=ADC;

#else
#error"Wrong Resolution Mode"
#endif

	return LocalVar_u8Reading;
}

void ADC_voidStartConversionAsync(u8 Copy_u8Channel, u8 *Copy_u8Reading){

	/*Enable end of conversion interrupt*/
	SET_BIT(ADCSRA,ADCSRA_ADIE);

	/*Enable Global interrupt*/
	SET_BIT(SREG,SREG_I);

	/*Assign global variable to get the reading*/
	Global_u8Reading = Copy_u8Reading;

	/** Set ADC Required Channel **/
	ADMUX &= MUX_MASK;
	ADMUX |= Copy_u8Channel;

	/*Start Conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

}

u8 ADC_voidStartChainConversionAsync(chain_t *Copy_Chain){
	u8 Local_u8ErrorState=Ok;
	if(Copy_Chain!=NULL){
		if(ADC_u8State==ADC_u8_IDLE){
		/*Initialise Channel Array*/
		ADC_pu8ChannelArr=Copy_Chain->ChannelArr;

		/*Initialise Result Array*/
		ADC_pu8ResultArr=Copy_Chain->ResultArr;

		/*Initialise Length */
		ADC_u8ChannelLength=Copy_Chain->Length;

		/*Initialise Chain Notification Function*/
		ADC_pvNotificationFunc=Copy_Chain->Notificationfunc;

		/*Initialise Channel Index */
		ADC_u8ChannelIndex=0;

		/** Set ADC first Channel **/
		ADMUX &= MUX_MASK;
		ADMUX |=ADC_pu8ChannelArr[ADC_u8ChannelIndex];

		/*Enable end of conversion interrupt*/
		SET_BIT(ADCSRA,ADCSRA_ADIE);

		/*Enable Global interrupt*/
		SET_BIT(SREG,SREG_I);

		/*Start Current Conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
		else{
			Local_u8ErrorState=BUSYFUNC;
		}
	}
	else{
		Local_u8ErrorState=NULL_Pointer;
	}
	return Local_u8ErrorState;
}

void ADC_voidSetCallBack(void(*Copy_ptrToFunction)(void)){
	if (Copy_ptrToFunction!=NULL)
	{
		Global_ptrEndOfConversion=Copy_ptrToFunction;
	}
	else{
		/*do Nothing*/
	}

}

/*ADC Conversion Complete ISR*/
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if(Global_ptrEndOfConversion!=NULL)
	{
#if ADC_MODE==_8_bits
		*Global_u8Reading=ADCH;

#elif ADC_MODE==_10_bits
		*Global_u8Reading=ADC;

#else
	#error"Wrong Mode Input"
#endif
		/*Assign global variable to get the reading*/
		Global_ptrEndOfConversion();


	}
	else
	{
		/*do Nothing*/
	}

}


//void __vector_16(void) __attribute__((signal));
//void __vector_16(void)
//{
//
//	if(ADC_pvNotificationFunc!=NULL)
//	{
//#if ADC_MODE==_8_bits
//		/*Read Current Conversion Result*/
//		ADC_pu8ChannelArr[ADC_u8ChannelIndex]=ADCH;
//		/*Increment channel index */
//		ADC_u8ChannelIndex++;
//		if(ADC_u8ChannelIndex!=ADC_u8ChannelLength){
//			/*Chain Not Completed*/
//			/*ADC is now busy*/
//			ADC_u8State=ADC_u8_BUSY;
//			/*Set next channel*/
//			ADMUX &= MUX_MASK;
//			ADMUX |=ADC_pu8ChannelArr[ADC_u8ChannelIndex];
//			/*Start Next Conversion*/
//			SET_BIT(ADCSRA,ADCSRA_ADSC);
//		}
//		else{
//			/*Chain Completed*/
//			/*ADC is now idle*/
//			ADC_u8State=ADC_u8_IDLE;
//			/*set Call Back Notification Function*/
//			ADC_pvNotificationFunc();
//			/*Disable ADC  Conversion Complete Interrupt*/
//			CLR_BIT(ADCSRA,ADCSRA_ADSC);
//		}
//
//#elif ADC_MODE==_10_bits
//		/*Read Current Conversion Result*/
//			ADC_pu8ChannelArr[ADC_u8ChannelIndex]=ADC;
//			/*Increment channel index */
//			ADC_u8ChannelIndex++;
//			if(ADC_u8ChannelIndex!=ADC_u8ChannelLength){
//				/*Chain Not Completed*/
//				/*Set next channel*/
//				ADMUX &= MUX_MASK;
//				ADMUX |=ADC_pu8ChannelArr[ADC_u8ChannelIndex];
//				/*Start Next Conversion*/
//				SET_BIT(ADCSRA,ADCSRA_ADSC);
//			}
//			else{
//				/*Chain Completed*/
//				/*set Call Back Notification Function*/
//				ADC_pvNotificationFunc();
//				/*Disable ADC  Conversion Complete Interrupt*/
//				CLR_BIT(ADCSRA,ADCSRA_ADSC);
//			}
//#else
//	#error"Wrong Mode Input"
//#endif
//
//	}
//	else
//	{
//		/*do Nothing*/
//	}
//
//}
