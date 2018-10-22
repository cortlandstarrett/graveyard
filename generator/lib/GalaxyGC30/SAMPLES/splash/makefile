# makefile for make-based platforms

ALL_TARGETS =  splash$(E)

!include ..\environ

LDLIBS_HOOK =

splashOBJS = splash$(O) app$(O)

splash$(E) : $(splashOBJS)
	$(COMPILE_AND_LINK)$@ $(splashOBJS) $(LDLIBS)

