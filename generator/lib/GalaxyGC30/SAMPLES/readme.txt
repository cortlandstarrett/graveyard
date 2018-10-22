

	     	             Sample Programs
			     ---------------
                              Galaxy/C 2.5

This directory contains subdirectories for Galaxy sample programs.

Following is a brief description of each sample and its purpose.  See
the comments in the individual readme for each sample for more information
about the sample and any specific instructions on how to use each sample.


Subdir Name        Contents
----------------------------------------------------------------------------
adjust		-- The adjust program consists of a single dialog containing
                   a "splitter" item between the top and bottom areas of the
                   dialog. The splitter can be dragged up and down in the
                   dialog to re-adjust the amount of space taken up by the
                   different areas of the dialog. This program illustrates 
                   how to implement a dialog-specific "splitter" item.

animcur		-- The animcur program demonstrates one technique for
		   implementing animated cursors in a Galaxy application.
		   A sequence of vcursors is displayed in sequence when a
		   timer is fired. You can change the images used for the
		   animation, the desired frames per second, and whether the
		   animation should bounce or wrap.

boinker		-- The boinker program illustrates a technique for 
		   implementing an initialization progress window. This 
		   window is immediately opened to show progress of the
		   initialization of the boinker application. Progress is
		   shown by a series of humorous messages displayed in the
		   window. The initialization of the application is
		   broken into chunks each represented by an instance of
		   a "task" object. These task objects are good examples of
		   non-GUI objects that benefit from the object-based paradigm
		   provided by the Galaxy Class Manager. The boinker program
		   also is a good example of how to effectively use Galaxy
		   exceptions and the Galaxy Debug Manager.

calc 		-- The calc program consists of a single dialog which
                   represents a two-button calculator that
                   multiplies and adds integers. This program illustrates 
                   how to use notify functions to associate application-
                   specific code with user interface items. It also illustrates
                   how to use vtextitem objects to retrieve typed-in user
                   input and how to use code that vre can generate
                   automatically to refer to all user interface items by
                   constant internal names.

cfocus		-- The cfocus program consists of a single dialog with a 
                   scrolling container of buttons, text items and check 
                   boxes. This program illustrates how to make containers 
                   scroll automatically as focus is changed from the keyboard.

chart		-- The chart program is an extended example consisting of 
                   six dialogs. Four of these dialogs contain different 
                   kinds of charts. The other two dialogs are used to control
                   what to display on the charts and how to display it. 
                   The program illustrates subclassing of Galaxy classes and
                   provides a basic chart package that may be of use to
                   customers.

chsrhlp		-- The Chooser Help sample programs demonstrate
                   on-line help for Galaxy Choosers. It also
                   illustrates how to incorporate chooser help into
                   on-line help for your application.

colchsr		-- The colchsr program is a simple example illustrating 
                   how to use a color chooser. On platforms that have a 
                   native color chooser, the native chooser is used.
                   Otherwise, the Galaxy color chooser is used.

combo		-- There are six different combo samples, each illustrating
		   the use of standard and popdown comboboxes with varying
		   kinds of entry boxes, choice boxes, and values. These 
		   samples serve to demonstrate the flexibility of the Galaxy
		   Combination Box Manager.

comm		-- The comm program is a command-line interface for sending 
                   a string from one instance of the program to another. 
                   The program illustrates basic use of the Galaxy 
                   Communications Manager.

commterm	-- The commterm program is a client program that allows the
		   user to connect to and send characters to any server 
		   program that will accept them. The user types characters
		   into the text view in the client dialog and each character
		   is sent to the server as it is typed. The commterm program
		   illustrates the Communication Manager.

domain		-- The vdomain program consists of a dialog containing 
                   a domain item and many controls with which to manipulate
                   the attributes of the domain item. The program illustrates
                   the many features of a vdomainitem that you get "for free."

domsamp		-- The domsamp sample illustrates the full range of
		   functionality available in the Galaxy Domain Manager.
		   It allows the user to basically experiment with most 
		   of the Domain Manager entry points.  
		   live it. love it.

