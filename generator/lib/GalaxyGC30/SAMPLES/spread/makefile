# makefile for make-based platforms

ALL_TARGETS =  spread$(E)

!include ..\environ

LDLIBS_HOOK =

spreadOBJS = spread$(O) spcom$(O) spkey$(O) spnote$(O) spview$(O)

spread$(E) : $(spreadOBJS)
	$(COMPILE_AND_LINK)$@ $(spreadOBJS) $(LDLIBS)

