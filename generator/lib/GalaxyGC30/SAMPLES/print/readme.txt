
textprnt -- Text printing sample
------------------------------------------------------------------------------

This sample illustrates how to print multi-page documents using the Print
Manager.  The sample shows how to use ConfirmJob to initiate a printing
routine, and how to format printing for a user-selected paper type.  Using
a basic vtextitem, the sample prints multiple pages by using vprintOpenPage
and ClosePage, and scrolling the textitem.  In addition, the size of the
printed rectangle is adjusted so that only whole lines of text are printed.
The textitem is initially filled with a test pattern that fills several
pages, but the text is editable.  The printing techniques are illustrated
here with a textitem, but they are applicable to any view that must be
printed on multiple pages.

For simplicity, this sample sets up notify functions to link the various
user-interface elements.  In a real application, commands would be the
preferred method of connecting the user-interface and the core code.

To end the demo, choose Exit from the File menu, or close the main dialog.
