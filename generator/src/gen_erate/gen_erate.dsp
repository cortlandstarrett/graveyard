# Microsoft Developer Studio Project File - Name="gen_erate" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=gen_erate - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gen_erate.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gen_erate.mak" CFG="gen_erate - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gen_erate - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gen_erate - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gen_erate - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "gen_erate - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gen_erate___Win32_Debug"
# PROP BASE Intermediate_Dir "gen_erate___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "gen_erate___Win32_Debug"
# PROP Intermediate_Dir "gen_erate___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gen_erate - Win32 Release"
# Name "gen_erate - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\action\src\a_bush.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\action\src\a_gfinds.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\al.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\al_rd.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\colToken.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\DLGLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\elm_stub.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\src\gen\gen_force.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\GEN_SOR.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\genal.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\genal_rd.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\intp\gs_actn.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\gen\gs_arch.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\gen\gs_crypt.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\intp\gs_expr.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\intp\gs_func.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\gen\gs_gactn.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idbio\gs_imp.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\intp\gs_selct.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\gen\gs_sorgen.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\intp\gs_stack.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\intp\gs_sub.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\ui\gs_ui.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_ainst.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_c_rop.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_clock.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idbio\i_dainst.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_einst.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_esdi.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_esdii.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_evt.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\gen\i_gainst.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_idb.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_ir_rop.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_obj.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_oinst.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_rel.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_relate.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_roip.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_rop.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_var.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\src\gen\main_gen.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\src\gen_erate\main_gen_erate.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\src\imp\main_imp.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\mcdbms_restore.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\myAST.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\myPanic.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\myTokenBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\noleakAST.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\noleakTok.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_check.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_ckbase.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_ckgendb.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_ckosdb.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_ckudb.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_error.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_msgs.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_swhere.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_symtbl.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\p_tthred.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\schema_gen.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\src\gen\schemgen.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\sim.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\sim_rd.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\sim_rd2.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\sim_rd3.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\sim_rd4.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\sim_rd5.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\SIM_SOR.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\sym.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_bplic.c
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_config.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_date.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_desc.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_dumper.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_env.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_file.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_file_rd.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_fopen.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_getopt.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_id.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_init.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_keyword.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_licens.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_log.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_mc_dbms.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_print.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_string.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_trace.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_tspec.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_udmenu.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_udmenu_rd.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_userid.cc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\action\include\a_bush.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\action\include\a_gfinds.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\action\include\a_schema.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\action\include\a_stmtyp.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\Arg.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\ArgException.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\CmdLine.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\CmdLineInterface.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\CmdLineOutput.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\colToken.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_acthom.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_action.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_ario.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_assrel.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_attr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_battr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_bridge.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_cmprel.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_cnthap.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_cp_im.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_cp_sm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_crttns.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_dataud.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_dattyp.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_dbattr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_dd_sam.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_dd_ver.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_ddasnr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_domain.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_domid.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_drvpth.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_entity.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_evtign.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_exespec.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_im_oam.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_im_ver.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_imasnr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_inhrel.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_invoct.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_itratr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_levt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_mealhm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_mealsm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_moorhm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_moorsm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_nbattr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_nevttn.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_nlevt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_nwsttn.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_object.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_oid.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_oida.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_parm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_pevt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_rattr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_rel.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_schema.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_seme.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_sevt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_sm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_sm_pm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_sm_ver.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_smasnr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_smedi.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_smevt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_smprel.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_smsta.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_ss.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_stubs.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_subsys.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_suppdi.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_suppdt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_synchs.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_tfmr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_tns.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_typdef.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_usrprp.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\d_vertag.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\DLGLexer.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\DocBookOutput.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\GEN_SOR.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\genal.sor
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_actn.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_arch.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_crypt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_evt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_expr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_find.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_func.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_gactn.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_imp.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_obj.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_selct.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_sizes.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_sorsim.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_stack.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_sub.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\gs_ui.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\HelpVisitor.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_ainst.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_attr.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_attr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_c_rop.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_clock.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_einst.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_esdi.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_esdii.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_evt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\src\idb\i_idaref.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_idaref.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_idb.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_ir_rop.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_obj.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_oinst.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_rel.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_relate.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_roip.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_rop.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\gen_sim\include\i_var.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\IgnoreRestVisitor.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_dd.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_im.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_model.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_oam.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_ocm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_sam.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_schema.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_scm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_sm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\m_srm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\makefile
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\mf.pccts
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\MultiArg.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\myAST.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\myPanic.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\mySyn.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\myToken.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\myTokenBuffer.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\n_format.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\noleakAST.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\noleakTok.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\P.cpp
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\P.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_check.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_ckbase.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_ckgendb.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_ckosdb.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_ckudb.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_error.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_msglst.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_msgs.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_swhere.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_symtbl.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_tthred.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\p_types.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\src\parser.dlg
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\platform.str
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\r_cursor.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\r_galp.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\r_lang.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\s_invoct.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\s_simref.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sg_about.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sg_com.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sg_index.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sg_inst.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sg_suprp.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sg_synch.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\SIM_SOR.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\simpleToken.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\StdOutput.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sv_com.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sv_synch.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_about.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_com.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_creat.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_ctrl.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_index.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_inst.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_resrce.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_suprp.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\sw_synch.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\SwitchArg.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\sym.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\parser\include\tokens.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_bplic.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\src\u_cmd.cc
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_cmd.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_config.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_cursor.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_date.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_deldwn.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_desc.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_dumper.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_elm.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_env.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_error.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_file.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_fopen.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_getopt.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_id.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_keyword.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_licens.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_log.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_mc_dbms.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_media.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_print.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_report.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_schema.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_sleep.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_smtptr.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_string.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_sysnet.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_tempdir.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_trace.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_tspec.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_typdef.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_udmenu.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_userid.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\utility\include\u_util.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\UnlabeledMultiArg.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\UnlabeledValueArg.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\v_subcls.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\ValueArg.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\VersionVisitor.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\Visitor.h
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\xtra_includes\w_ctrl.hh
# End Source File
# Begin Source File

SOURCE=.\bp_source\win32\7.1B\main\tclap\XorHandler.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
