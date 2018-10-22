# makefile for make-based platforms

ALL_TARGETS =  offscreen$(E)

!include ..\environ

LDLIBS_HOOK =

offscreenOBJS = offscreen$(O) offsamp$(O)

offscreen$(E) : $(offscreenOBJS)
	$(COMPILE_AND_LINK)$@ $(offscreenOBJS) $(LDLIBS)

