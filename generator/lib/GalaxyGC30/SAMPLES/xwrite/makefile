# makefile for make-based platforms

ALL_TARGETS =  xwrite$(E)

!include ..\environ

LDLIBS_HOOK =

xwriteOBJS = mark$(O) pref$(O) search$(O) style$(O) xwrite$(O) document$(O) xctrans$(O) xcflchsr$(O) xtxtview$(O)

xwrite$(E) : $(xwriteOBJS)
	$(COMPILE_AND_LINK)$@ $(xwriteOBJS) $(LDLIBS)

