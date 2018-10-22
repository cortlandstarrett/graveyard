
                              Galaxy/C Samples
                                    format


This sample program implments a simple interactive format editor.
The user is presented with a dialog containing a notebook whose pages
display, and allow the editing of, the patterns of a type-specific
format.  Each page contains a listitem that displays the patterns for 
the particular format.  By selecting a pattern, it is copied into a 
"Scratch Pad" for modification.  As the user modifies the pattern in
the Scratch Pad, it is parsed to determine the validity of the pattern.
If the pattern is invalid, the associated exception (vformatParseException)
is dumped to the "Pattern Errors" page.  If the pattern is accepted as valid,
a stringitem of the same type as the format is enabled for testing the format.
For instance, on the Date Format page, there is a vdateitem below the Scratch
Pad.  This stringitem is disabled if the pattern in the Scratch Pad is invalid.


To end the demo, simply close the application window.
