 
 Description Of Text_Filtering Sample:
 
       This module implements a simple subclass that runs all text insertion
       through a client-settable filter function that can decide on a 
       character-by-character basis what gets put into the textitem.
 
       The client supplies a filter function of the form:

          int filterFunc (vtext *text, vtextSelection *selection, 
                 const vchar **newText, long *length)

       where text is the vtext object to add the text to, selection is the
       currently selected range of text, newText is the new data being added,
       and length is a pointer to the length of text in newText.
  
       Since newText is a vchar**, you can change the text being added, even
       adding new text.  The length can be modified in the filter as well.
       The filter returns TRUE if the text manager should insert the new text,
       returning FALSE will abort the insertion.
 
       Then the client attaches the filter to the text.  The filter gets called
       whenever new text is added to the text item.
 
       The 'txtflt.c' file is broken into 3 parts:

       (a)  The text and textitem filtering functions.  These can be lifted
            verbatim and put into your application.

       (b)  Sample filters.  These give a flavor of writing a filter function.

       (c)  Driver program that filters 5 textitems

       Parts (b) and (c) are surrounded by an #ifdef filterSAMPLE_PROGRAM.
 
