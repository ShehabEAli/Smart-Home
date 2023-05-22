#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "GIE_interface.h"

#include"UART_interface.h"
#include"UART_private.h"
#include"UART_cfg.h"

void (*Global_ptrtoFunc)(void)=NULL;
void (*Global_ptrtoFunc2)(void)=NULL;
u8 *Global_u8RecievedData=NULL;
u8 Global_u8Data;


void UART_voidInit(u8 Copy_u8Parity,u8 Copy_u8StopBit,u8 Copy_u8OperationMode){

	UCSRC=(REGISTER_SELECT<<7)|(OPERATION_MODE<<6)|(Copy_u8Parity)|(Copy_u8StopBit<<3)|(1<<2)|(1<<1)|(0);
	CLR_BIT(UCSRB,2);

	/* assign the calculated bit_rate (9600) */
	UBRRL=51;

	/* enable transmitter and receiver mode -> full Duplex operation  */
	UCSRB|=Copy_u8OperationMode;

	/*SET_BIT(UCSRB , UCSRB_RXEN);
	SET_BIT(UCSRB , UCSRB_TXEN);*/
}

void UART_voidSendDataSync(u8 Copy_u8data){

	// MAKE sure UDRE is empty
	while((GET_BIT(UCSRA,UCSRA_UDRE))==0);

	// assign value to get transmitted
	UDR=Copy_u8data;

	// indicate if transmitter buffer is empty
	while((GET_BIT(UCSRA,UCSRA_TXC))==0);

//	// clear the flag
//	SET_BIT(UCSRA,UCSRA_TXC);
}

u8 UART_voidRecieveDataSync(void){
	//check if receiver buffer is empty
	while((GET_BIT(UCSRA,UCSRA_RXC))==0);

	return UDR;

}
void UART_voidSendDataAsync(u8 Copy_u8data,void(*Ptr_ToFunc)(void)){
	SET_BIT(UCSRB,UCSRB_TXCIE);
	SET_BIT(UCSRB,UCSRB_UDRIE);
	GIE_voidEnableGlobalInterrupt();
	Global_u8Data=Copy_u8data;
	if(Ptr_ToFunc !=NULL){
		Global_ptrtoFunc2=Ptr_ToFunc;
	}
}
void UART_voidReceiveAsync(u8 * Copy_pu8ReceivedData , void(*Copy_ptrToFunc)(void))
{

	/*Enable receive complete interrupt*/
	SET_BIT(UCSRB , UCSRB_RXCIE);

	/*Enable Global interrupt*/
	GIE_voidEnableGlobalInterrupt();

	if(Copy_ptrToFunc != NULL)
	{
		Global_ptrtoFunc = Copy_ptrToFunc ;
	}

	/*Passing the address of the location to store the recieved data to be global*/
	/*Received data is done by ISR*/
	Global_u8RecievedData = Copy_pu8ReceivedData ;


}
void UART_voidSendString(u8 arr[50]){
	u8 i=0;
	while(arr[i]!='\0'){
		UART_voidSendDataSync(arr[i]);
		i++;
	}
}

u8 * UART_voidReceiveString(u8 size){

	u8 arr5[size];
	for(u8 i=0;i<size;i++){
		arr5[i]=UART_voidRecieveDataSync();
	}
	return arr5;
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	/*Getting the received data*/
	*Global_u8RecievedData = UDR ;

	/*Call the application ISR*/
	Global_ptrtoFunc();
}

void __vector_14(void) __attribute__((signal));
void __vector_14(void){

	UDR=Global_u8Data;
	CLR_BIT(UCSRA,UCSRA_UDRE);
}
void __vector_15(void) __attribute__((signal));
void __vector_15(void){
	CLR_BIT(UCSRB,UCSRB_TXCIE);
	if(Global_ptrtoFunc2!=NULL){
		Global_ptrtoFunc2();

	}

}
