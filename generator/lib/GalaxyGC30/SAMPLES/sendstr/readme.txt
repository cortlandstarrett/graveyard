 Description Of 'sendstr' Sample:

    	This sample illustrates a comparison of building two application that
    	talk to each other using the Communication Manager vs using the Service
    	and Session Managers.

    	The application in question is simple; it provides a dialog that sends
	and receives strings.  Each application has its own dialog for each
    	connection or session it has.  (There are 2 dialogs for each
    	connection or session; 1 in each of the applications.)

    	There are 2 versions of the Service/Session Manager example.  The
    	first version does not use the Service Broker.  The second example 
   	uses more DAS components (such as the Service Broker and Service 
	Chooser).

    	Both programs have a main dialog that displays the
    	location, tranpsort, and port of the "service", along with a quit
    	button for terminating the application.

    	Specifying -Port <port> -Transport <transport> and -Location <location>
    	as command line arguments (or preferences) makes the application
    	a consumer of the specified service - the service must already be
    	running.  The default location is on the same machine, and the default
    	transport is dependent on the particular platform.  The 2nd DAS
    	example uses the Service Chooser instead of preferences.

    	To send a string, type it in the textitem and press the "Send" button.
    	The string will appear in the "Received" text item in the peer
    	application.
