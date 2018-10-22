# makefile for make-based platforms

ALL_TARGETS =  master$(E) slave$(E)

!include ..\environ

LDLIBS_HOOK =

masterOBJS = master$(O) utility$(O)

master$(E) : $(masterOBJS)
	$(COMPILE_AND_LINK)$@ $(masterOBJS) $(LDLIBS)

LDLIBS_HOOK =

slaveOBJS = slave$(O) utility$(O)

slave$(E) : $(slaveOBJS)
	$(COMPILE_AND_LINK)$@ $(slaveOBJS) $(LDLIBS)

