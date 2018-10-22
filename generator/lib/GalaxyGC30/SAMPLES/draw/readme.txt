Welcome to the Galaxy Draw Demos (vdraw & vdrawres)

Using vdraw & vdrawres
======================
The draw demos are designed to show off some of what can be done with the
Drawing Manager in Galaxy.  The drawing routines between the two list programs
are the same; the only differences is behind the scenes in the handling of the
dialogs.  vdraw creates the dialog on the fly with API calls and it manually
moves things round to do resizing (hence no min size).  vdrawres, on the other
hand, loads its dialog from a resource file (vdrawres.vr), and has springs and
struts defined in it to handle resizing as needed.

When you launch either of the draw demos you are presented with a dialog
which contains a drawing area and then a collection of buttons, menus,
and text fields.  The buttons, menus, and text fields are used to control
what and how the list demo is drawing.  The drawing area is the large area
above the copyright notice.

The controls function as follows:

Buttons:

  Start       This will start the draw demo again once it has been
              stopped to allow you to set some of its controls.  You
              can stop it by clicking in its window.

  Change Font This will bring up the font chooser so you can set the
              font that the demo uses when drawing text in the draw
              area.

  Close       This will quit the draw demo.

Check Boxes:

  Fastest     This changes the way the draw demo does it drawing.
              When turned on, in each pass through the drawing cycle
              it will draw all of the objects; when off, it will only
              draw one object on each pass.  This makes a difference
              when clicks are checked to interupt it.

  Once        This will cause the draw demo to automatically stop once
              it has drawn the specified number of objects; otherwise,
              it will clear the draw area and start again.

  Monochrome  This will cause the demo to draw in only black and white
              instead of picking random colors. (Color is dithered on
              1 bit displays).

  X-or Colors Causes the demo to X-or the colors into the drawing area
              instead of just drawing the object in its current color.

  Dashed Lines Causes any lines drawn in the drawing area to be done
               in the predefined dash patterns.

(Option) Menus:

  Object Type This allows you to select the type of object the draw
              demo draws into the draw area.

  Fill Type   Controls how the objects are drawn, whether they are
              filled and/or bordered.  (See the sections in the Galaxy
              documentation on fill and clip methods)

  Line Caps   This controls how the line ends are drawn.  This affects
              the ends of single line segments.  (See vdrawSetLineCap
              in the Galaxy documentation)

  Line Joints This controls how the ends of the lines meet.  To see
              what these do, set the line width to 20, and then let
              the demo draw lines in outline only. (See
              vdrawSetLineJoint in the Galaxy documentation)

Text Fields:

  # Objects   This specifies how many objects to draw on each pass
              before clearing the draw area.

  Rotate Angle The number of degrees to rotate the drawing area.  The
              rotation is from the bottom left corner of the draw
              area.  Anything more than 90 will rotate out of the draw
              area until things are rotated enough to move them back
              into view ( >270 ).
  Scale X & Y This the the scale to zoom in on the drawing.  The X & Y
              scales can be set independently.  Again, the origin is
              in the bottom left corner, and too large of a scale can
              move things out of view.

  Flatness    This effects the tolerance used to draw curves (they are
              done as line segments actually).  Smaller numbers mean
              smoother curves, but more segments.  (See vdrawSetFlat
              in the Galaxy documentation)

  Line Width  This is the width that the lines are drawn, this affects
              the outlines of the object that are being drawn.

  Miter Limit This controls the amount of a miter that is allowed for
              a line joints.  (see vdrawSetMiterLimit in the Galaxy
              Documentation)


About the source
================
The draw demos are basically complete, the only change that might be made
is to cache the last drawing to do refreshes better.

drawdemo.h    This is the header file for both draw demos.

drawboth.c    This holds the common routines for the draw demos. This
              has most all of the guts since they are the same between
              the two demos.

vdraw.c       This holds the vdraw specific routines in it. This has
              the load procedure that takes care of creating the
              dialog from scratch, as well as the notify procedures
              that will take care of resizing the window.

vdrawres.c    This holds the vdrawres specific routines in it. This
              is just the load routine that will take care of fetching
              the resource for the dialog.

vdrawres1.hs
vdrawres2.hs
vdrawres3.hs  These are the help syntax source files for the vdrawres
              demo. These source files are specified in the help
              project file vdrawres.vhp.

vdrawres.rtf  This is the rtf help source file for the vdrawres demo.
              Use this source file in a help project file to create
              on-line help for the vdrawres demo.

vdrawres.prj  This is the help project file for the vdrawres demo. Use
              this project with the help compiler to build the help
              document set file, vdrawres.vhs.

vdrawres.vhs  This is the help document set that provides on-line help
              for the vdrawres demo. This document set was created
              from the help project, vdrawres.vhp. Note that on-line
              help is only provided for the vdrawres demo.

makefile      The makefile to build the draw demos.

