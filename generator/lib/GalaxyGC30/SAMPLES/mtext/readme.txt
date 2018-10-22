/* $Id: readme,v 1.2 1994/11/22 16:22:49 markd Exp $ */

Welcome to mtext.  mtext (short for 'minitext') is a vdialogItem subclass
that shows how to handle all of the moving parts for a complete, well-behaved
dialog item subclass.  mtext is a small textitem that allows text entry,
simple selection, and attribute settings (like font and colors).  It's not
a full-blown replacement for the vtext family of objects, but can be a fun
toy to fool around with.

Here are the different pieces:

demo.c & mtextdemo.vr:
  a simple demo to show some of the mtext features, ways to change
  dialog item attributes, as well as the dialog item being put into
  different situations for testing (such as in a scrolling container,
  with natural internal struts, load/store, and cloning)

ditem.c:
  code that overrides vdialog*_ITEM_* methods.  Typically code that only
  deals with dialog manager issues (drawing, mouse tracking, focus) lives here

object.c:
  code that overrides vobject* and vinstance* methods.  Typically code that
  only deals with object issues (copy, load, store, attributes, commands)
  lives here

text.c:
  new features specific to minitext (data entry, selection handling,
  setup for command and attribute dictionaries, class table setup) live here

mtext.h:
  exported interface for minitext

privstuff.h:
  private implementation details for minitext that are shared between the
  source files, but aren't proper for exportation

template.h:
  a header file template for laying out your own header files in the Galaxy
  Way.  Not directly used by this sample, but mtext.h was based on this file.

