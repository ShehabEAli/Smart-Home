

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_cfg.h"

#include "BUZER_interface.h"



/******************************************************************************/
/*************************Functions' implementation****************************/
/******************************************************************************/

void Play_Note(int Frequancy,int Delay_MilliSec)
{
	for(int i=0; i<Delay_MilliSec ; i++)
	{
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN7,DIO_HIGH_PIN);
		_delay_us(Frequancy);
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN7,DIO_LOW_PIN);
		_delay_us(Frequancy);
	}
}
