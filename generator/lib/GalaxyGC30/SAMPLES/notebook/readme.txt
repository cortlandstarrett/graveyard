There are three samples for the notebook:
LISTTEST
OPTTEST
NOTEBK



			LISTTEST
			========
		
files:
------
listtest.c
listtest.vr

description:
------------
The listtest sample is provided to demonstrate how
subclass the tabset so that other objects can be used 
to display the tabs of the pages for a notebook.  This
sample does so with a list.  All of the list items 
represent a tab in a tabset.  The overrides are done in
the _getlisttestClass function.  The pages themselves are
containers that hold various objects.  All of which are loaded
in from resource.


			OPTTEST
			=======

files:
------
opttest.c
opttest.vr

description:
------------
same as listtest above, but the tabset is represented 
by a control option menu.



			NOTEBK
			======

files:
------
notebk.c
notebk.vr

description:
------------
This sample is a demo of all the styles that 
can be set for a notebook.  The user can set the styles
via one of the many control option menus.  It also 
allows the user to page through the notebook to 
help diplay major an minor tabs and page wrapping.
This is a good introduction for new users to get 
familiar with the "parts" of a notebook.
