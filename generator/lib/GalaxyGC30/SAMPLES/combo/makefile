# makefile for make-based platforms

ALL_TARGETS =  sample$(E) sample1$(E) sample2$(E) sample3$(E) sample4$(E) sample5$(E)

!include ..\environ

LDLIBS_HOOK =

sampleOBJS = main$(O) sample$(O)

sample$(E) : $(sampleOBJS)
	$(COMPILE_AND_LINK)$@ $(sampleOBJS) $(LDLIBS)

LDLIBS_HOOK =

sample1OBJS = main$(O) sample1$(O)

sample1$(E) : $(sample1OBJS)
	$(COMPILE_AND_LINK)$@ $(sample1OBJS) $(LDLIBS)

LDLIBS_HOOK =

sample2OBJS = main$(O) sample2$(O)

sample2$(E) : $(sample2OBJS)
	$(COMPILE_AND_LINK)$@ $(sample2OBJS) $(LDLIBS)

LDLIBS_HOOK =

sample3OBJS = main$(O) sample3$(O)

sample3$(E) : $(sample3OBJS)
	$(COMPILE_AND_LINK)$@ $(sample3OBJS) $(LDLIBS)

LDLIBS_HOOK =

sample4OBJS = main$(O) sample4$(O)

sample4$(E) : $(sample4OBJS)
	$(COMPILE_AND_LINK)$@ $(sample4OBJS) $(LDLIBS)

LDLIBS_HOOK =

sample5OBJS = main$(O) sample5$(O)

sample5$(E) : $(sample5OBJS)
	$(COMPILE_AND_LINK)$@ $(sample5OBJS) $(LDLIBS)

