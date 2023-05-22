/**************************************************************************/
/*Author      : Shehab Emad Ali										      */
/*File Name   : EEPROM_private.h                                          */
/*Layer       : HAL										  		          */
/*Description : This file contains functions' implementation of DIP module*/
/*Date        : 27 March 2023                                             */
/**************************************************************************/
#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_
#define Adress_mask   0b1010000
#define A2    1



/*This Function Shall Read byte From EEPROM*/
void EEPROM_voidSendData(u8 Copy_u8Data,u16 Copy_u16Address);
/*This Function Shall Read byte From EEPROM*/
void EEPROM_voidReciveData(u8 *Copy_u8Data,u16 Copy_u16Address);
/*This Function Shall Read String From EEPROM*/
void EEPROM_u8ReceiveStr(u16 Copy_u16Address,u8* Copy_u8Str, u8 Copy_strlength);
/*This Function Shall Send String to EEPROM*/
void EEPROM_u8SendStr(u16 Copy_u16Address,u8* Copy_u8Str);

#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
