 
 Description Of 'grid' Sample:

	This sample provides a subclass of listview that does
	synchronized-scrolling between two listviews, as well as the 
        drawing of grid lines between rows.

 	One listview is a content area that will be populated by the
 	user.  The upper listview has column headings that can span 
 	multiple columns underneath it.  Clicking in a column heading
 	will select the appropriate column(s) in the main listview.
 	Rearranging of rows is active.
 
 	The portions of the List Manager used are the vlistviewNOTIFY_SCROLL
 	method, as well as modifying the cellContent drawing procedure.
 
 	Lots of support stuff is also shown.  Note that this program 
  	does not use commands, just simple callbacks.  Had this been
 	a Real Application, commands would have been used.
 
 	The user populates the list by typing things into the 4 textfields,
 	then clicking the "DoIt" button.  Hitting Return is equivalent
 	to clicking DoIt.
 
