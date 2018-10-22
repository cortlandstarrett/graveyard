# makefile for make-based platforms

ALL_TARGETS =  progress$(E)

!include ..\environ

LDLIBS_HOOK =

progressOBJS = main$(O) progress$(O)

progress$(E) : $(progressOBJS)
	$(COMPILE_AND_LINK)$@ $(progressOBJS) $(LDLIBS)

