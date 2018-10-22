/* $Id: vgalaxy.h,v 1.53 1997/11/17 23:40:49 gregt Exp $ */

/*
 * Galaxy Master Header
 *
 * This header demonstrates the recommended order of inclusion of all
 * Galaxy header files.  This order is based upon precedence.
 * This will reduce the maximum depth of inclusion so that stupid CPPs will
 * be able to handle Galaxy compilations.
 */

#ifndef vgalaxyINCLUDED
#define vgalaxyINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif


/*
 * ANSI headers
 */

#ifndef  vstddefINCLUDED
#include vstddefHEADER
#endif

#ifndef  vstdargINCLUDED
#include vstdargHEADER
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vlimitsINCLUDED
#include vlimitsHEADER
#endif

#ifndef  vctypeINCLUDED
#include vctypeHEADER
#endif

#ifndef  verrnoINCLUDED
#include verrnoHEADER
#endif

#ifndef  vstringINCLUDED
#include vstringHEADER
#endif

#ifndef  vmathINCLUDED
#include vmathHEADER
#endif

#ifndef  vlocaleINCLUDED
#include vlocaleHEADER
#endif

#ifndef  vsignalINCLUDED
#include vsignalHEADER
#endif

#ifndef  vsetjmpINCLUDED
#include vsetjmpHEADER
#endif

#ifndef  vfloatINCLUDED
#include vfloatHEADER
#endif

#ifndef  vtimeINCLUDED
#include vtimeHEADER
#endif


/*
 * POSIX headers
 */

#ifndef  vsystypesINCLUDED
#include vsystypesHEADER
#endif

#ifndef  vsysstatINCLUDED
#include vsysstatHEADER
#endif

#ifndef  vdirentINCLUDED
#include vdirentHEADER
#endif

#ifndef  vunistdINCLUDED
#include vunistdHEADER
#endif

#ifndef  vfcntlINCLUDED
#include vfcntlHEADER
#endif

#ifndef  vutimeINCLUDED
#include vutimeHEADER
#endif

#ifndef  vgrpINCLUDED
#include vgrpHEADER
#endif

#ifndef  vpwdINCLUDED
#include vpwdHEADER
#endif


/*
 * Unix headers
 */

#ifndef  vsystimeINCLUDED
#include vsystimeHEADER
#endif

#ifndef  vsysfileINCLUDED
#include vsysfileHEADER
#endif

#ifndef  vsysdirINCLUDED
#include vsysdirHEADER
#endif


/*
 * Galaxy headers
 */

#ifndef  vgalaxyBuildNumberINCLUDED
#include vgalaxyBuildNumberHEADER
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vstatusINCLUDED
#include vstatusHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

#ifndef  vconditionINCLUDED
#include vconditionHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vlonglongINCLUDED
#include vlonglongHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  vtransformINCLUDED
#include vtransformHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vevent2INCLUDED
#include vevent2HEADER
#endif

#ifndef  vtimerINCLUDED
#include vtimerHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vbtreeINCLUDED
#include vbtreeHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vresolverINCLUDED
#include vresolverHEADER
#endif

#ifndef  vinstallINCLUDED
#include vinstallHEADER
#endif

#ifndef  vinstINCLUDED
#include vinstHEADER
#endif

#ifndef  vcommINCLUDED
#include vcommHEADER
#endif

#ifndef  vregexpINCLUDED
#include vregexpHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vdateINCLUDED
#include vdateHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vclipboardINCLUDED
#include vclipboardHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  viteratorINCLUDED
#include viteratorHEADER
#endif

#ifndef  vmoduleINCLUDED
#include vmoduleHEADER
#endif

#ifndef  vprocessINCLUDED
#include vprocessHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif

#ifndef  voccurrenceINCLUDED
#include voccurrenceHEADER
#endif

#ifndef  vobserverINCLUDED
#include vobserverHEADER
#endif

#ifndef  vsequenceINCLUDED
#include vsequenceHEADER
#endif

#ifndef  vmappingINCLUDED
#include vmappingHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vundoINCLUDED
#include vundoHEADER
#endif

#ifndef  vurlINCLUDED
#include vurlHEADER
#endif

#ifndef  vwebbrowseINCLUDED
#include vwebbrowseHEADER
#endif

#ifndef  vhelprequestINCLUDED
#include vhelprequestHEADER
#endif

#ifndef  vhelpdisplayINCLUDED
#include vhelpdisplayHEADER
#endif

#ifndef  vhelplocatorINCLUDED
#include vhelplocatorHEADER
#endif

#ifndef  vhelpobjectINCLUDED
#include vhelpobjectHEADER
#endif

#ifndef  vhelpregistryINCLUDED
#include vhelpregistryHEADER
#endif

#ifndef  vhelprefINCLUDED
#include vhelprefHEADER
#endif

#ifndef  vhelpstatusINCLUDED
#include vhelpstatusHEADER
#endif

#ifndef  vhelptooltipINCLUDED
#include vhelptooltipHEADER
#endif

#ifndef  vhelptextINCLUDED
#include vhelptextHEADER
#endif

#ifndef  vhelptextlocatorINCLUDED
#include vhelptextlocatorHEADER
#endif

#ifndef  vhelpreflocatorINCLUDED
#include vhelpreflocatorHEADER
#endif

#ifndef  vhelphtmllocatorINCLUDED
#include vhelphtmllocatorHEADER
#endif

#ifndef  vhelphypertextINCLUDED
#include vhelphypertextHEADER
#endif

#ifndef  vhelpwinhelpINCLUDED
#include vhelpwinhelpHEADER
#endif

#ifndef  vhelpnetscapeINCLUDED
#include vhelpnetscapeHEADER
#endif

