 
  Description Of 'iconview' Sample:
 
  This program illustrates how to add a popup menu to viconview icons.
  
  The demo consists of a single dialog containing a standard viconview
  that was created with vre. All the icons within the iconview were added
  in vre also. When the user presses the menu mouse button on any icon
  within the viconview, a popup menu appears. The user can make a selection
  from the menu, but there is no functionality behind the menu items as yet.
  To "Clean Up" the icon view, pick Clean Up from the View menu.
 
  To accomplish this task, the standard viconview is subclassed to override
  its vdialogHANDLE_ITEM_BUTTON_DOWN method.
 
  To end the demo, choose "Quit" from the File menu, or quit from the
  window manager menu.
 
  This demo also illustrates how to create and use a custom
  viconviewView.  The new view, called a "Moon View", is essentially
  the same as the standard "Icon View" except that the default image
  is different, and the icon's name is placed above the icon's image.
