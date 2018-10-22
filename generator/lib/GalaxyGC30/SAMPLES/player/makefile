# makefile for make-based platforms

ALL_TARGETS =  player$(E)

!include ..\environ

LDLIBS_HOOK =

playerOBJS = player$(O) activemovie$(O) realaudio$(O)

player$(E) : $(playerOBJS)
	$(COMPILE_AND_LINK)$@ $(playerOBJS) $(LDLIBS)

