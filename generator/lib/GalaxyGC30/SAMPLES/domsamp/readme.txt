hey, emacs, take THIS:-*- mode: text; -*-, damnit.

domsamp - a sample showing how to exploit the domain manager, kinda.
-------

  so, yeah, here's a sample which shows off the domain manager.  it's
basically an api fiddler/tester.  here's a rundown on most of the
commands, and exactly what they do:

File Menu:
Open - this doesn't do anything
Save - neither does this
Preferences - brings up the preferences dialog (see below)

Objects Menu:
Add Objects - brings up the add objects dialog
Remove Objects - removes the selected objects from the domain
Connect Objects - connects all of the selected objects together
Disconnect Objects - disconnects the selected objects from any other
		     objects they may be connected to
Hide Objects - hides the selected objects
Show All Objects - the only way to un-hide objects
Scroll To Selected - scrolls to the selected object
Make Unselectable - makes the selected objects unselectable

Domain Menu:
Toggle Virtual - toggles virtual bounds on the domain
Toggle Long - disabled: you can't toggle between long and short
	      domains in the sample yet, but the toggle's state is
	      correct, so this can be used to tell which kind of
	      domain you're currently viewing. 
Toggle Top Left - toggles top-left orientation on the domain
Edit Grid - brings up the edit grid dialog
View Coords - brings up the whacky view coords window

Domain View Menu:
Domain Installed - toggling this disconnects the domain from the
		   domainview
Track Select - track selections in the domainview
Track Drag - track drags in the domainview
Track Auto Scroll - auto scroll the domainview when tracking
Live Selection - allow live selection in the domainview
Select Enclosed - only select objects which are fully enclosed during
		  live selection
Single Selection - only allow one object to be selected at a time
Grabbing Hand - enable grabbing hand scrolling
Drag Prohibited - prohibit object drags in the domainview
Snap To Grid - turn on snap to grid for tracking
Edit Matrix - edit the user matrix for the domainview
Outline All - draw outlines for all objects being dragged
Outline Two - outline the limit rect + the object clicked on for drags
Outline Limit Rect - outline just the limit rect for drags
Outline None - no outline at all for drags
Normal Drag - neither autoscroll nor external drag
Auto Scroll Drag - auto scroll the domainview when dragging
External Drag - drag outside of the domainview
Smart Scrollbars - scrollbars are on when they need to be, and off
		   when they're not needed.
Horizontal Bar - toggle the horz bar (only when smart bars are off)
Vertical Bar - toggle the vertical bar (only when smart bars are off)
Show Grid - show the grid in the background of the domainview
Drag On Unselectables - goofy hack which is no longer needed


Adding Objects:

  selecting add objects lets you add objects to the domain (what a
concept).  there are a few different types of objects you can add:
rectangles (squares, really), triangles, circles, and text.  you can
add as many or as little as you want.  you can specify where they go,
or you can let the placement be randomized within the bounds of the
domain.

Edit Grid Dialog:

  this lets you edit the grid used when dragSnapToGrid is turned on.

View Coords Window:

  selecting "view coords" brings up a rather boring window which shows
you the entire viewable area of the domain, and a black rectangle
representing the domain rect.  scroll around in a domain, and watch
the dancing rectangle in the view coords window.  click anywhere
inside the window to dismiss it.

Edit Matrix Dialog:

  lets you change the user matrix used when drawing.  specifying the
identity matrix (or all empty fields) will remove the user matrix from
the domain view.

Other magical stuff:

  pressing the arrow keys will scroll 20 domain units in the given
direction.

  enjoy.  mail any bug reports to "galaxy-bugs@visix.com" using the
bug template which (theoretically) shipped with this release.
