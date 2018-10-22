scalerot -- Scaling and rotation demo
------------------------------------------------------------------------------

This sample demonstrates some of the drawing capabilities provided by Galaxy.
An image is scaled, rotated, and translated using the Drawing Manager, with
the former two under the user's control.  Sliders can be used to rotate and
scale the image and commands are available for scaling and rotating over a
range.  

A subclass of a dialog item is used as a "canvas" for displaying the rotated
and scaled image, which is rendered offscreen for smoothness.  The slider on
the left side of the canvas controls scaling between 0.01 and 5.0, with 1.0
being the default.  Below the canvas is the slider which controls rotation
between -180 and 180, with 0 being the default.  These values, as well as
the image to be used, can be changed using the Visual Resource Builder.

Three commands are available for zooming and rotating through a range, and
for quitting the application.  These can be accessed with buttons below the
canvas or from the menu items in the menu bar.  Zooming ranges from the
current size down to 1/10 the current size and returns.  Rotation is a full
360 degrees counterclockwise with 15 increments.

