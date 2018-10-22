# makefile for make-based platforms

ALL_TARGETS =  demo$(E)

!include ..\environ

LDLIBS_HOOK =

demoOBJS = ditem$(O) object$(O) text$(O) demo$(O)

demo$(E) : $(demoOBJS)
	$(COMPILE_AND_LINK)$@ $(demoOBJS) $(LDLIBS)

