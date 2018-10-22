
xwrite  - a micwrite extension
------------------------------
This module is an extension of the micwrite sample program, the baby
Galaxy word processor.  Added features include:

---the possibility to go between vtext objects and text files 
   stored in various character encodings via the Import/Export commands, 

---a uniform treatment of the "newline character" problem over 
   different platforms (LF vs. CR vs. CR-LF), and 

---the possibility to do some tricky key handling with textviews 
   to support input of different of characters beyond ASCII on 
   a U.S. keyboard.

xctrans.h, xctrans.c
--------------------
These files implement a subclass of vinstance that supports buffered
mappings for text files between the text character encoding
and the Galaxy vchar encoding.  Effectively, this module allows users
to build a translator between various character sets, using the vchar 
character set as an intermediary, although there may be significant 
loss of data if the vchar character set is other than Unicode.

In the xctransReadFromFile method implementation, all the various platforms' 
"newline" indicators (CR, LF, CR-LF) are mapped to a user-specified 
end-of-line character, preferably vtextEOLN.  This ensures that well-formed 
text files built on any platform will be read in properly.

In the xctransWriteLineToFile method implementation, the proper platform 
"newline" code is inserted at the end of every line.  The exported 
lines correspond to vtext paragraphs, not to wrapped lines.

Proper use of this module can be found in file document.c in functions
writeImportDocument and writeExportDocument.  All encodings known
to the String Manager are supported.

The strings associated with the messages of xctrans are stored in
the "Messages" string array of the "Xctrans" dictionary in the 
application resource file.

xcflchsr.h, xcflchsr.c
----------------------

These files implement a subclass of the Galaxy file chooser,
that allows users to specify the encoding and, optionally, the byte-order 
in the case of 2-byte encodings, when the selected files is to be treated 
as text and translated to the internal vchar character set.  The encoding 
and byte order are specified via menus in the file chooser menubar.

An additional ("split") subclass is provided, for the users who prefer to
specify the additional information separately from the file chooser.

The confirnation notices and menus associated with thes module are 
stored in the "Xcflchsr" dictionary of the appliation resource file.

xtxtviw.h xtxtview.c
----------------------

These files contain some slippery re-definitions for the default 
vtextview class bindings, and novice users are strongly discouraged
from imitating the methods used here.  Some of the methods of the
default vtextview class are replaced and its command space is modified
in order to support hexadecimal keying, and in the case where the
vchar character set is Unicode, Greek and Russian typewriter input,
and Hiragana (syllabic japanese) composition.

You may switch between the different modes on a per textview basis
by hitting "Command-Alt-a" for regular keyboard, "Command-Alt-g" for Greek, 
"Command-Alt-c" for Russian or "Command-Alt-h" for Hiragana keyboard.
"Command-Alt-x" allows hexadecimal keying in any occasion.  Example
for Unicode libraries:

Hello
[command-alt-g]
Kalhm`era
[command-alt-c]
{jhjij
[command-alt-h]
kore wa nan desu ka
[command-alt-a]
That's all.

The e-tonos greek character will appear only if you have a font that
includes the glyph for it.

If you want to implement your own input methods, it is safer to subclass
the default vtextitem class and override the methods that were replaced
in these files.  Modifying existing classes is a bad idea(TM).

This module has no associated resources.

other files
-----------
Compared to micwrite, some changes were made to the following files:

micwrite.h: now includes the header files discussed above.

micwrite.c: vstartup was replaced with a series of *getDefaultClass()
            calls, so that no textitems are inited before 
            the xtxtviewStartup modification takes effect;
    	    some new preferences were added.

document.c: the ShowSpecial focus command was removed, and new 
            ShowNormal, ShowSpecial and ShowKeycodes commands are implemented
            in the document command space; minor changes for import/export;
            messages from xctrans are redirected to the Debugging Stream.

resources
---------
File xwrite.vr is identical to micwrite.vr but for the following 
modifications:  

---dictionaries for the xctrans and xcflchsr classes were added;

---slight modification in the document command space to accomodate change 
   described under document.c.

remarks
-------
If you link this application with the Unicode libraries, try using a larger 
size application font, for example "family:fixed-size:16", because smaller
sizes may produce unpleasant scaling.  For a regular Sun4 Type5 keyboard,
you may run the application as:

./xwrite -font family:fixed-size:16 -commandkey meta -mnemonickey alt:shift 

If you link this application with the 8-bit libraries and don't expect to
ever deal with text files other than ASCII, Latin-1, Macintosh Standard Roman
and Windows Latin, you may still find a use for the code in xctrans
in the way it deals with the "newline character" problem.

xtxtview exercise
-----------------
A decent dictionary driven compose-machine for 8-bit codes.  Since 8-bit Galaxy
libraries may support different vchar characters sets on different platforms, 
the cleanest solution would be to compute the dictionary at run-time.
