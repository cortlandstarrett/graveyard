-------------------------------------------------------------
Toolbar Samples
-------------------------------------------------------------

* toolbar1 **************************************************

Files:      toolbar1.c
Resources:  toolbar1.vr
Executable: toolbar1  

Toolbar sample one shows the basic usage of the toolbar manager.  It
consists of one dialog with a toolbar across the top, integrated into
the dialog's top-level spring solution.

The sample has several buttons and other items on the toolbar.  The
buttons are all vtoolbuttons some of which act as an exclusive group
using a vfield.  (The dialog was entirely created using the Visual
Resource Builder).

There are a couple of options for changing the behaviour of the
toolbar.  Both are under the "Toolbar" menu:

When "Wrapping" option is turned on, making the dialog narrower than
the size of the toolbar will cause some of the items on the toolbar to
wrap around to form a second row of items.

When "Rearrangeable" is turned on, the appropriate mouse and key
combination can be used to rearrange the items on the toolbar.
Certain combinations will just move the items, while others make
copies of the items.

The binding depends upon the look and feel as follows:

         RearrangeMove             RearrangeCopy
         ------------------        --------------------------
Motif    Middle button             Middle button + Ctrl
Windows  Left button + Alt         Left button + Alt + Ctrl
CUA      Left button + Alt         Left button + Alt + Ctrl
Mac      Mouse button + Alt        Mouse button + Alt + Ctrl


The sample also demonstrate the basic use of tooltip and status
help.  Help messages which correspond to particular item tags are
stored in the resource file in top level resource dictionaries called
"Phrase" and "Status" which hold help for tooltips and the statusbar,
respectively.  The help manager automatically looks in those resource
dictionaries to find the help messages.

The toolbar1 sample uses attribute propagation to keep a set of
exclusive menu choices in sync with corresponding vtoolbuttons.


* toolbar2 **************************************************

Files:      toolbar2.c
Resources:  toolbar2.vr
Executable: toolbar2  

The second toolbar sample is identical to the first except that
instead of using attribute propagation to keep the exclusive menu
choices in sync with the corresponding vtoolbuttons, the menu items
are made to observe the buttons' field directly.

