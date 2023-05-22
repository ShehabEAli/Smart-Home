/**************************************************************************/
/*Author      : Shehab Emad Ali										      */
/*File Name   : EEPROM_program.c                                          */
/*Layer       : HAL										  		          */
/*Description : This file contains functions' implementation of DIP module*/
/*Date        : 27 March 2023                                             */
/**************************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATHS.h"
#include<util/delay.h>

#include"TWI_interface.h"

#include"EEPROM_interface.h"
#include"EEPROM_private.h"
#include"EEPROM_cfg.h"

void EEPROM_voidSendData(u8 Copy_u8Data,u16 Copy_u16Address){
	u8 LOcal_Address;
	LOcal_Address=((Adress_mask) |(A2<<2)|(u8)(Copy_u16Address>>8));

	TWI_StartCondition();

	TWI_SendSLAwithWrite(LOcal_Address);

	TWI_SendData((u8)Copy_u16Address);

	TWI_SendData(Copy_u8Data);

	TWI_StopCondition();

_delay_ms(10);

}
void EEPROM_voidReciveData(u8 *Copy_u8Data,u16 Copy_u16Address){
	u8 LOcal_Address;
		LOcal_Address=((Adress_mask)|(A2<<2)|(u8)(Copy_u16Address>>8));

	TWI_StartCondition();

	TWI_SendSLAwithWrite(LOcal_Address);

		TWI_SendData((u8)Copy_u16Address);
		TWI_RepeatedStart();
		TWI_SendSLAwithRead(LOcal_Address);

	TWI_ReceiveData(Copy_u8Data);
	TWI_StopCondition();
	_delay_ms(10);

}

void EEPROM_u8ReceiveStr(u16 Copy_u16Address,u8* Copy_u8Str, u8 Copy_strlength)
{
	u8 i,Local_u8Address = 0 ;
	Local_u8Address = ((Adress_mask)|(A2<<2)|(u8)(Copy_u16Address>>8));

	/*Send Start Condition to Start Communication and Control the Bus*/
	TWI_StartCondition();

	/*Send EEPROM Slave Address with Write*/
	TWI_SendSLAwithWrite(Local_u8Address);

	/*Send the Byte Location in the EEPROM*/
	TWI_SendData((u8)Copy_u16Address);

	/*Send Repeat Start to Change Condition to Read*/
	TWI_RepeatedStart();

	/*Send EEPROM Slave Address with Write*/
	TWI_SendSLAwithRead(Local_u8Address);

	/*Send Required Data*/
	TWI_MasterReceiveStr(Copy_u8Str,Copy_strlength);

	/*Send Stop Condition to Stop Communication and Free the Bus*/
	TWI_StopCondition();

	/*Delay until the write cycle is finished*/
	_delay_ms(20);
}

/*This Function Shall Send String to EEPROM*/
void EEPROM_u8SendStr(u16 Copy_u16Address,u8* Copy_u8Str)
{
	u8 Iterator;
	for(Iterator = 0 ; Copy_u8Str[Iterator]!='\0' ; Iterator++ , Copy_u16Address++)
	{
		/*Send Received Char to EEPROM Addess*/
		EEPROM_voidSendData(Copy_u16Address,Copy_u8Str[Iterator]);
	}
	/*Send Null Char to NEXT EEPROM Addess*/
//	EEPROM_voidSendByte(Copy_u16Address,'\0');

}
void EEPROM_voidEraseDataByte(u16 Copy_u16Address)
{
    u8 Local_u8Address;
    Local_u8Address = ((Adress_mask) | (A2 << 2) | ((u8)(Copy_u16Address >> 8)));
    TWI_StartCondition();
    TWI_SendSLAwithWrite(Local_u8Address);
    TWI_SendData((u8)Copy_u16Address);
    TWI_SendData(0xFF);
    TWI_StopCondition();
    _delay_ms(20);
}


void EEPROM_voidEraseData(u16 Copy_u16FirstAddress, u16 Copy_u16SecondAddress)
{
    u8 Local_u8Itirator = Copy_u16FirstAddress;
    for (Local_u8Itirator = Copy_u16FirstAddress; Local_u8Itirator <= Copy_u16SecondAddress; Local_u8Itirator++)
    {
        EEPROM_voidEraseDataByte(Local_u8Itirator);
    }
}
