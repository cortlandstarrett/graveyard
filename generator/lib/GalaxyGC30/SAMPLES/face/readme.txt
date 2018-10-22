
                                Galaxy Samples
                              face, face2, face3


The three face samples build on each other. face is the simplest,
face3 is a little more involved, and face2 is more involved still.
They all illustrate how to associate application code with interface items
using selector commands (instead of notify functions). They also illustrate
how to do subclassing and how to use some of the drawing manager 
functionality.

face
----
This demo consists of a single dialog which contains a "Happy Face"
dialog item.  This face item is a subclass of vdialogItem and knows
how to draw itself as a happy face.  Different parts of the face can
be drawn or erased by picking from the "Face Parts" menu.  The menu
item titles change dynamically depending on whether each face part can
be drawn or erased.  The menu items use selector commands to map to
application code.

To end the demo, choose "Quit" from the File menu.


face2
-----
This demo builds upon the face sample to add four named attributes (or
"instance variables") to the face item. All method overrides needed to 
implement these four new named attributes correctly for the face item
are provided. This program is also an illustration of how to propagate named
attributes correctly to multiple user interface items in a dialog. There
are nine face items in the dialog.

To end the demo, choose "Quit" from the File menu.

face3
-----
This demo is identical to face2 except that instead of adding four named 
attributes to the face item, it adds four class variables. This approach
makes sense because the state information in this example does not vary 
amoung particular instances of the face item.

To end the demo, choose "Quit" from the File menu.



Things to do better in future versions of these samples:
--------------------------------------------------------

-- The menu item titles should really be changed through use of a vname_Title 
   attribute dictionary, not by direct calls to vmenuSetItemTitle.
