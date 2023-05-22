/***********************************************************************/
/****************   Author   : Shehab Emad Ali   ***********************/
/****************   File Name: UART_interface.h  ***********************/
/****************   Layer    : MCAL	             ***********************/
/****************   Date     : 7 April 2023      ***********************/
/*Description :This file contains interfacing parameters of UART module*/
/***********************************************************************/






/*************************************************************************/
/*************************Functions' prototypes***************************/
/*************************************************************************/

void UART_voidInit(u8 Copy_u8Parity,u8 Copy_u8StopBit,u8 Copy_u8OperationMode);

void UART_voidSendDataSync(u8 Copy_u8data);

u8 UART_voidRecieveDataSync(void);

void UART_voidSendDataAsync(u8 Copy_u8data,void(*Ptr_ToFunc)(void));

void UART_voidReceiveAsync(u8 * Copy_u8ReceivedData , void(*Copy_ptrToFunc)(void));

void UART_voidSendString(u8 arr[15]);

u8 * UART_voidReceiveString(u8 size);


/*This function shall start UART*/


