			COLCHSR
		sample Galaxy application
files:
-----
colchsr.c
colchsr.vr

description:
------------

The colchsr samples is a program demonstrating
the basic uses of a colchsr.  On all platforms 
without a native color chooser the "Galaxy" 
color chooser will be used.  Otherwise calls 
will be made to open the native color chooser, 
unless the -nonativecolorchooser option is 
specified.

The sample itself is a dialog with a box item and 
a menu bar.  The menu bar has menu items for quitting
the sample or setting a color.  When the SetColor... 
menu item is chosen the sample will open the 
appropriate color chooser.  The  color it opens
with is the background color of the box item.  When
the Apply or OK of the color chooser is hit the sample 
shows how to set the background of the box item with the 
color selected in the color chooser.  This is done in 
the apply notify function.  