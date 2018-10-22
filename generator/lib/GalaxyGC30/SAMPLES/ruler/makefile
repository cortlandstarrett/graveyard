# makefile for make-based platforms

ALL_TARGETS =  ruler$(E)

!include ..\environ

LDLIBS_HOOK =

rulerOBJS = ruler$(O) rultag$(O)

ruler$(E) : $(rulerOBJS)
	$(COMPILE_AND_LINK)$@ $(rulerOBJS) $(LDLIBS)

