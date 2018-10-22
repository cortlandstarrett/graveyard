# makefile for make-based platforms

ALL_TARGETS =  boinker$(E)

!include ..\environ

LDLIBS_HOOK =

boinkerOBJS = boinker$(O) boink$(O) dtask$(O) etask$(O) ttask$(O)

boinker$(E) : $(boinkerOBJS)
	$(COMPILE_AND_LINK)$@ $(boinkerOBJS) $(LDLIBS)

