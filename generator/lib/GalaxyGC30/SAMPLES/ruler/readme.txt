 
 Description Of 'ruler' Sample:
      This sample provides an example of using the ruler to control a 
      listview.  The following operations are possible:
 
      select a column from a list
      resize a column
      remove a column
      move a column
      
      This example always compacts the ruler.  This makes things much
      easier to implement.  The ruler items cannot get any bigger.
      Something I haven't tracked down yet.
  
      The demo can be stopped by using the File/Quit menu item.
 
      Hints: to watch rulerNotify messages
         setenv vdebugMODULE ruler
         setenv vdebugLEVEL  750
 
