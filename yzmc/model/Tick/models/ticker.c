/* Copyright 2009-2012 Mentor Graphics Corporation

    All Rights Reserved.

 THIS WORK CONTAINS TRADE SECRET
 AND PROPRIETARY INFORMATION WHICH IS THE
 PROPERTY OF MENTOR GRAPHICS
 CORPORATION OR ITS LICENSORS AND IS
 SUBJECT TO LICENSE TERMS. 
*/
#include <stdio.h>
#include "Rte_co_Ticker.h"

void
ib_Ticker_reset( Rte_Instance self, sint16 resetCount )
{
	sint16*	count;
	count = Rte_Pim_pm_count( self );
	*count = resetCount;
} 

FUNC(void, RTE_APPL_CODE)
ib_Ticker_ru_TickerTimer( Rte_Instance self ) 
{
	sint16* count;
	count = Rte_Pim_pm_count( self );
	(*count)++;
	Rte_Write_pt_TickReq_tick_count( self, *count );
}

FUNC(void, RTE_APPL_CODE)
ib_Ticker_ru_TickResetProv_reset( Rte_Instance self , sint16 resetCount)
{
	ib_Ticker_reset( self, resetCount );
}

FUNC(void, RTE_APPL_CODE)
ib_Ticker_ru_Ticker_Initialize(Rte_Instance self)
{
	ib_Ticker_reset( self, 0 );
}
