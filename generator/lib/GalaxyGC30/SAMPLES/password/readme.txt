The password program displays a textitem that can be used for entering 
a password.  The basic idea here it to display "*"'s instead of the entered 
characters, while still preserving the character data.  This is accomplished 
by overriding the vtextviewDRAW_RUN method of the textitem.

