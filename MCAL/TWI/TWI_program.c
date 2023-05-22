/*
 * TWI_program.c
 *
 *  Created on: Apr 14, 2023
 *      Author: Shehab Emad Ali
 */
#include"STD_TYPES.h"
#include"BIT_MATHS.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_cfg.h"

void TWI_voidMasterInit(u8 Copy_u8Address)
{
	/*Enable ACK Bit*/
	SET_BIT(TWCR,TWCR_TWEA);
	/*Setting Node Address*/
	Copy_u8Address=Copy_u8Address<<1;
	TWAR=Copy_u8Address;
	/*Setting Clock to Be 400KHz*/
	TWBR=2;
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);
	/*Enable TWI Peripheral*/
	SET_BIT(TWCR,TWCR_TWEN);
}
void TWI_voidSlaveInit(u8 Copy_u8Address)
{
	/*Setting Node Address*/
	Copy_u8Address=Copy_u8Address<<1;
	TWAR=Copy_u8Address;
	/*Enable ACK Bit*/
	SET_BIT(TWCR,TWCR_TWEA);
	/*Enable TWI Peripheral*/
	SET_BIT(TWCR,TWCR_TWEN);
}
TWI_ErrorState_t TWI_StartCondition(void)
{

	TWI_ErrorState_t Local_ErrorState = ok;
	/*Send Start condition on the bus */
	SET_BIT(TWCR,TWCR_TWSTA);
	/*Clear Interrupt Flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Polling over Interrupt Flag Till the operation is Done*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
	if((TWSR & STATUS_MASK)==START_ACK)
	{
		/*Do Nothing*/
	}
	else
	{
		Local_ErrorState = InvalidStartCondition;
	}


	return Local_ErrorState;

}
TWI_ErrorState_t TWI_RepeatedStart(void)
{
	TWI_ErrorState_t Local_ErrorState = ok;
	/*Send Start condition on the bus */
	SET_BIT(TWCR,TWCR_TWSTA);
	/*Clear Interrupt Flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Polling over Interrupt Flag Till the operation is Done*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
	if((TWSR & STATUS_MASK)==REP_START_ACK)
	{
		/*Do Nothing*/
	}
	else
	{
		Local_ErrorState = InvalidRepeatedStart;
	}


	return Local_ErrorState;
}
TWI_ErrorState_t TWI_SendSLAwithRead (u8 Copy_u8Address)
{
	TWI_ErrorState_t Local_ErrorState = ok;
	/*Set Value of Slave Address*/
	TWDR=(Copy_u8Address<<1)|1;
	/*Clearing Start Condition Bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);
	/*Clear Interrupt Flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Polling over Interrupt Flag Till the operation is Done*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
	if((TWSR & STATUS_MASK)==SLAVE_ADD_AND_RD_ACK)
	{
		/*Do Nothing*/
	}
	else
	{
		Local_ErrorState = InvalidSLAwithRead;
	}

	return Local_ErrorState;
}
TWI_ErrorState_t TWI_SendSLAwithWrite(u8 Copy_u8Address)
{
	TWI_ErrorState_t Local_ErrorState = ok;
	/*Set Value of Slave Address*/
	TWDR=Copy_u8Address<<1;
	/*For Read Request*/
	CLR_BIT(TWDR,0);
	/*Clearing Start Condition Bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);
	/*Clear Interrupt Flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Polling over Interrupt Flag Till the operation is Done*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
	if((TWSR & STATUS_MASK)==SLAVE_ADD_AND_WR_ACK)
	{
		/*Do Nothing*/
	}
	else
	{
		Local_ErrorState = InvalidSLAwithWrite;
	}

	return Local_ErrorState;
}
TWI_ErrorState_t TWI_SendData(u8 Copy_u8Data)
{
	TWI_ErrorState_t Local_ErrorState = ok;
	/*Set Value of Transmitted Data*/
	TWDR=Copy_u8Data;
	/*Clear Interrupt Flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Polling over Interrupt Flag Till the operation is Done*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
	if((TWSR & STATUS_MASK)==MSTR_WR_BYTE_ACK)
	{
		/*Do Nothing*/
	}
	else
	{
		Local_ErrorState = InvalidSendData;
	}

	return Local_ErrorState;
}
TWI_ErrorState_t TWI_ReceiveData(u8 *Copy_u8Data)
{
	TWI_ErrorState_t Local_ErrorState = ok;
	/*Clear Interrupt Flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Polling over the Interrupt Flag till the end of Receive*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
	if((TWSR & STATUS_MASK)==MSTR_RD_BYTE_WITH_ACK)
	{
		*Copy_u8Data = TWDR ;
	}
	else
	{
		Local_ErrorState = InvalidReceiveData;
	}
	return Local_ErrorState;
}

TWI_ErrorState_t TWI_MasterReceiveStr(u8* Copy_u8Str, u8 Copy_u8STRLength)
{
	TWI_ErrorState_t Local_ErrorState = ok;
	u8 i;

	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	for(i=0 ; i <= Copy_u8STRLength ; i++)
	{
		/*Clear The Interrupt Flag to Allow Slave to Send Data*/
		SET_BIT(TWCR,TWCR_TWINT);

		/*Polling till the Interrupt flag is raised
		 *Command is Executed*/
		while(!GET_BIT(TWCR,TWCR_TWINT));

		/*Check 5 MSB in TWSR for Error*/
		if((TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_ErrorState = InvalidReceiveData;
		}
		else
		{
			/*Read Received Data From Data Register*/
			Copy_u8Str[i] = TWDR ;
		}
		if (i == (Copy_u8STRLength-1))
		{
			/*Disable Acknowledge bit*/
			CLR_BIT(TWCR,TWCR_TWEA);
		}
	}
	Copy_u8Str[i-2]='\0';
	return Local_ErrorState;
}

void TWI_StopCondition(void)
{
	/*Enable Stop Condition*/
	SET_BIT(TWCR, TWCR_TWSTO);
	/*Clear Interrupt Flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
}
