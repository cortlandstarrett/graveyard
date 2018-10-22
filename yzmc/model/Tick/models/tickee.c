/* Copyright 2009-2012 Mentor Graphics Corporation

    All Rights Reserved.

 THIS WORK CONTAINS TRADE SECRET
 AND PROPRIETARY INFORMATION WHICH IS THE
 PROPERTY OF MENTOR GRAPHICS
 CORPORATION OR ITS LICENSORS AND IS
 SUBJECT TO LICENSE TERMS. 
*/
#include <stdio.h>
#include "Rte_co_Tickee.h"

FUNC(void, RTE_APPL_CODE)
ib_Tickee_ru_TickProv(Rte_Instance self)
{
	sint16		count;
	sint16*		clamp;

	Rte_Read_pt_TickProv_tick_count( self, &count );

	clamp = Rte_Pim_pm_clamp( self );
	if( count >= *clamp ) 
	{
		Rte_Call_pt_TickResetReq_reset_op_reset( self, 1 );
	}
}

FUNC(void, RTE_APPL_CODE)
ib_Tickee_ru_Tickee_Initialize(Rte_Instance self)
{
	sint16*	clamp;
	clamp = Rte_Pim_pm_clamp( self );
	*clamp = 7;	
}
