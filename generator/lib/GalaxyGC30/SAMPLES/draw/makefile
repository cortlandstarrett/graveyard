# makefile for make-based platforms

ALL_TARGETS =  vdraw$(E) vdrawres$(E)

!include ..\environ

LDLIBS_HOOK =

vdrawOBJS = drawboth$(O) vdraw$(O)

vdraw$(E) : $(vdrawOBJS)
	$(COMPILE_AND_LINK)$@ $(vdrawOBJS) $(LDLIBS)

LDLIBS_HOOK =

vdrawresOBJS = drawboth$(O) vdrawres$(O)

vdrawres$(E) : $(vdrawresOBJS)
	$(COMPILE_AND_LINK)$@ $(vdrawresOBJS) $(LDLIBS)

