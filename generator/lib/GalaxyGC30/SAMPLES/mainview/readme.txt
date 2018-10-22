Mainview Help Reference                                          December 1994
(c) Copyright 1994 Visix Software Inc.
All Rights Reserved.
------------------------------------------------------------------------------

Overview:
========

    The mainview sample is designed to demonstrate the mainview class,
    which implements MDI (the multiple document interface) when running
    under Microsoft Windows.

    The sample opens two windows and makes them child documents of the
    main frame window.  These windows should behave as MDI children when 
    running under Windows.  In particular, note that the menubar in the
    frame window changes in response to changes in the active child.
    When not running under Windows, the child windows will be separate 
    but will still have a leader/follower relationship with the frame 
    window.  The icon area on non-Windows platforms is implemented by a 
    viconview, but that is an implementation detail and should not be 
    relied upon.

    A button bar and status line are also provided.

Bug Reports, etc.
================

    Please send any bug reports, enhancement requests, etc. to:

                    galaxy-bugs@visix.com

    Use "mainview" in the Component field of the problem report.

Running the sample:
==================

    * Make the mainview executable

    * Run mainview.  There are no special command line switches or
      environment variables to set.
 