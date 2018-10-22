
                                Galaxy Sample
                                  complete

This sample demonstrates a textitem that auto-completes its current input
string against the set of input strings that were previously accepted.

Note: a user "accepts" the contents of a textitem when they hit the [Return]
or [Enter] key or move the keyboard input-focus out of the textitem.

The textitem, actually a vstritem, acts in a similar fashion to the Microsoft
Internet Explorer URL entry combobox.  Strings entered by the user are added
to a listitem located below the input item.  As the user types into the
textitem, it searches the listitem for entries that are prefixes for its
current string content.  For instance, if the user had previously entered the
strings "foo", "bar", and "baz" and then types the letter "b", the search
would discover "b" is a prefix for "bar."  It then would append the remaining
matched string "ar" to "b" and finally it would select "ar" so that any
subsequent typing would replace that matching substring. If the user then
accepts the match, the matched listitem entry is moved to the top of the list.
The idea is that the most recently entered/matched listitem entries should
be near the top of the list.

The goal of this sample is to demonstrate:

1) an interaction technique that minimizes the number of keystrokes necessary
   for entering commonly used strings.

2) features of the vstritem class, notably the ease with which modifications
   to the item's string content can be observed by overridiing the
   vstritemINSERT_STRING method.