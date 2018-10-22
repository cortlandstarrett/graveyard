# makefile for make-based platforms

ALL_TARGETS =  commshow$(E)

!include ..\environ

LDLIBS_HOOK =

commshowOBJS = attrib$(O) control$(O) main$(O) util$(O) commshow$(O) create$(O) notify$(O)

commshow$(E) : $(commshowOBJS)
	$(COMPILE_AND_LINK)$@ $(commshowOBJS) $(LDLIBS)

