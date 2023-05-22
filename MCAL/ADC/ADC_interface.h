/**********************************************************/
/*           Author  : Shehab Emad Ali                    */
/*           Layer   : MCAL                               */
/*           Version : 1.00                               */
/*           SWC     : ADC                                */
/**********************************************************/

/*preprocessor header file guard*/
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_CHANNEL0    0
#define ADC_CHANNEL1    1
#define ADC_CHANNEL2    2
#define ADC_CHANNEL3    3
#define ADC_CHANNEL4    4
#define ADC_CHANNEL5    5
#define ADC_CHANNEL6    6
#define ADC_CHANNEL7    7


/************************************************************************************/
/*********************************Interfacing macros*********************************/
/************************************************************************************/


/*****************************************************************************/
/*****************************Functions' Prototypes***************************/
/*****************************************************************************/
typedef struct{
	u8 *ChannelArr;
	u8 *ResultArr;
	u8 Length;
	void(*Notificationfunc)(void);
}chain_t;

//this function shall initialise ADC peripheral
void ADC_voidInit(void);
//this function shall start Conversion Asynchronous
u16 ADC_u16StartConversionSync(u8 Copy_u8Channel);
//this function shall start Conversion Asynchronous
void ADC_voidStartConversionAsync(u8 Copy_u8Channel, u8 *Copy_u8Reading);
//this function shall start Chain Conversion Asynchronous
u8 ADC_voidStartChainConversionAsync(chain_t *Copy_Chain);
//This function shall start call back
void ADC_voidSetCallBack(void(*Copy_ptrToFunction)(void));
#endif /* ADC_INTERFACE_H_ */
