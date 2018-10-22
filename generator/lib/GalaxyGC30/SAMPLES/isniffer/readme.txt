
isniffer Help Reference                                          August 1994
(c) Copyright 1993-94 Visix Software Inc.
All Rights Reserved.
------------------------------------------------------------------------------

Overview:
========

	The isniffer sample was written as an exercise in undo. More specifically,
	it was written to "get a feel" for what level of library-level undo 
	support an application with single level undo might need. As it turns
	out, several other Galaxy managers get used heavily: the resource manager,
	(lots of reading/writing), the iconview manager, and the exception/debug
	managers. Four lesser known managers also make brief guest appearances:
	the print manager, the spring domain manager, the image editor module,
	and the new preferences manager.

	So what's isniffer good at? Sniffing out galaxy vimages! True, it's not
	lighting swift, but it has a cool progress indicator and does a through
	job <hint: take a coffee break if you ever start sniffing the galaxy
	system resource file> It even lets you sniff more than one file
	at once <oooooouuu...aaaaahh>. 

	As it plows through the file, isniffer stores any discovered images in
	a temporary file (you can customize where these temp files are stored
	with a "tempdir" preference). Since large, dense resource files can
	take some time, isniffer allows you to suspend or abort any sniff in 
	progress. Once a file has been completely processed, isniffer creates a 
	"viewer" for it (seen as a vanilla icon in the main window) and beeps 
	(an alarm in case you've fallen asleep). To see the retrieved images, 
	double click on the sniffed file's icon.

	The viewer window is where the real undo testing happens. Sniffed image
	collections are managed by the "image manager" or imanager for short.
	The image manager is a first stab at a class that provides on-demand
	retrieval and shared access to a set of images (called an "image store").
	Within a single store, images can be added, removed, and changed as 
	single entities or groups. All destructive operations are undoable.
	A viewer loads its sniffed images from the temporary file into an image
	store. By using the available viewer "Edit" options we can exercise the 
	imanager's undo capability. As the sample code shows, in addition to the 
	imanager's undo support, the application itself had to put lots work
	into the visual support for undo. Moral of the story? Undo needs to 
	built into an application from day one; retro-fitting it would be 
	really really ummm...yucky.

	In trying to pep up the sample, several goodies have been added: You
	can edit any image in a viewer using the standard galaxy image editor
	facilities. From a viewer window you can print out a catalogue of 
	the sniffed images. Images can be viewed their actual sizes or as
	40x40 thumbnails (the default setting).

	The default setup for the isniffer sample involves one executable
	isniffer and a sample resource file for sniffage snf_imgs.vr


Bug Reports, etc.
================

	Please send any bug reports, enhancement requests, etc. to:

					galaxy-bugs@visix.com

	Use "isniffer" in the Component field of the problem report.


Running the sample:
==================

	* Make the isniffer executable.

	* Run isniffer. In environments that support command line arguments, 
	  there are several options you can specify. Here is a summary:

	  * not really preferences
	    -help				: show dis file

	  * sniffage and environment preferences
		-tempdir [PATH]		: store temporary files in PATH (must be writable)
		-tempfolder [PATH]	: same as -tempdir but for mac weenies
		-verbose			: spew extra information
		-recursive			: sniff compound resources recursively
		-allresources		: sniff all compound resources (ignored without
	                          recursion)
	  * viewer window layout
		-thumbnails			: show thumbnails by default
		-fulltitles			: show full pathnames to sniffed files by default
		-thumbsize-actual [N] : make thumbnail size NxN pixels

	  * image catalogue printing
	    -header				: show extra info in page header
		-border				: include borders in printout
		-pages				: include page numbers in printout
		-errata				: include # items, sniff file name, etc.

	  You can also specify resource files on either the command line, or
	  on the Macintosh, by dropping the file on the isniffer application
	  icon from the Finder.

	* A single main "requestor" window opens. From this window you can 
	  start sniffs, suspend sniffs in progress, resume suspended sniffs,
	  view sniffed files, and quit the application. To quit isniffer, 
	  either select the "phffht" button or close the requestor window.

	  To begin sniffing files, select the "sniff..." button; this opens
	  up a file chooser. Choose one or more resource files and hit "OK"
	  (or when available "Apply"), and let the sniffage begin...

	  For each resource file, the progress indicator shows how many 
	  compound resources still need to be examined and how many images
	  have been located and stashed in the temporary file. You can 
	  continue to add new files for sniffing before all the other files 
	  have been complete processed. Notice the "springiness" of the 
	  progress indicator. <oooouuuu....aaaaaahhhh...>

	  To suspend -all- sniffs hit the "suspend" button in the requestor
	  window. Since the image sniffing and image stashing work independently,
	  suspending a sniff does not block isniffer from stashing all images 
	  its found for a file. isniffer will continue to write the images to 
	  the temporary file until all have been processed; then it waits for 
	  the user to continue sniffing or quit. To continue sniffing hit the
	  "resume" button in the requestor window.

	  When a file has been completely processed (all sniffing and stashing
	  has completed), isniffer adds a vanilla viewer icon to the requestor
	  window's view. Double-click on this icon to open a window to see
	  the images.

	* The viewer window shows all the images retrieved from a resource 
	  file (the full pathname to the source resource file is shown as
	  the viewer's default title). You can view the images full-size or as 
	  thumbnails (scaled down versions). By default viewers will display an 
	  image thumbnail if the image's size is greater than 40 pixels in 
	  either direction. The suffix "{scale}" is tagged to the end of the 
	  image's name to indicate it's been scaled down. Use the 
	  "View/Thumbnails Shown" menu option to adjust whether full-size 
      images are displayed.

      Use the Edit menu to do cut/copy/paste/duplicate and other mangling
	  with the images. You can change the image itself with the "Edit/Edit..."
	  option or by double-clicking on the image. Only one image 
	  can be edited at a time -- a limitation of the sample not the galaxy
	  image editor module. Warning: undo is not implemented for image
	  editing!

	  To print a thumbnail catalogue of the viewer, select "File/Print."
	  This uses the default vprint device for the platform. Refer to the
	  Galaxy Programmer's Guide and Reference Manuals for more information
	  on the vprint mangler <can you say "pass the buck">.

	  To save the images to a permanent file select either "File/Save" or
	  "File/Save as..." The images will be saved as a Galaxy resource 
	  file.

	  To close a viewer window select "File/Close" or the window's window
	  manager's close adornment ("go-away box", "close menu", etc.). 
	  Warning: closing a viewer, removes the temporary image file and 
	  destroys the viewer. Use "View/Hide" to hide the viewer's window.

	* You can adjust some isniffer window layout/printing preferences.
	  But first you must find the magic cookie...


Things the sample doesn't do well:
=================================

	o the main "sniff requestor" window should be based on vmainview. this
	  sample was written before vmainview existed, so it's based on straight
	  iconviews. a newer version should use mainviews to support MDI 
	  (windooze), global menubar (MDI and Macintosh), etc.

	o under u-nuts, saving the temporary sniff file never works across 
	  filesystems because we use vfsRename (just a "move" in disguise which
	  isn't supported across filesystems in many a-case). for these, we 
	  should do an explicit copy or we could just wait for vfsCopy...

	o we use function commands a lot. there are some situations where
	  synthetic commands would be more elegante.

	o misc edit commands are not supported across viewers. since the focus
	  was testing the imanager and current galaxy's clipboard support is
	  limited (really) to text this feature got punted.

	o should remember explicit temp directory info across sessions.

	o opening a large image store takes a looooooong time. this reflects
	  a problem w/ iconviews and the way the "viconviewAddIcon" method
	  is implemented (Order(n) iterations over the entire domain every
	  time you add an object!). Ideally, we should be able to either batch
	  item additions or lock the iconview from recalculating positions
	  until the last item is added.


------------------------------------------------------------------------------
History:

$Log: readme,v $
# Revision 1.1  1994/08/19  00:10:38  simone
# Initial revision
#

------------------------------------------------------------------------------

/*
 * Local Variables:
 * tab-stop-list:(4 8 12 16 20 24 28 32 36 40 44 48 52 56 64 72 80 88 96 104)
 * tab-width:4
 * indent-tabs-mode:t
 * truncate-lines:t
 * End:
 */


