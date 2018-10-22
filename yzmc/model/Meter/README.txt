*** NOTE: In all execution environments, the application loop runs infinitely, the
***   user must manually terminate the runtime.


Verifier
----------
- Run the launch at "Debug Configurations > xtUML eXecute Application > Meter1"
  o The application will launch and run the test case automatically
  
  
Vanilla C
-----------
- Make sure "gen/vfb_main.c" is renamed to "gen/vfb_main.c.no"
- Make sure the AUTOSAR and VFB marks are turned off in gen/system.mark
- Remove all files under src/
- Build Project
- Run the launch at "Debug Configurations > C/C++ Application > Meter Debug"


AUTOSAR C + VFB
-----------------
- Make sure "gen/vfb_main.c" is in place
- Make sure the AUTOSAR and VFB marks are turned on in gen/system.mark
- Remove all files under src/
- Build Project
- Run the launch at "Debug Configurations > C/C++ Application > Meter Debug"