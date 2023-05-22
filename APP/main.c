/************************************************************************/

/*Author      : Shehab Emad Ali 									    */

/*File Name   : Smart Home Application                                  */

/*Date        : 20 May 2023                                             */

/************************************************************************/ 


#include "STD_TYPES.h"

#include "BIT_MATHS.h"

#include "util/delay.h"

#include "string.h"

#include <stdbool.h>

#include"DIO_interface.h"

#include"GIE_interface.h"

#include"SERVO_interface.h"


#include"UART_interface.h"

#include"UART_private.h"

#include"UART_cfg.h"


#include"ADC_interface.h"

#include"ADC_private.h"

#include"ADC_cfg.h"


#include"BUZER_interface.h"

#include"TWI_interface.h"

#include"EEPROM_interface.h"


void Application(void);

u8 *Reading=0;

u16 Local_u16Temb;

int main(void)
{

	/* Initialize variables */
	u8 US_flag = 0x00;
	
	u8 flow_flag = 0x00;
	
	bool password_verified = false;
	
	char USER_NAME[6];
	
	char Password[6];
	
	u8 Local_u8Compare;
	
	u8 LocalRecieve = 0x00;
	
	u8 US1_flag = 5;
	
	u8 US2_flag = 5;
	
	u8 US3_flag = 5;
	
	char LocalRecieve_data[6];
	
	char LocalRecieve_US1data[6];
	
	char LocalRecieve_US2data[6];
	
	char LocalRecieve_US3data[6];

	/* Set the initial address for copying */
	u16 Copy_u16Adress = 0x00;

	/* Set the direction of the RX and TX pins */
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_INPUT_FLOAT); 
	
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN1, DIO_PIN_OUTPUT); 


	/* Set the direction of a port and two pins */
	DIO_voidSetPortDirection(DIO_PORTB, DIO_PORT_OUTPUT);
	
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
	
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN1, DIO_PIN_OUTPUT);


	/* Set the direction of a pin for thebuzzer */
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN7, DIO_PIN_OUTPUT);

	/* Initialize the UART with the specified parameters */
	UART_voidInit(PARITY_DISABLED, STOP_1BIT, MODE_FULL_DUPLIX);

	/* Initialize the Timer1 in non-inverted PWM mode for channel A */
	TIM1_InitNonInvertedPWM(CHANNEL_A);

	/* Initialize the I2C/TWI master */
	TWI_voidMasterInit(0);
	
/*To Erase the data from EEprom*/
//	EEPROM_voidEraseDataByte(0);

/*To add user name and password for admin only once*/
//			UART_voidSendString("\rUser Name: ");

//			USART_voidReciveString(USER_NAME,6);

//			EEPROM_u8SendStr(0,USER_NAME);



//			UART_voidSendString("\rpassword: ");

//			USART_voidReciveString(Password,6);

//			EEPROM_u8SendStr(5,Password);



//			/*To initialize all flags of users */
//			UART_voidSendString("\rpassword: ");

//			USART_voidReciveString(Password,6);