#ifndef  vhelpexplorerINCLUDED
#include vhelpexplorerHEADER
#endif

#ifndef  vhelpdefaultINCLUDED
#include vhelpdefaultHEADER
#endif

#ifndef  vhelpINCLUDED
#include vhelpHEADER
#endif

#ifndef  vbufferINCLUDED
#include vbufferHEADER
#endif

#ifndef  vpixmapINCLUDED
#include vpixmapHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vfontspecINCLUDED
#include vfontspecHEADER
#endif

#ifndef  vdatatagINCLUDED
#include vdatatagHEADER
#endif

#ifndef  vdelegatorINCLUDED
#include vdelegatorHEADER
#endif

#ifndef  vscrapINCLUDED
#include vscrapHEADER
#endif

#ifndef  vsignatureINCLUDED
#include vsignatureHEADER
#endif

#ifndef  vtextselectionINCLUDED
#include vtextselectionHEADER
#endif

#ifndef  vtextINCLUDED
#include vtextHEADER
#endif

#ifndef  vtextmarkerINCLUDED
#include vtextmarkerHEADER
#endif

#ifndef  vlistselectionINCLUDED
#include vlistselectionHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vliststrINCLUDED
#include vliststrHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vthreadINCLUDED
#include vthreadHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  vdrawrectsetINCLUDED
#include vdrawrectsetHEADER
#endif

#ifndef  vdrawpenINCLUDED
#include vdrawpenHEADER
#endif

#ifndef  vdrawpathINCLUDED
#include vdrawpathHEADER
#endif

#ifndef  vdrawcontextINCLUDED
#include vdrawcontextHEADER
#endif

#ifndef  vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef  vspringINCLUDED
#include vspringHEADER
#endif

#ifndef  vspringdomINCLUDED
#include vspringdomHEADER
#endif

#ifndef  vprintINCLUDED
#include vprintHEADER
#endif

#ifndef  vinputINCLUDED
#include vinputHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vdropsiteINCLUDED
#include vdropsiteHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vlistsizeINCLUDED
#include vlistsizeHEADER
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef  vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef  vfieldINCLUDED
#include vfieldHEADER
#endif

#ifndef  vformatINCLUDED
#include vformatHEADER
#endif

#ifndef  vstritemINCLUDED
#include vstritemHEADER
#endif

#ifndef  vboolitemINCLUDED
#include vboolitemHEADER
#endif

#ifndef  vlongitemINCLUDED
#include vlongitemHEADER
#endif

#ifndef  vulongitemINCLUDED
#include vulongitemHEADER
#endif

#ifndef  vdoubleitemINCLUDED
#include vdoubleitemHEADER
#endif

#ifndef  vmaskitemINCLUDED
#include vmaskitemHEADER
#endif

#ifndef  vpwditemINCLUDED
#include vpwditemHEADER
#endif

#ifndef  vdateitemINCLUDED
#include vdateitemHEADER
#endif

#ifndef  vtypeitemINCLUDED
#include vtypeditemHEADER
#endif

#ifndef  vpaletteINCLUDED
#include vpaletteHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#ifndef  vdomainitemINCLUDED
#include vdomainitemHEADER
#endif

#ifndef  viconviewINCLUDED
#include viconviewHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef  vnoticeINCLUDED
#include vnoticeHEADER
#endif

#ifndef  vkeyitemINCLUDED
#include vkeyitemHEADER
#endif

#ifndef  vtextrulerINCLUDED
#include vtextrulerHEADER
#endif

#ifndef  vrulerINCLUDED
#include vrulerHEADER
#endif

#ifndef  vmainviewINCLUDED
#include vmainviewHEADER
#endif

#ifndef  vcomboINCLUDED
#include vcomboHEADER
#endif

#ifndef  vcomboboxINCLUDED
#include vcomboboxHEADER
#endif

#ifndef  vspinnerINCLUDED
#include vspinnerHEADER
#endif

#ifndef  vdragINCLUDED
#include vdragHEADER
#endif

#ifndef  vnotebookINCLUDED
#include vnotebookHEADER
#endif

#ifndef  vstatusbarINCLUDED
#include vstatusbarHEADER
#endif

#ifndef  vdockerINCLUDED
#include vdockerHEADER
#endif

#ifndef  vdockINCLUDED
#include vdockHEADER
#endif

#ifndef  vdockitemINCLUDED
#include vdockitemHEADER
#endif

#ifndef  vdockcontainerINCLUDED
#include vdockcontainerHEADER
#endif

#ifndef  vformINCLUDED
#include vformHEADER
#endif

#ifndef  vtoolbuttonINCLUDED
#include vtoolbuttonHEADER
#endif

#ifndef  vtoolchangerINCLUDED
#include vtoolchangerHEADER
#endif

#ifndef  vtoolbarINCLUDED
#include vtoolbarHEADER
#endif

#ifndef  voleINCLUDED
#include voleHEADER
#endif

#ifndef  volevariantINCLUDED
#include volevariantHEADER
#endif

#ifndef  volesiteINCLUDED
#include volesiteHEADER
#endif

#ifndef  vtreeINCLUDED
#include vtreeHEADER
#endif

#ifndef  vtreelistINCLUDED
#include vtreelistHEADER
#endif

#ifndef  vimageedtrINCLUDED
#include vimageedtrHEADER
#endif

#ifndef  vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef  vfontchsrINCLUDED
#include vfontchsrHEADER
#endif

#ifndef  vfilechsrINCLUDED
#include vfilechsrHEADER
#endif

#ifndef  vstylechsrINCLUDED
#include vstylechsrHEADER
#endif

#ifndef  vstrchsrINCLUDED
#include vstrchsrHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#endif /* #ifndef vgalaxyINCLUDED */

