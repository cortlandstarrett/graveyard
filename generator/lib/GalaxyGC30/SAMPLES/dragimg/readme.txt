dragimg -- "live dragging" an image across a dialog
-----------------------------------------------------
This sample show how to "live drag" an image across a dialog.  It does
so by polling the mouse position, then drawing the image where the
mouse is located.  It "removes" the image from the previous location
by copying in bits from an off-screen bitmap of the virgin unmolested
dialog.

