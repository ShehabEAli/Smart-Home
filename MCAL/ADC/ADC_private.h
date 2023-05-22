/*preprocessor header file guard*/
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/******************************************private macros******************************************/
#define MUX_MASK                      0b11100000

#define PRESCALER_MASK                0b11111000
#define DIVIDE_BY_2                   1
#define DIVIDE_BY_4                   2
#define DIVIDE_BY_8                   3
#define DIVIDE_BY_16                  4
#define DIVIDE_BY_32                  5
#define DIVIDE_BY_64                  6
#define DIVIDE_BY_128                 7

#define _8_bits         0
#define _10_bits        1

#define AVCC            0
#define AREF            1
#define INTERNAL_2_56v  2

/******************************************ADC registers******************************************/

#define ADMUX    *((volatile u8 *)(0x27))       //ADC multiplexer selection register
#define ADMUX_REFS1                   7         //for reference voltage selection bit1
#define ADMUX_REFS0                   6         //for reference voltage selection bit0
#define ADMUX_ADLAR                   5         //for left adjustment


#define ADCSRA   *((volatile u8 *)(0x26))       //ADC control and status registerA
#define ADCSRA_ADEN                   7         //for ADC enable
#define ADCSRA_ADSC                   6         //for ADC start conversion
#define ADCSRA_ADATE                  5         //for ADC auto trigger enable
#define ADCSRA_ADIF                   4         //for ADC interrupt flag
#define ADCSRA_ADIE                   3         //for ADC interrupt enable
#define ADCSRA_ADP2                   2         //for ADC clock Prescaler bit 2
#define ADCSRA_ADP1                   1         //for ADC clock prescaler bit 1
#define ADCSRA_ADP0                   0         //for ADC clock prescaler bit 0

#define ADCH     *((volatile u8 *)(0x25))       //ADC high register
#define ADCL     *((volatile u8 *)(0x24))       //ADC low register
#define ADC     *((volatile u16 *)(0x24))       //ADC register for 10 bits

#define SFIOR    *((volatile u8 *)(0x50))       //ADC special function IO register
#define ADCR     *((volatile u16*)(0x24))       //ADC data register for 10 bit resolution

#define SREG      *((volatile u8 *)(0x5f))
#define SREG_I                        7

#define ADC_u8_BUSY                   0
#define ADC_u8_IDLE                   1


#endif /* ADC_PRIVATE_H_ */
