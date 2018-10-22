commshow sample
===============

Purpose
-------
The purpose of this sample is to expose the API of the Communication Module
graphically.

A user of this sample can create sessions where interprocess communication
can occur.  All attributes of the transport objects can be set and
experimented with.


Terminology
-----------
The following terms are defined in the Communication Module chapter of the
Programmer's Guide.  Briefly:

"transport object" - an instance of vcommDatagram or vcommStream.
                     For a vcommStream, this represents one end of a
                     connection.  For a vcommDatagram, this is an object
                     that receives and sends data at a certain location.
"locator"          - an instance of vcommLocator.  This object is used
                     locate transport objects
"events"           - messages (not data from another transport object) sent
                     to transport object notifying the application programmer
                     of certain events, like:
			- the transport object has been enable (vcommENABLED)
			- the transport object has been disabled(vcommDISABLED)
			- data is available to be received (vcommRECEIVE)
			- data is can be sent (vcommSEND)
			- an error has occurred (vcommERROR)

General Use
-----------
When the sample is run, the main dialog appears with five buttons,
categorized into two main sets, vcommStream and vcommDatagram.  The stream
transports are Pipe, TCP and Shared Memory.  The datagram transports are
UDP and Mailbox.

Hitting one of these buttons will create a transport object and dialog that
that represents that transport object graphically.  If a dialog doesn't
appear, that means this transport is not yet available for this platform.

The dialog has three main pages:

   Control:
	Used to make the transport object to perform some action, like
        send data, receive data.  Connect to a peer.  Listen for a connection.
        Shutdown and close connection.  (note: the concept of a "connection"
        only applies to the stream transports)

   Locators:
        Each transport object has at least a local locator.  vcommStream's
        have an additional locator (a "remote locator") that is used to 
        identify the peer when it connects or is connected to.

        Graphically, two locators are displayed on the locator page.  For
        vcommStream's, this represents the local and remote locator.  For
        vcommDatagram's, one is the local locator, the other is an
        auxillary locator used in the Receive() and Send() methods.
        For example, when a message is sent to a vcommDatagram, this locator
        will be updated to display the address of the sender.

   Attributes:
	All available named attributes for the transport object can be
	set on this page.  The available attributes depends on the transport.
	Refer to the Programmer's Guide for more details on these attributes.

	The available named attributes for locators are found on the
        "Locators" page.

        When events of interests occur, the all named attributes (transport
        object and locator) are updated.

The dialog also has two labels, one shows the state of the transport object,
the other shows any events of interest (explained above).  These get
updated primarily when the notify function of the transport object is called.

Setting of Attributes
---------------------

When setting attributes on a transport object or it's associated locators,
the dialog item's foreground color will turn green when the value is
accepted.  If the value changes as the transport object goes through
different states or receives different events, the color of the corresponding
dialog item will return to the default foreground color.  

A good example of this is the "hostname" attribute on a TCP locator.
Say, you are making a connection to a machine "booboo".  You type the
name "booboo" in the textitem labeled "Hostname: " and press enter, the
textitem turns green indicating to you that you set this value.  When the 
connection is made, the hostname reflects the fully qualified name, which 
would be different, something like "booboo.company.com".  The color is
useful in identifying attributes that are either ignored by the underlying
transport as the state of the transport object changes.

Refer to the GetAttribute method of the Reference Manual documentation
for a discussion on how attributes are effected by the state of the
transport object.

Simple Sample Session
---------------------

1.  Start the commshow sample
2.  Hit the TCP button.
3.  Select the "Locators" page of the newly opened dialog.
4.  In the Local Locator section, type 3333 in for "Port: " and push ENTER
    The 3333 should turn green.
5.  Go to the "Control" page.  Notice that the state of the object is 
    "Disabled". Hit the Enable button.  Notice that the state of the object 
    is now "Enabling".  This transport object is now listening for a 
    connection at port 3333.
6.  Hit the TCP button on the main dialog again.  A dialog (which will 
    be referred to as "second dialog") appears.
7.  Go to the locator page of the second dialog.
8.  In the Remote Locator section of the second dialog, type 3333 in for 
    "Port: " and push ENTER.  The 3333 should turn green.
9.  Go to the "Control" page (of the second dialog).  Notice that the state 
    of the object is "Disabled". Hit the Enable button.  Notice that the 
    state of the object eventually turns to "Enabled".  This transport object
    has just made a connection to the other transport object listening at
    port 3333.

10. Notice how the "Message: " label on each dialog says vcommENABLED - 0.  
    This means that the notify function of the each transport object received
    a vcommENABLED event.  The "- 0" represents the count of the events
    received in the notification function (important if you receive the same
    event twice).

11. Go to the locator page of each dialog.  Notice how it reflects the
    peer's address as well as the local address.

12. Go to control page of either dialog.  Click in the textitem labeled
    "Send This Message: ", and push ENTER.  This sends the data
    "Hi there!" to the other transport object.
13. Notice that the other transport object received a "vcommRECEIVE" message.
14. Go to the Attribute page of the dialog of the receiving transport object.
    Notice that the attribute "Available: " says "10".  That means there is
    10 bytes of data available to be read: strlen("Hi there!") == 10.
15. Receive the message by hitting the "Recv Message of Size" button
    (do not worry that the available data is only 10 bytes, since the
     transport object is asynchronous (by default), it will read as
     much data as it an and return.  Notice that "Received: " reflects
    10 bytes.
16. Hit the "Disable" button in the control page of one of the transport
    dialogs.  The other side gets a vcommERROR event, more specifically,
    the error code of this error event is displayed for "Message: ".
17. Hit the Disable button on the other transport object's dialog.

The session is now over.
