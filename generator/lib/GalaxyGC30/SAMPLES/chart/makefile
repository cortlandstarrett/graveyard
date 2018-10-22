# makefile for make-based platforms

ALL_TARGETS =  chart$(E)

!include ..\environ

LDLIBS_HOOK =

chartOBJS = access$(O) attr$(O) canvas$(O) chart$(O) citem$(O) colspot$(O) cview$(O) drawble$(O) linedr$(O) list$(O) listacc$(O) scatdr$(O)

chart$(E) : $(chartOBJS)
	$(COMPILE_AND_LINK)$@ $(chartOBJS) $(LDLIBS)

