# makefile for make-based platforms

ALL_TARGETS =  vlist$(E)

!include ..\environ

LDLIBS_HOOK =

vlistOBJS = vlist$(O) listlife$(O) listapi$(O) listcell$(O) incell$(O)

vlist$(E) : $(vlistOBJS)
	$(COMPILE_AND_LINK)$@ $(vlistOBJS) $(LDLIBS)

