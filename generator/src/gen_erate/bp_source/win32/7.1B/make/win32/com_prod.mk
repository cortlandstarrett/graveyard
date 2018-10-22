#==========================================================================
#
# File:      $RCSfile: com_prod.mk,v $
# Version:   $Revision: 1.11 $
# Modified:  $Date: 2013/01/10 23:43:06 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#

include $(SOURCE_HOME)/make/$(PLATFORM)/prodopts.mk

include $(SOURCE_HOME)/make/$(PLATFORM)/compopts.mk

include $(SOURCE_HOME)/make/dep_prod.mk



scour: clean

clean:
	rm -f $(SCHEMA_DIR)/*app_schema
	rm -f analyst gen_import gen_file sim_ooa support_password
	rm -f analyst.vr sim_ooa.vr
	rm -f $(SH_REPB_DLL) $(SH_TRANS_DLL)

links:
	@echo "make links should be run on a Unix host"

all:	 repb trans rep_scripts analyst gen_erate sim_ooa ptgetenv ptgetshe support_password

.PHONY: repb
repb: $(SH_REPB_DLL)

$(SH_REPB_DEF): $(SOURCE_HOME)/repbin/src/$(SH_REPB_DEF)
	cp $(SOURCE_HOME)/repbin/src/$(SH_REPB_DEF) $(SH_REPB_DEF)

$(SH_REPB_DLL): ptrepbin.obj $(SH_REPB_DEF)
	rm -f $(SH_REPB_DLL)
	rm -f $(SH_REPB_IMPLIB)
	$(LNK) ptrepbin.obj $(MSDEV_LIBS) \
		/dll $(OOA_LIBOPTS) $(LIBDEBUG) \
		/def:$(SH_REPB_DEF) \
		/out:$(SH_REPB_DLL) \
		/implib:$(SH_REPB_IMPLIB)

.PHONY: trans
trans: $(SH_TRANS_DLL)

$(SH_TRANS_DLL): pt_trans.obj
	rm -f $(SH_TRANS_DLL)
	rm -f $(SH_TRANS_IMPLIB)
	$(LNK) pt_trans.obj $(MSDEV_LIBS) \
		/dll $(OOA_LIBOPTS) $(LIBDEBUG) \
		/def:$(SH_TRANS_DEF) \
		/out:$(SH_TRANS_DLL) \
		/implib:$(SH_TRANS_IMPLIB)

.PHONY: mc_dbms
mc_dbms:
	$(MAKE) -C $(MC_DBMS_ROOTDIR) -f $(MC_DBMS_ROOTDIR)/makefile mc_dbms.lib

.PHONY: analyst sim_ooa gen_import gen_file support_password ptgetenv ptgetshe

analyst:			analyst.exe
sim_ooa:			sim_ooa.exe
support_password:	support_password.exe
ptgetenv:			ptgetenv.exe
ptgetshe:			ptgetshe.exe
gen_erate:         gen_erate.exe

analyst.exe:	repb main_ooa.obj schema_ooa.obj ooa_force.obj sim_force.obj \
	$(OOA_LDLIBS)
	rm -f $@
	$(LNK) $(TFLAGS) $(OOA_LIBOPTS) $(LIBDEBUG) -out:$@ \
		main_ooa.obj schema_ooa.obj ooa_force.obj sim_force.obj \
		$(OOA_LDLIBS) \
		$(GALAXY_LIBS) $(MC_DBMS_LIBS) $(MSDEV_LIBS) \
		$(SCHEMA_PATHS) $(LDPATHS)
	- chmod 777 $@
	rm -f analyst.vr
	cp $(SOURCE_HOME)/window/src/resource/analyst.vr analyst.vr


sim_ooa.exe:	trans main_sim.obj schema_sim.obj sim_force.obj gen_force.obj \
	$(SIM_LDLIBS)
	rm -f $@
	$(LNK) $(TFLAGS)  $(SIM_LIBOPTS) $(LIBDEBUG) -out:$@ \
		main_sim.obj schema_sim.obj sim_force.obj gen_force.obj \
		$(SIM_LDLIBS) \
		$(GALAXY_LIBS) $(MC_DBMS_LIBS) $(MSDEV_LIBS) \
		$(SCHEMA_PATHS) $(LDPATHS)
	- chmod 777 $@
	rm -f sim_ooa.vr
	cp $(SOURCE_HOME)/swindow/src/resource/sim_ooa.vr sim_ooa.vr

# i3020.2 removed $(ELM_LIBS) from link line

# i1163 removed the gen_file.exe and gen_import.exe rules, and added the 
#       gen_erate rule

gen_erate.exe: main_imp.obj gen_force.obj trans main_gen.obj main_gen_erate.obj \
	$(GEN_LDLIBS) $(DBIO_LDLIBS)
	rm -f $@
	$(LNK) $(TFLAGS) $(GEN_LIBOPTS) $(LIBDEBUG) -out:$@ \
		main_gen.obj gen_force.obj main_imp.obj main_gen_erate.obj \
		$(GEN_LDLIBS) $(DBIO_LDLIBS) \
		$(GALAXY_LIBS) $(MC_DBMS_LIBS) $(MSDEV_LIBS) \
		$(SCHEMA_PATHS) $(LDPATHS)
	- chmod 777 $@
	
support_password.exe:	main_pas.obj
	rm -f $@
	$(LNK) $(TFLAGS) $(PAS_LIBOPTS) $(LIBDEBUG) -out:$@ \
		main_pas.obj \
		$(GALAXY_LIBS) $(MSDEV_LIBS) \
		$(LDPATHS)
	- chmod 777 $@


ptgetenv.exe:	main_env.obj
	rm -f $@
	$(LNK) $(TFLAGS) $(ENV_LIBOPTS) $(LIBDEBUG) -out:$@ \
		main_env.obj \
		$(MSDEV_LIBS)
	- chmod 777 $@

ptgetshe.exe:	main_she.obj
	rm -f $@
	$(LNK) $(TFLAGS) $(ENV_LIBOPTS) $(LIBDEBUG) -out:$@ \
		main_she.obj \
		$(MSDEV_LIBS)
	- chmod 777 $@


arch_crypt.exe:	main_crypt.obj gs_crypt.obj
	rm -f $@
	$(LNK) $(TFLAGS) $(LIBDEBUG) -out:$@ \
		main_crypt.obj gs_crypt.obj \
		$(MSDEV_LIBS) $(LDPATHS)
	strip $@
	- chmod 777 $@

arch_decrypt.exe:	main_decry.obj gs_crypt.obj
	rm -f $@
	$(LNK) $(TFLAGS) $(LIBDEBUG) -out:$@ \
		main_decry.obj gs_crypt.obj \
		$(MSDEV_LIBS) $(LDPATHS)
	strip $@
	- chmod 777 $@

arch_cmpcr.exe:	main_cmpcr.obj gs_crypt.obj
	rm -f $@
	$(LNK) $(TFLAGS) $(LIBDEBUG) -out:$@ \
		main_cmpcr.obj gs_crypt.obj \
		$(MSDEV_LIBS) $(LDPATHS)
	strip $@
	- chmod 777 $@


include $(SOURCE_HOME)/make/$(PLATFORM)/rep_scripts.mk

#
# Formatting information for emacs
#
# Local Variables:
# tab-width:2
# End:
#
