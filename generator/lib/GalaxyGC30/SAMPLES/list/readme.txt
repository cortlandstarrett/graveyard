Welcome to the Galaxy List Manager Demo (vlist)

Using vlist
==============
When you first launch vlist, you're greeted with a dialog with 7 buttons:
API Fiddler, Life, Spreadsheet, In-cell Editing, About, Stock List, and Quit.
API Fiddler brings up a dialog which lets you experiment ("fiddle")
with different aspects of the API.  Life is a simple version of John
Conway's "Life" mathematical amusement.  In-cell Editing brings up a
dialog that shows an experimental list subclass that performs text
editing within the list.  About brings up an About box with obligatory
legalese.  Quit exits the application.  Spreadsheet and Stock List
are currently unimplemented, but will be a simple spreadsheet and a
stock feed simulator, respectively.

Using API Fiddler
-----------------
The window is divided into 3 parts: The menu bar at the top, the
scrolling listview in the middle, and a message strip at the bottom.
Generally, when you perform an action in the list or with the menus,
the API call being used is shown in the message strip.  The API
fiddler gives you access to most of the listview features so you can
see the interaction of the different attributes, as well as see some
of the stuff the list manager is capable of.

API fiddler menus:

File->Close -- Closes the API Fiddler window.

Attributes menu:
Set Font -- Brings up a font chooser that lets you set the font
    the list uses to draw the cells.
Set Foreground Color -- Brings up a color chooser that lets you set
    the foreground drawing Color.
Set Background Color -- Brings up a color chooser that lets you set
    the background drawing Color.
Border -- Toggles the border.
Disable -- Toggles the disabled state of the listview (this causes 
    it to draw with disabled colors.)
Row Rearrange -- Toggles rearranging-of-rows mode.
Column Rearrange -- Toggles rearranging-of-columns mode.
    Use the drag button (middle button in Motif, left button in OpenLook) 
    to do the rearranging.  Bug: Don't turn these on at the same time -- 
    the menu will get out of sync with the listview.
Selection Sense -- Toggles selection sense.  (Adjust-click on a 
    selected cell, dragging will unselect cells)
Drawing Selection -- Toggles selection of individual cells the pointer 
    passes over (vs. sweeping out a rectangle).
Keyboard Selection -- Toggles "type to select" mode.
Keyboard Traversal -- Toggles whether to use Motif keyboard traversal.
Keyboard Traversal Wrap -- Toggles state of pinning the keyboard .
    traversal cursor when trying to move past the bounds of the list.

Operations menu:
Remove Row -- Removes Selected Rows.
Remove Column -- Removes Selected Columns.
Insert Row -- Inserts empty rows before each selected row.
Insert Column -- Insert empty columns before each selected column.
Swap Rows -- Swaps selected rows.  (Exchanges two rows, plays follow-the-
    leader with 3 or more.  no-op for one row.)
Swap Columns -- Swaps selected columns.
Set Row Count -- Brings up a dialog that lets you type in a new row count.
    New rows will be empty.  If you set a row count to be smaller than the 
    current number of rows, the list will be truncated.
Set Column Count -- Brings up a dialog that lets you type in a new column 
    count.
Get Row Count -- Prints the current row count in the message area.
Get Column Count -- Prints the current column count in the message area.
Set Cell Value -- Brings up a dialog that lets you type in a new cell value. 
    All selected cells will be changed when you click this dialog's Apply 
    button.

Scroll menu:
Scroll to Selection -- Scrolls the selection into view if it's currently 
    out of view.
Scroll to Focus -- Scrolls so the keyboard focus cursor is visible.
Scroll Home -- Scrolls to cell (0,0).
Scroll End -- Scrolls to the bottom-right cell.
Scroll Left -- Scrolls the list one cell to the left.
Scroll Right -- Scrolls the list one cell to the right.
Scroll Up -- Scrolls the list one cell up.
Scroll Down -- Assures world peace.
Scroll All Around -- Scrolls around randomly for awhile.
Autoscroll -- Toggles autoscroll-during-selection state.
Grabbing Hand -- Toggles grabbing hand mode. There is also a "spring-loaded" 
    grabbing hand mode: control-middle-button click in the list will do 
    scrolling.
Horizontal Scrollbar -- Toggles the state of the horizontal scrollbar.
Vertical Scrollbar -- Toggles the state of the vertical scrollbar.
Set Scrollbar Margin -- Brings up a dialog that lets you set the space 
    between the scrollbars and the list border.

Selection menu:
Select All -- Selects all cells.
Unselect All -- Unselects all cells.
Select Randomly -- Selects a couple of random ranges of cells.
Unselect Randomly -- Same as Select Randomly, but different.
Free Selection -- Turn on free selection select method (any arbitrary cell 
   can be selected).
