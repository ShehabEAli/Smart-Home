/************************************************************************/
/*Author      : Shehab Emad Ali										    */
/*File Name   : DIO_private.h                                           */
/*Layer       : MCAL												    */
/*Description : This file contains private paremeters of DIO module     */
/*Date        : 22 March 2023                                           */
/************************************************************************/

/*preprocessor header file guard*/
#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/****************************************/
/*          DIO Registers               */
/****************************************/
/*PORT A registers                      */
#define PORTA (*(u8 *)(0x3B))
#define DDRA  (*(u8 *)(0x3A))
#define PINA  (*(u8 *)(0x39))

/*PORT B registers                      */
#define PORTB (*(u8 *)(0x38))
#define DDRB  (*(u8 *)(0x37))
#define PINB  (*(u8 *)(0x36))

/*PORT C registers                      */
#define PORTC (*(u8 *)(0x35))
#define DDRC  (*(u8 *)(0x34))
#define PINC  (*(u8 *)(0x33))

/*PORT D registers                      */
#define PORTD (*(u8 *)(0x32))
#define DDRD  (*(u8 *)(0x31))
#define PIND  (*(u8 *)(0x30))

#endif /* DIO_PRIVATE_H_ */
