Splash sample
=============

This program illustrated how to implement a splash dialog for any
Galaxy application.  The splash dialog must be opened before we have
entered the main event loop, so we must post our own events for it.
This program also illustrates how to associate application code with
menu items using notify functions.

This demo consists of a splash dialog which appears immediately and
stays up until all application initialization is finished.  Then, the
splash dialog closes and an application dialog appears.

To end the demo, choose "Quit" from the File menu of the application
dialog.
