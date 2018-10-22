# makefile for make-based platforms

ALL_TARGETS =  micdraw$(E)

!include ..\environ

LDLIBS_HOOK =

micdrawOBJS = micdraw$(O) micdas$(O) canvas$(O) document$(O) object$(O) pattern$(O) pen$(O) pref$(O) text$(O)

micdraw$(E) : $(micdrawOBJS)
	$(COMPILE_AND_LINK)$@ $(micdrawOBJS) $(LDLIBS)