drag		-- The drag program consists of a "Drag" dialog and a "Drop"
                   dialog. The Drag dialog contains a scrolling list and an
                   image. The list entries as well as the image can be dragged
                   individually from the Drag dialog to the Drop dialog using
                   the drag mouse button combination specific to the
                   particular look-and-feel in use. The program illustrates
                   use of the Galaxy Drag Manager.

dragimg	       	-- The dragimg program illustrates "live dragging" of an
                   image over a dialog.

draw		-- This program consists of a dialog containing a drawing 
                   area and various controls to specify what to draw
                   in the area. The program illustrates the
                   capabilities of the Galaxy Drawing Manager. There are two
                   versions of this program: one version (vdraw) creates the
                   dialog on-the-fly with API calls and handles resizing of
                   the dialog manually; the other (vdrawres) loads its
                   dialog from a resource file and thus leaves the handling
                   of the dialog resize to the springs and struts laid out in
                   the resource file. It is interesting to compare vdraw to
                   vdrawres.

drcomm		-- This example consists of two executables, drclient and
		   drserver. The drclient program represents a patient who
		   is communicating with a doctor. The drserver program is
		   the doctor. This example extensively illustrates the
		   Communication Manager.

dropimg		-- The dropimg program illustrates how to pass strings and
		   images to another process using DAS. The sending of both
		   strings and images from the main dialog to the secondary
		   dialog is animated to give a neat effect.

dwi		-- "Domain With Items". The dwi program consists of a single
                   dialog containing a vdomainview with domain objects
                   that are actually dialog items. The program illustrates 
                   subclassing a vdomainview so that it can contain 
                   (and properly deal with) embedded dialog items.

event		-- This example shows how to flush pending events without 
		   returning to the main loop. This is a code snippet, not 
		   a full program.

face		-- The face program consists of a single dialog containing 
                   a single dialog item. The dialog item is a subclass of 
                   vdialogItem that renders itself as a happy face. The
                   program illustrates how to use selector commands  to 
                   associate application code with user interface items. 
                   It also illustrates simple subclassing and how to use some
                   basic Drawing Manager functionality. The face2 and face3
		   programs are extensions of the face program. face2
		   illustrates adding named attributes while face3 illustrates
		   adding class variables.

filecshr	-- Three demos illustrating basic use of a file chooser.
                   The filechs1 program shows setup and use of a no-frills file
                   chooser for use in opening a file. On platforms that have
                   a native file chooser, the native file chooser is 
                   used. Otherwise, the Galaxy file chooser is used. The
                   filechs2 program shows setup and use of a file chooser
                   that contains platform independent filters. Again, if a
                   native chooser is available on a particular platform, the
                   native chooser is used. The filechs3 shows setup and use of 
                   a _directory_ chooser that allows the user to choose a 
                   directory.

fontchsr	-- The fontchsr program illustrates the use of a simple font
                   chooser. On platforms that have a native font chooser,
                   the native chooser is used. Otherwise, the Galaxy
                   font chooser is used.

grid		-- The grid program illustrates using one list view as column
		   headers for another list view. Column headers scroll with
		   the main list view. Selecting a column heading
		   can select multiple columns in the main list view.

help		-- The vhelp program provides a command-line interface to 
                   the Galaxy Help System. The program illustrates the 
                   various capabilities of the Galaxy Help System and shows
                   how to use them.

helpsrc		-- Four different examples of the Visix Help Source language.
		   These examples are snippets of help source files that each
		   show a particular style or construct that help source file
		   writers might find handy.

iconview        -- The iconview program illustrates how to add a popup menu
                   to the icons within a viconview.

isniffer	-- This program allows the user to find all the vimages in
		   any given resource file and create a temporary file to
		   hold copies of these images. isniffer has a fairly complex
		   progress indicator window and the "sniffing" of
		   a resource file can be suspended or aborted while in 
		   progress. The viewer window of collected images provides
		   a good example of the undo capabilities of the Galaxy Undo
		   Manager. This example is also valuable to aid in learning
		   more about the Resource Manager, Iconview Manager, 
		   Exception Manager, and Debug Manager.

