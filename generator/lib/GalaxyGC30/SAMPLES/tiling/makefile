# makefile for make-based platforms

ALL_TARGETS =  tiling$(E)

!include ..\environ

LDLIBS_HOOK =

tilingOBJS = tiling$(O) grid$(O)

tiling$(E) : $(tilingOBJS)
	$(COMPILE_AND_LINK)$@ $(tilingOBJS) $(LDLIBS)

