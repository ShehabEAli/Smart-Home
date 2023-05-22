/*
 * TWI_interface.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Shehab Emad Ali
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
	ok,
	InvalidStartCondition,
	InvalidRepeatedStart,
	InvalidSLAwithRead,
	InvalidSLAwithWrite,
	InvalidSendData,
	InvalidReceiveData
}TWI_ErrorState_t;








/*This Function Shall Initialize the Node as Master*/
void TWI_voidMasterInit(u8 Copy_u8Address);
/*This Function Shall Initialize the Node as Slave*/
void TWI_voidSlaveInit(u8 Copy_u8Address);
TWI_ErrorState_t TWI_StartCondition(void);
TWI_ErrorState_t TWI_RepeatedStart(void);
TWI_ErrorState_t TWI_SendSLAwithRead (u8 Copy_u8Address);
TWI_ErrorState_t TWI_SendSLAwithWrite(u8 Copy_u8Address);
TWI_ErrorState_t TWI_SendData(u8 Copy_u8Data);
TWI_ErrorState_t TWI_ReceiveData(u8 *Copy_u8Data);
TWI_ErrorState_t TWI_MasterReceiveStr(u8* Copy_u8Str, u8 Copy_u8STRLength);
void TWI_StopCondition(void);


#endif /* TWI_INTERFACE_H_ */