linedom		-- The linedom program illustrates how to provide 
                   "live updating" of connecting lines (instead of bounding
                   rectangles) while dragging 'nodes' in a domain view.

list		-- The vlist program is an extended example illustrating 
                   the capabilities of the Galaxy List Manager. The main
                   dialog has buttons that bring up other dialogs 
                   that illustrate particular areas of functionality of the
                   List Manager. One dialog illustrates the functionality
                   that you get "for free" and another illustrates how to 
                   extend a vlistview object to support editing within its
                   cells, etc.

mainview	-- The mainview program is an example of how to use the 
                   vmainview class which is new to Galaxy 2.0. vmainview
                   implements document interfaces particular to 
                   certain window systems. Under the Microsoft Windows look
                   and feel, the document interface is the Multiple Document
                   Interface (MDI). When running with Windows look and feel,
                   a vmainview provides native Windows MDI functionality.

mandel          -- This sample consists of two programs, master and slave.
                   These demonstrate the use of DAS and the service broker
                   for splitting up a computationally expensive job among
                   several slaves.

mdemo		-- The vmdemo program illustrates an "outline view." This is
		   a list where each row can expand and collapse to
		   show/hide sub-rows. It is very similar to the vre dictionary
		   editor. The vmdemo program also illustrates how to use
		   two list views as column and row headers for a third list
		   view. When the main list view is scrolled, its column and
		   row headers scroll with it.

micdraw		-- This fairly extended example is a basic drawing program
                   which uses the vdomainview class as its basis. It
                   illustrates how to create objects on a canvas, manipulate
                   these objects, zoom in and out of the document, create
                   patterns and pens, save and load documents, and more.
		   The sample, when compiled with mdrawUSE_DAS set to TRUE,
		   also illustrates how to integrate DAS into an
		   application.

miniedit	-- A simple example consisting of a single dialog that is
                   a text editor. This example illustrates the functionality
                   that the programmer gets "for free" when using a
                   vtextview object. It also illustrates how to read text from
                   a file into a vtext object to be viewed by a vtextview.

mtext		-- The mtext program illustrates how to implement a
		   complete, well-behaved dialog item subclass that overrides
		   methods from many different inherited layers. This
		   subclass, named "mtext", is a small text item that allows 
		   text entry, simple selection, and attribute settings.

notebook	-- There are three notebook samples which illustrate how
		   to use the vnotebook user interface item. the listtest
		   program demonstrates how to subclass the vnotebook to use
		   other objects (a vlistitem in this sample) in place of
		   the tabs of the pages for a notebook. The
		   opttest program is the same as listtest except that the
		   tab set is represented by a control option menu. The
		   notebk sample illustrates all of the styles that can be
		   set for a default unsubclassed vnotebook. The default tab
		   set is used.

pacemake	-- The thump sample illustrates how to use events to
		   slice up long computations. This technique prevents the
		   user interface from locking up during the long calculations.
		   The thump program includes a status window which
		   shows the percentage of work done as the calculations
		   are proceeding.

password	-- The password program displays a textitem that can be used
		   for entering a password. The textitem displays stars 
		   instead of the entered characters.

print		-- The print program illustrates how to quickly get started
		   using the Galaxy Print Manager. It provides a basic
		   interface to some of the Print Manager functionality.

progress	-- This small example shows how to set up a "progress" window.
                   A progress window contains a slider that moves to
                   indicate the amount of work completed so far. It
                   illustrates how to use the Galaxy Event Manger to update
                   the progress window as other work is being done.

puzzle		-- This example is a game consisting of a 4x4 grid of 
                   numbered tiles, one of which is empty. The object is to
                   arrange the tiles in numerical order from top left to
                   bottom right. (Good Luck!)  The program illustrates 
                   fairly advanced use of the Galaxy Domain Manager.
                   

resmerge	-- The resmerge program is a command line interface for 
                   merging multiple given resource files into a single 
                   resource file. It illustrates use of the Galaxy 
                   Resource Manager.

ruler           -- The ruler program consists of a single dialog containing
                   a vruler coordinated with a vlistview. It illustrates how
                   to set up a vlistview to respond to vruler changes.

