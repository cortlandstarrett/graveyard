# makefile for make-based platforms

ALL_TARGETS =  boxt$(E) isniffer$(E)

!include ..\environ

LDLIBS_HOOK =

boxtOBJS = names$(O) statitem$(O) boxt$(O)

boxt$(E) : $(boxtOBJS)
	$(COMPILE_AND_LINK)$@ $(boxtOBJS) $(LDLIBS)

LDLIBS_HOOK =

isnifferOBJS = iter$(O) llist$(O) array$(O) stack$(O) names$(O) statitem$(O) statwin$(O) com$(O) geticons$(O) help$(O) utils$(O) spin$(O) iman$(O) viewedit$(O) view$(O) viewio$(O) viewedtr$(O) snoop$(O) prefs$(O) isniffer$(O)

isniffer$(E) : $(isnifferOBJS)
	$(COMPILE_AND_LINK)$@ $(isnifferOBJS) $(LDLIBS)

