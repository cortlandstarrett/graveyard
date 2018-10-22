/* $Id: create.h,v 1.3 1997/02/20 18:31:09 david Exp $ */

#ifndef _commtestCreateINCLUDED
#define _commtestCreateINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

void _createUDP(vdialog *parent);
void _createMailbox(vdialog *parent);
void _createTCP(vdialog *parent);
void _createPipe(vdialog *parent);
void _createShm(vdialog *parent);

void _destroyBase(vwindow *window);

#endif