scalerot	-- The scalerot sample illustrates scaling, rotation, and
		   translation of an image using the Galaxy Drawing Manager.

scramble	-- A screen-saver like program that divides the screen into
                   cells and move these cells around to scramble the screen.
                   This program illustrates how to do basic animation.

sendstr		-- The sendstr example consists of three separate executables,
                   comm, das1, and das2. All three send and receive simple
		   text strings to/from other instances of themselves. 
		   However, all three differ in the mechanism they use to
		   accomplish this task. The comm program uses the
		   Communication Manager. The das1 program is analogous to
		   comm, but uses the Service Manager and Session Manager
		   instead of the Communications Manager. The das2 program
		   uses more DAS components (the Service Broker and Service
		   Chooser) instead of trying to be analogous to comm.

spam		-- The spam program illustrates use of an off-screen buffer to
		   draw and erase text of a specific solid color quickly and
		   efficiently. Using the Event Manager to drive the action,
		   the program flashes the word "Spam" in different colors and
		   sizes on the screen at regular intervals.

splash		-- This simple example illustrates how to implement a
                   simple splash dialog for a Galaxy application.
                   The program immediately puts up a splash dialog, and
                   leaves it up until all program initialization work
                   is finished. Then, the splash dialog closes and an
                   application dialog appears. The program illustrates use 
                   of the Galaxy Event Manager.

spread		-- The spread sample illustrates how to set up a simple
		   spreadsheet using Galaxy. The sample uses the List
		   Manager extensively. The spreadsheet in this example has
		   an Excel-inspired user interface.

textfilt	-- This example provides a simple vtext subclass that runs
                   all text insertion through a client-settable filter
                   function that can decide on a character-by-character
                   basis what gets put into a textitem. The program
                   consists of a single dialog which has many text items
                   with various filter functions. Try entering valid and
                   invalid text!

thmeter		-- The thmeter program provides a subclass of vcontrol that
		   is a simple read-only control that mimics a thermometer
		   (two different colored regions indicating division of
		   a whole).

tiling          -- The tiling program draws quasi periodical Penrose tiling 
		   of the plane. You can select different dimensions of the 
		   tiling from 3 to 13 from the Options menu.  This sample 
		   is an example of how to write a Galaxy application 
		   starting from the similar application written using 
		   Microsoft Windows SDK. It may be useful as a starting 
		   point for developers already familiar with MSW SDK.  
		   Tilingw - application with the same functionality and 
		   user interface but written by SDK is included ( for
		   MS-Windows platforms).  It also illustrates Drawing, 
		   Command, Dialog, Color and Resource managers.  

tracker		-- The tracker program illustrates one way to do simple
		   animation using the Galaxy Domain Manager and the Galaxy
		   Timer Manager. Domain objects that look like planes and
		   blimps etc. "fly" around the domain.

tutorial	-- This directory contains all of the source code for all
                   of the Galaxy Tutorial examples and exercises. The programs
                   and program names are consistent with the printed version
                   of the Galaxy 2.x Tutorial.

xrunner		-- The xruntest program illustrates how to establish a
		   connection from a Galaxy application to the XRunner/WinRunner
		   automated testing tool from Mercury Interactive Corp. You
		   must have XRunner/WinRunner installed at your site for this program
		   to be of any use. The program puts up a dialog containing a
		   good assortment of various Galaxy user interface items.
		   Assuming XRunner/WinRunner is running at the time, the program
		   demonstrates the recording and playback capabilities of
		   XRunner/WinRunner as well as the specifics of how Galaxy interacts
		   with XRunner/WinRunner.

xsubwin		-- The xsubwin program shows how to set up an X window as
		   a Galaxy dialog item.

xwrite		-- The xwrite program is an extended sample consisting of
		   a single main dialog which is a basic word processor.
		   It illustrates advanced use of the Galaxy Text Manager.
		   It allows import/export of text files under various 
		   encodings supported by the String Manager.  The xtxtview 
		   module allows hex keying into textviews and if compiled with
                   the Unicode vchar character set, it simulates input 
                   methods for Greek, Cyrillic and Hiragana characters.
