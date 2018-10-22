/* $Id: vctlchsr.h,v 1.4 1996/06/17 15:24:48 gary Exp $ */

#ifndef vctlchsrINCLUDED
#define vctlchsrINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef vstrINCLUDED
#include vstrHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef voleINCLUDED
#include voleHEADER
#endif

#if (vportOLE)
#ifndef  vmswhdrsINCLUDED
#include vmswhdrsHEADER
#endif
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * Class and object definitions
 */
typedef struct voleCntlchsr {
	vconfirm	confirm;
	vlistitem	*m_cntllist;
	CLSID		m_clsid;
	vdict		*m_dict;
	vwindow		*m_parent;
} voleCntlchsr;

#define voleCntlchsrCLASS(SUPER, CHSR, HOOK) \
	vconfirmCLASS(SUPER, CHSR, HOOK)

typedef struct voleCntlchsrClass voleCntlchsrClass;

struct voleCntlchsrClass {
	voleCntlchsrCLASS(voleCntlchsrClass, voleCntlchsr, vconfirmHookProc);
};

/*
 * Forward declarations
 */
voleCntlchsrClass *voleGetDefaultCntlchsrClass(void);

voleCntlchsrClass *voleGetCntlchsrClass(voleCntlchsr *chsr);

voleCntlchsr *voleCreateCntlchsr(void);

void voleDestroyCntlchsr(voleCntlchsr *chsr);

CLSID voleGetCntlchsrCLSID(voleCntlchsr *chsr);

vconfirm *voleGetCntlchsrConfirm(voleCntlchsr *chsr);

vwindow *voleGetCntlchsrParent(voleCntlchsr *chsr);

void voleSetCntlchsrParent(voleCntlchsr *chsr, vwindow *window);

const vname *voleCntlchsrProcess(voleCntlchsr *chsr);

/*
 * Macro implementations
 */
#define voleGetCntlchsrClass(c) ((voleCntlchsrClass *) \
	vdialogGetClass(vconfirmGetDialog(voleCntlchsrGetConfirm(c)))

#define voleCreateCntlchsr() \
	((voleCntlchsr *) vconfirmCreateOfClass( \
	(vconfirmClass *) voleGetDefaultCntlchsrClass()))

#define voleDestroyCntlchsr(c) vconfirmDestroy(voleGetCntlchsrConfirm(c))

#define voleGetCntlchsrCLSID(c) ((c)->m_clsid)

#define voleGetCntlchsrConfirm(c) (vportBASE_OBJECT((c), confirm))

#define voleGetCntlchsrParent(c) ((c)->m_parent)

#define voleSetCntlchsrParent(c, w) ((c)->m_parent = w)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vctlchsrINCLUDED */
