ac -- Animated Cursor Demo
------------------------------------------------------------------------------

This sample demonstrates one method for using animated cursors in a Galaxy
application.  A series of vcursors is displayed in sequence when a timer is
fired.  Many of the attributes can be set within the Visual Resource Builder,
allowing for changes without recompilation.  You can change the images used
for the animation, the desired frames per second, and whether the animation
should bounce or wrap.  A series of function calls is provided to make the 
inclusion of animated cursors easier.

To use the demo, simply press the button labeled "Cursor Tester" to toggle
the animated cursor on and off.  You can quit by using the "Quit" menu item
in the "File" menu.  If you want to try some other cursors, rename any of
the "AnimCursorX" dictionaries to "AnimCursor".  You can also copy these and
add your own images.  Please note that a programmer drew the cursors in this
demo and should not be held responsible for the lack of artistic talent. 

Inside the cursor dictionaries are a boolean named "Bounce" and an integer
named "FPS".  Setting "Bounce" to true will cause the animation to reverse
when it reaches the last frame.  If "Bounce" is false, the animation will
wrap around.  This can be used to reduce the number of frames for an
animation that reverses itself.  Setting "FPS" will set the desired frames
per second for the animation.  Note that this is a desired value and your
real-world mileage will vary.  Rates up to 10fps are reasonable on most
systems, although 4-5fps is all that is usually needed.