Rectangular Selection -- Turn on rectangular selection (only rectangular 
   ranges can be selected).
One-only Selection -- 0 or 1 cells can be selected.
No Selection -- Nothing can be selected.
At Least One Selection -- One cell must be selected at all times.
Immutable Selection -- Selection doesn't get altered during row/column 
    operations.
Extend Row Selection -- Turns on selection extension for rows.  (If you
    click on a cell, the entire row gets selected.)
Extend Column Selection -- Turns on selection extension for columns.  Both 
    row and column selection extension may be active at the same time.
No Selection Filter -- Does not filter selections being made.
Even/Odd Selection filter -- Removes cells whose row & column sum is even.
Prime Row/Column Selection Filter -- Removes cells whose row & column sum 
    is prime.
Count Selected Cells -- Puts the selected cell count in the message area.
Iterate Selected Cells -- Iterates over the selected cells and puts their 
    value in the message area.

Size menu:
Set Row Height -- Puts up a dialog that lets you type in a new row height. 
    When you click Apply, all selected rows get that row height.
Set Column Width -- Puts up a dialog that lets you type in a new column width.
Get Row Height -- Puts the row height of the selected row in the message area.
    If more than one row is selected, an arbitrary row height is shown.
Get Column Width -- Puts the column width of the selected column in the 
    message area.
Random Row Heights -- Sets the row heights to random values.
Random Column Widths -- Sets the column widths to random values.
Short Rows -- Makes all of the rows short.
Narrow Columns -- Makes all of the columns narrow.
Tall Rows -- Makes all of the rows tall.
Wide Columns -- Makes all of the columns wide.

Cell Menu:
Draw as Text -- Draws strings in the list.
Draw Image -- Draws images in the list.
    (These are actually two different lists that get swapped underneath the 
    listview.  Some operations (like Set Cell Value) will probably crash 
    with image view.)
Horizontal Grid Lines -- Toggle drawing of routed lines between rows.
Vertical Grid Lines -- Toggle drawing of routed lines between columns.

Using In-Cell Editing
---------------------
The list in the window is a grid similar to the API fiddler.  Click on a cell 
to edit its contents.  Type the new value into the text field.  Click outside
of the text field to save the editing values.  Dragging in the list will 
select ranges of cells as expected.

In-Cell Editing menus:
File->Close -- Closes the window.
Action->Accept Editing -- Saves the editing value in the list and removes 
    the text item.
Action->Cancel Editing -- Aborts the editing and restores the previous list 
    value.
Attributes->Can Edit -- Toggles in-cell editing state.
Attributes->Auto Row Resize -- Resize the row so all of the entered
    text can be seen.  (Not implemented yet.)
Attributes->Auto Column resize -- Resizes the column so all of the 
    entered text can be seen.  (Not implemented yet.)
Attributes->No Auto Resize -- The current behavior.
Attributes->Text Can Grow -- Auto size the text item so it shows all 
    of the text.  (Not implemented yet.)


Future enhancements planned: Return saves the value, escape cancels.  Using 
other dialog items.  Implementing the resizing.  Put in menu commands to
change the sizes of cells.


Using Life
----------
Use the mouse to draw an initial cell pattern in the list.  Clicking in an 
empty area will put down a new cell; clicking on an already existing cell 
will remove it from the colony.  One pattern to try is the "R"-pentomino:
**
 **
 *
(Put this near the center.)
Choose Action->Start to start the colony growing, choose Action->Stop to 
pause the growth.  Action->Step steps the colony's growth for one time unit.

Bugs: Sometimes the screen doesn't always reflect the state of the colony
(if you start seeing isolated cells survive several generations, you'll need
to refresh the window.) Sometimes the timer being used to animate the life 
window overwhelms the event manager with traffic, causing update events to
be lost.  If you have a problem with the window not redrawing, 
do Action->Stop to let the event manager catch its breath.

Life menus:
File->Close -- Closes the Life window.
Edit->Clear -- Erases the window.
Action->Start -- Starts running Life with the colony in the window.
Action->Stop  -- Halts Life.
Action->Step  -- Performs one life generation.



About the source
================
vlist is still growing and mutating.  Currently, it shows some 
examples on how to use lists and listviews, using commands, and doing 
sophisticated subclassing of built-in dialog items.  It does not 
handle application shutdown and cleanup properly

listapi.c -- Implements the api fiddler dialog.
vlist.c -- Handles the control panel dialog.
listdemo.h -- Generic header file.
vlist.vr -- The resource file that has the dialogs and images.
listcell.c -- Handles the incell editing dialog using the xincell subclass.
listlife.c -- Life.  Don't talk to me about life.
incell.c -- This is the implementation for an in-cell editing subclass.
xincell.c -- Interface to the in-cell editing subclass.
makefile -- The makefile.  (do a make vlist)