//			EEPROM_u8SendStr(user1,Password);


	while(US_flag<5)
	{
		
		UART_voidSendString("\rModes  [1]-Admin   [2]-User");
		
		UART_voidSendString("\rPlease select: ");
		
		LocalRecieve=UART_voidRecieveDataSync();
		
		/*******************************For Admin****************************************/
		
		if(LocalRecieve == '1')
		{
			
			while(US_flag<5)
			{
				
				UART_voidSendString("\rAdmin's name: ");
				
				EEPROM_u8ReceiveStr(0,LocalRecieve_data,6);
				
				USART_voidReciveString(USER_NAME,6);
				
				/* Compare the entered admin's name with the stored one in the EEPROM */
				if(strcmp(LocalRecieve_data,USER_NAME) == 0)
				{
					while(US_flag<5)
					{
						
						/* Prompt the user to enter the admin's password and compare it with the stored one in the EEPROM */
						UART_voidSendString("\rAdmin's password: ");
						
						EEPROM_u8ReceiveStr(5,LocalRecieve_data,6);
						
						USART_voidReciveString(Password,6);

						if(strcmp(LocalRecieve_data,Password) ==0)
						{
							/* Play a note to indicate that the password is correct */
							Play_Note(F,250);
							
							/* Retrieve the flags of the three users from the EEPROM */
							EEPROM_u8ReceiveStr(user1,&US1_flag,2);
							
							EEPROM_u8ReceiveStr(user2,&US2_flag,2);
							
							EEPROM_u8ReceiveStr(user3,&US3_flag,2);
							
							
							
							/* Prompt the user to select an option */
							UART_voidSendString("\rAdmin's option 1- Add new User 2- Change data of any User 3- Remove a user");
							
							UART_voidSendString("\rplease select: ");
							
							LocalRecieve=UART_voidRecieveDataSync();
							
							if(LocalRecieve=='1')
							{

								/* Add a new user to the system */
								if (US1_flag == '0')
								{
									
									UART_voidSendString("\rFirst User Name: ");
									
									USART_voidReciveString(USER_NAME,6);
									
									/* Store the new user's name in the EEPROM */
									EEPROM_u8SendStr(10,USER_NAME);
									
									UART_voidSendString("\rFirst password: ");
									
									USART_voidReciveString(Password,6);
									
									/* Store the new  password in the EEPROM */
									EEPROM_u8SendStr(15,Password);
									
									EEPROM_u8SendStr(user1,"1");
									
									flow_flag=1;
									
								}
								
								else if(US2_flag =='0')
								{
									
									UART_voidSendString("\rSecond User Name: ");
									
									USART_voidReciveString(USER_NAME,6);
									
									/* Store the new user's name in the EEPROM */
									EEPROM_u8SendStr(20,USER_NAME);
									
									UART_voidSendString("\rSecond password: ");
									
									USART_voidReciveString(Password,6);
									
									/* Store the new  password in the EEPROM */
									EEPROM_u8SendStr(25,Password);
									
									EEPROM_u8SendStr(user2,"1");
									
									flow_flag=1;
									
								}
								
								else if(US3_flag =='0')
								{
									
									UART_voidSendString("\rThird User Name: ");
									
									USART_voidReciveString(USER_NAME,6);
									
									/* Store the new user's name in the EEPROM */
									EEPROM_u8SendStr(30,USER_NAME);
									
									UART_voidSendString("\rThird password: ");
									
									USART_voidReciveString(Password,6);
									
									/* Store the new  password in the EEPROM */
									EEPROM_u8SendStr(35,Password);
									
									EEPROM_u8SendStr(user3,"1");
									
									flow_flag=1;
								}
								
								else
								{
									
									UART_voidSendString("\rYou Already Have 3 Uers");
									
								}
								
								break;
								
							}
							
							/* Change the data of an existing user */
							else if (LocalRecieve=='2')
							{

								UART_voidSendString("\rChanging in [1]-first user  [2]-second user  [3] Third user");
								
								UART_voidSendString("\rplease select: ");
								
								LocalRecieve=UART_voidRecieveDataSync();
								
								if(LocalRecieve=='1')
								{
									
									UART_voidSendString("\rNew First User Name: ");
									
									USART_voidReciveString(USER_NAME,6);
									
									EEPROM_u8SendStr(10,USER_NAME);
									
									UART_voidSendString("\rNew First password: ");
									
									USART_voidReciveString(Password,6);
									
									EEPROM_u8SendStr(15,Password);
									
									flow_flag=1;
									
								}
								
								else if(LocalRecieve=='2')
								{
									
									UART_voidSendString("\rNew Second User Name: ");
									
									USART_voidReciveString(USER_NAME,6);
									
									EEPROM_u8SendStr(20,USER_NAME);
									
									UART_voidSendString("\rNew Second password: ");
									
									USART_voidReciveString(Password,6);
									
									EEPROM_u8SendStr(25,Password);
									
									flow_flag=1;

								}
								
								else if(LocalRecieve=='3')
								{
									
									UART_voidSendString("\rNew Third User Name: ");
									
									USART_voidReciveString(USER_NAME,6);
									
									EEPROM_u8SendStr(30,USER_NAME);
									
									UART_voidSendString("\rNew Third password: ");
									
									USART_voidReciveString(Password,6);
									
									EEPROM_u8SendStr(35,Password);
									
									flow_flag=1;
									
								}
								
								break;
								
							}
							
							/* Remove an existing user from EEPROM*/
							
							else if(LocalRecieve=='3')
							{
								
								UART_voidSendString("\rRemoving Of The [1]-first user  [2]-second user  [3] Third user");
								
								UART_voidSendString("\rplease select: ");
								
								LocalRecieve=UART_voidRecieveDataSync();
								
								if(LocalRecieve=='1')
								{
									
									/* Erase the data of the first user from the EEPROM */
									if(US1_flag=='1')
									{
										
										EEPROM_voidEraseData(10,19);
										
										EEPROM_u8SendStr(user1,"0");
										
										flow_flag=1;
									}
									
									else 
									{
										
										UART_voidSendString("\rNo user to Remove");
										
									}


								}
								
								else if(LocalRecieve=='2')
								{
									
									if(US2_flag=='1')
									{
										/* Erase the data of the second user from the EEPROM */
										EEPROM_voidEraseData(20,29);
										
										EEPROM_u8SendStr(user2,"0");
										
										flow_flag=1;
										
									}
									
									else 
									{
										
										UART_voidSendString("\rNo user to Remove");
										
									}

								}
								
								else if(LocalRecieve=='3')
								{
									
									if(US3_flag=='1')
									{
										
										/* Erase the data of the third user from the EEPROM */
										
										EEPROM_voidEraseData(30,39);
										
										EEPROM_u8SendStr(user3,"0");
										
										flow_flag=1;
										
									}
									
									else 
									{
										
										UART_voidSendString("\rNo user to Remove");
										
									}

								}
								
								break;
								
							}

							else
							{
								
								UART_voidSendString("\rInvalid input");
								
							}

						}
						
						else
						{
							
							UART_voidSendString("\rInvalid password");
							
							US_flag++;
							
						}
						//						break;
					}

				}
				
				else
				{
					UART_voidSendString("\rInvalid admin ");
					
					US_flag++;
				}
				
				if(flow_flag==1)
				{
					break;
					
					
				}
				
				
			}


		}
		
		
		/*******************************For Users****************************************/
		else if(LocalRecieve == '2')
		{

			while(US_flag<5&& !password_verified)
			{

				EEPROM_u8ReceiveStr(10,&LocalRecieve_US1data,6);
				
				EEPROM_u8ReceiveStr(20,&LocalRecieve_US2data,6);
				
				EEPROM_u8ReceiveStr(30,&LocalRecieve_US3data,6);
				
				UART_voidSendString("\rUser Name: ");
				
				USART_voidReciveString(USER_NAME,6);
				
				if( strcmp(LocalRecieve_US1data,USER_NAME)==0 )
				{
					
					while(US_flag<5)
					{
						
						UART_voidSendString("\rWelcome User 1 Enter your Password: ");
						
						EEPROM_u8ReceiveStr(15,&LocalRecieve_US1data,6);
						
						USART_voidReciveString(Password,6);
						
						if(strcmp(LocalRecieve_US1data,Password) ==0 )
						{
							/* Play a note to indicate that the password is correct */
							Play_Note(F,250);
							
							password_verified = true;
							
							break;
						}
						
						else
						{
							UART_voidSendString("\rInvalid");
							
							US_flag++;
						}
					}

				}
				
				else if(strcmp(LocalRecieve_US2data,USER_NAME) ==0)
				{
					
					while(US_flag<5)
					{
						
						UART_voidSendString("\rWelcome User 2 Enter your Password: ");
						
						EEPROM_u8ReceiveStr(25,&LocalRecieve_US2data,6);
						
						USART_voidReciveString(Password,6);
						
						
						if( strcmp(LocalRecieve_US2data,Password) ==0 )
						{
							
							/* Play a note to indicate that the password is correct */
							Play_Note(F,250);
							
							password_verified = true;
							
							break;
						}
						
						else
						{
							
							UART_voidSendString("\rInvalid");
							
							US_flag++;
							
						}
						
						
					}


				}
				
				else if(strcmp(LocalRecieve_US3data,USER_NAME)==0)
				{
					
					while(US_flag<5)
					{
						
						UART_voidSendString("\rWelcome User 3 Enter your Password: ");
						
						EEPROM_u8ReceiveStr(35,&LocalRecieve_US3data,6);
						
						USART_voidReciveString(Password,6);
						
						
						if( strcmp(LocalRecieve_US3data,Password)==0 )
						{
							
							/* Play a note to indicate that the password is correct */
							Play_Note(F,250);
							
							password_verified = true;
							
							break;
							
						}
						
						else
						{
							UART_voidSendString("\rInvalid");
							
							US_flag++;
							
						}
					}

				}
				
				if (password_verified)
				{
					
					break;
					
				}
				
				else
				{
					
					UART_voidSendString("\rInvalid User Name Please Try Again ");
					
					US_flag++;
					
				}
				
			}
			
			break;

		}
		
		else
		{
			
			UART_voidSendString("\rInvalid input");
			
			US_flag++;
			
		}

	}
	
	if(US_flag == 5)
	{
		
		UART_voidSendString("\rplease reset the system and try again");
		
		while(1){
			
			/* Play a note to indicate that the password is correct */
			Play_Note(F,250);
			
			_delay_ms(100);
			
		}
		
		while(US_flag == 5);
		
	}
	

	UART_voidSendString("\rWelcome");
	
	UART_voidSendString("\rYour Options");
	
	UART_voidSendString("\r[1]: OPEN DOOR");
	
	UART_voidSendString("\r[2]: CLOSE DOOR");
	
	UART_voidSendString("\r[3]: LED ON");
	
	UART_voidSendString("\r[4]: LED OFF");
	
	UART_voidSendString("\r[5]: OPEN VAN >30");
	
	UART_voidSendString("\r[6]: CLOSE VAN <30\r");

	/* Delay for 1 second */
	_delay_ms(1000);

	/* Set the direction of two pins */
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, DIO_PIN_INPUT_FLOAT);
	
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN7, DIO_PIN_OUTPUT);


	/* Initialize the ADC */
	ADC_voidInit();

	/* Initialize a DC motor */
	DCM_voidInitial(DIO_PORTA, DIO_PIN6, DIO_PIN7);

	/* Set a callback function for the ADC */
	ADC_voidSetCallBack(Application);
	
	while (1)
	{
		
		/* Start an asynchronous ADC conversion on channel 0 */
		ADC_voidStartConversionAsync(ADC_CHANNEL0, Reading);

		/* Wait for a synchronous data reception from the UART */
		LocalRecieve = UART_voidRecieveDataSync();

		/* Check the received data and perform the corresponding action */
		if (LocalRecieve == '1')
		{
			
			/*Rotate the servo motor connected to channel A to 90 degrees */
			Servo_voidRotateServo(CHANNEL_A, 90);
			
		}
		
		else if (LocalRecieve == '2')
		{
			
			/*Rotate the servo motor connected to channel A to 0 degrees */
			Servo_voidRotateServo(CHANNEL_A, 0);
			
		}
		
		else if (LocalRecieve == '3')
		{
			
			/*Set all the pins of port B to high */
			DIO_u8SetPortValue(DIO_PORTB, 255);
			
		}
		
		else if (LocalRecieve == '4')
		{
			
			/*Set all the pins of port B to low */
			DIO_u8SetPortValue(DIO_PORTB, 0);
			
		}
		
		
	}
	
	
}


/*This Application to sense the change in Temperature*/
void Application(void)

{

	/*Get the reading and map it to Calculate temperature Reading*/
	Local_u16Temb=(500UL*(u32)*Reading)/1024UL;

	/*ADC finishes converting the analog signal to digital*/
	if(Local_u16Temb>=30)	
	{
		
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_HIGH_PIN);
		
	}
	
	else if (Local_u16Temb<30)
	{
		
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN7,DIO_LOW_PIN);
		
	}
	
	ADC_voidStartConversionAsync(ADC_CHANNEL0,Reading);

}
