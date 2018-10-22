 thmeter.c -- a simple read-only control that mimics a thermometer
                  (two different colored regions indicating division
                  of a whole.)
 
 This implements a subclass called "thermoMeter."  It uses the dialog
 item settings (foreground and background color, item menu.) to let
 clients customize the control without having to use code.  The
 "vertical" setting determines whether the control displays the dividing
 line between the two colors as horizontal or vertical.

 This also includes a small driver program (that hooks up a slider that
 controls the thermometer's value) and a quit button.


 thmeter.vr -- Galaxy Resource file for thermometer example


