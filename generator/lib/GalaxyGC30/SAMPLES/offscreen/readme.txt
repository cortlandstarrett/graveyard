-------------------------------------------------------------
 Offscreen Sample
-------------------------------------------------------------

Files:       offscreen.c
             offscreen.h
             offsamp.c
Resources:   offscreen.vr
Excutable:   offscreen


The offscren sample shows how to make a dialog subclass which repaints
using an offscreen buffer image to reduce flicker.  This is really
only an issue on platforms with "Full Drag" such as Microsoft
Windows 95 and NT.  With full drag turned on, dialogs are repainted
repeatedly as they are resized by a user, which can lead to very
flashy results as the entire dialog is first erased with the backgroud
color and then all the items are redrawn, then they are erased again,
and then redraw -- and so on ad infinitum.

The files offscreen.c and offscreen.h implement a reusable subclass of
vdialog called OffscreenDialog which acts just like a normal dialog
except it uses offscreen drawing to update in response to resize
events. 

The file offsamp.c is a simple galaxy program with a main() that uses
the offscreen dialog class.

When the sample starts, two dialogs are opened up, one is an
OffscreenDialog and the other is a plain vdialog.  Resize the dialogs
to see the difference offscreen updating can make.

NOTE:  Most windowing systems -- all but Windows -- do not implement
full drag!  On these platforms the OffscreenDialog class essentially 
reduces to a copy of the vdialog class.  A notice will pop up if you
are running on one of these platforms.

FURTHER NOTE: Full drag can be turned on and off even on Windows, so
if you do not see a difference when you resize the two dialogs, you
may not have full drag turned on.  (Or you may just have a really,
really fast computer with a really, really fast video card you lucky
sun of a gun.)
