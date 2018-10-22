# makefile for make-based platforms

ALL_TARGETS =  linedom$(E)

!include ..\environ

LDLIBS_HOOK =

linedomOBJS = domain$(O) linedom$(O)

linedom$(E) : $(linedomOBJS)
	$(COMPILE_AND_LINK)$@ $(linedomOBJS) $(LDLIBS)

