# makefile for make-based platforms

ALL_TARGETS =  thump$(E)

!include ..\environ

LDLIBS_HOOK =

thumpOBJS = thump$(O) group$(O) pacemake$(O) status$(O)

thump$(E) : $(thumpOBJS)
	$(COMPILE_AND_LINK)$@ $(thumpOBJS) $(LDLIBS)

