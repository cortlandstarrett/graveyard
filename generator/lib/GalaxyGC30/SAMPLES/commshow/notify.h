/* $Id: notify.h,v 1.3 1997/02/20 18:31:09 david Exp $ */

#ifndef _commtestNotifyINCLUDED
#define _commtestNotifyINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vcommINCLUDED
#include vcommHEADER
#endif

void _notifyBase(vcommBase *base, vcommEvent *event);
void _notifyUpdateState(vcommBase *base);

#endif
