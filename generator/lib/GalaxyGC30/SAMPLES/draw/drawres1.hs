@subject(DrawDemo Introduction to the Draw Demos)
@keyword(drawdemo)
@keyword(vdraw)
@keyword(vdrawres)
@font(Times 14)


@bold(Introduction to the Draw Demos)


The draw demos are designed to show off some of what can be done with the
Drawing Manager in Galaxy. The drawing routines between the two list programs
are the same; the only difference is behind the scenes in the handling of the
dialogs:


@relmargin(36 36) 
@prefix(-18 *)@link(Source vdraw) creates the dialog on
the fly with API calls and manually moves things around to do resizing
(hence no min size).


@prefix(-18 *)@link(Source vdrawres), on the other hand,
loads its dialog from a resource file (vdrawres.vr), and has springs
and struts defined in it to handle resizing as needed.

@end(prefix)
@end(relmargin)

When you launch either of the draw demos you are presented with a
dialog that contains a drawing area and a collection of buttons,
menus, and text fields. The buttons, menus, and text fields are used
to control what and how the list demo is drawing. The drawing area is
the large area above the copyright notice.


To get context-sensitive help for items in the vdrawres dialog, use
the Tab key in the dialog to move the focus to the item you want help
on. Then press F1 to get help on the item.


Additional information is available on the following topics:


@link(Controls Controls for the Draw Demo)

@link(Source Source Files for the Draw Demos)
@end(font)
