@section(Source About the Source for the Draw Demos)
@parent(DrawDemo)
@keyword(drawdemo)
@keyword(vdraw)
@keyword(vdrawres)
@keyword(source)
@font(Times 14)
@bold(About the Source for the Draw Demos)


The draw demos are basically complete; the only change that might be made
is to cache the last drawing to improve refreshes.


@font(Courier 14) drawdemo.h
@end(font)

This is the header file for both draw demos.


@font(Courier 14) drawboth.c
@end(font)

This holds the common routines for the draw demos. This has most of the
guts since they are the same between the two demos.


@font(Courier 14) vdraw.c
@end(font)

This holds the vdraw-specific routines in it. This has the load procedure
that takes care of creating the dialog from scratch, as well as the notify
procedures that resize the window.


@font(Courier 14) vdrawres.c
@end(font)

This holds the vdrawres-specific routines in it. This is just the load
routine that takes care of fetching the resource for the dialog.


@font(Courier 14) vdrawres1.hs

vdrawres2.hs

vdrawres3.hs
@end(font)

These are the help syntax source files for the vdrawres demo (what you
are now reading). These source files are specified in the help project
file vdrawres.vhp.


@font(Courier 14) vdrawres.rtf
@end(font)

This is the rtf help source file for the vdrawres demo. Use this source
file in a help project file to create on-line help for the vdrawres
demo.


@font(Courier 14) vdrawres.prj
@end(font)

This is the help project file for the vdrawres demo. Use this project
with the help compiler to build the help document set file,
vdrawres.vhs.


@font(Courier 14) vdrawres.vhs
@end(font)

This is the help document set that provides on-line help for the
vdrawres demo. This document set was created from the help project,
vdrawres.vhp. Note that on-line help is only provided for the
vdrawres demo.


@font(Courier 14) makefile
@end(font)

The makefile to build the draw demos.

@end(font)

