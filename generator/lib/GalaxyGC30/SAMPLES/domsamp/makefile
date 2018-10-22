# makefile for make-based platforms

ALL_TARGETS =  domsamp$(E)

!include ..\environ

LDLIBS_HOOK =

domsampOBJS = domsamp$(O) domres$(O) domnames$(O) mydview$(O) prefs$(O)

domsamp$(E) : $(domsampOBJS)
	$(COMPILE_AND_LINK)$@ $(domsampOBJS) $(LDLIBS)

