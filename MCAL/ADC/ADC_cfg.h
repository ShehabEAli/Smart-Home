/************************************************************************/
/*Author      : Shehab Emad										        */
/*File Name   : DIO_cfg.h                                               */
/*Layer       : MCAL												    */
/*Description : This file contains configurable parameters of DIO module*/
/*Date        : 22 March 2023                                           */
/************************************************************************/

/*preprocessor header file guard*/
#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/*options: 1- AREF
 *         2- AVCC
 *         3-INTERNAL_2_56v
 */
#define ADC_u8_REF_SELECTION     AVCC

/*MODES:   1- 8_bit
 *         2- 10_bit
 *
 */
#define ADC_MODE    _10_bits

/*options: 1- DIVIDE_BY_2
 *         2- DIVIDE_BY_4
 *         3- DIVIDE_BY_6
 *         4- DIVIDE_BY_8
 *         5- DIVIDE_BY_16
 *         6- DIVIDE_BY_32
 *         7- DIVIDE_BY_64
 *         8- DIVIDE_BY_128
 */
#define PRESCALER_SELECTION  DIVIDE_BY_128

#endif /* DIO_CFG_H_ */
