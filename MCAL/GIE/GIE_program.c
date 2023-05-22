
#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "GIE_cfg.h"
#include "GIE_interface.h"
#include "GIE_private.h"






/******************************************************************************/
/*************************Functions' implementation****************************/
/******************************************************************************/

void GIE_voidEnableGlobalInterrupt(void){
	SET_BIT(SREG,SREG_I);
}
void GIE_voidDisableGlobalInterrupt(void){
	CLR_BIT(SREG,SREG_I);
}
