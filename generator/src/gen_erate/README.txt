

IMPORTANT NOTE: As of BridgePoint 5.0, One Fact is no longer updating (recompiling) gen_erate.exe
  to pick up the latest MC template changes into the binary model compiler.  Users who wish to use
  the latest model compiler should switch their projects to use the source model compiler.


========================================================================

File:      README.txt

========================================================================

Generator Procedures Document
How to Build and Configure Generator

1  Introduction
----------------
This file contains instructions on how to compile and configure generator
(gen_erate.exe).  It is designed to be used by persons wanting to compile
on either on the build server or their local development machine.


2  Prerequisites
-----------------
2.1  Machine setup
  One Fact has a Windows build server as an AWS instance that is already 
  configured to build generator. If you are a One Fact employee you can log into
  the machine via remote desktop.  Information about how to do this is in file  
  IT/AWS and SSH Key Files/Windows AWS Build and Test Server.  The following 
  steps only apply to new development machine setup.
  
2.1.1  Applications
  The following applications are required to exist and be properly
  configured for development use.
        . Cygwin (add packages: git, make)
        . Microsoft Visual C++ 6 and Service Pack 6

2.1.2  Libraries
  The following libraries are required to exist.  They will be put into a useable
  place simply by cloning the generator repository to your machine.
    . GalaxyGC30       - the Galaxy library
    . PCCTS/v1.33_mr20 - the PCCTS library

  If you desire to place the libraries somewhere other than under the local repository,
  you will have to modify bp_prod/win32/7.1B/build_scripts/get_host_platform.inc
  starting at line 111.  You will also need to adjust step 3.3, below,
  accordingly.

  
3 Configure the workspace
--------------------------
3.1  On the server, open the workspace c:/workspaces/dev with
     BridgePoint.
  . Update the source code for the projects to the latest from master 
  . No additional configuration is necessary, the workspace build files are 
    already set up for this machine.
      
3.2  If you're doing a local build
  . Check out (or sync with master) <github>/xtuml/mc
  . Check out (or sync with master) <github>/xtuml/generator
  . Check out (or sync with master) <github>/xtuml/bridgepoint
  
  Setup up for the Build
  _- Navigate to <git root>/generator/src/gen_erate
  _- Edit the file "msvc6.bat"
       Replace "set HOME=/home/build"
          with "set HOME=/home/<your username>"
  _- cd <git root>/generator/gen_erate
  _- Edit the file "create_bp_build"
      . In libtrans_dir variable, replace "/git/bridgepoint/src/libTRANS/"
           with "/cygdrive/c/<git repo root dir>/bridgepoint/src/libTRANS/"
  _- cd bp_prod/win32/7.1B/build_scripts
  _- Edit the file "get_host_platform.inc"
      . Replace "/c/cygwin/git/generator/"
           with "/cygdrive/c/<git repo root dir>/generator/"
      . Replace "c:/cygwin/git/generator/"
           with "c:/<git repo root dir>/generator/"
      . Replace CC_DIR=C:/PROGRA~1/MICROS~1/VC98/BIN
           with CC_DIR=<"short-style" path to MS VC6 bin folder>
  _- Note: The following build steps can be repeated after modifying source or
           archetypes during development (to rebuild).  The
           build_{release|debug} scripts can be used at this point instead of
           these manual steps (if desired).
   
  
4  Compiling the Generator EXEs
--------------------------------
4.1  Open cygwin shell
  _- Navigate to <git repo root dir>/generator/src/gen_erate
  _- ./msvc6.bat
     Warning: This causes the current directory to change.

4.2  Verify with the developers or file history that the generator version
  number was incremented with the latest work.  If it was not:
  _- Increment the current version number on line 77 of
     .../gen_erate/bp_source/win32/7.1B/main/src/gen_erate/main_gen_erate.cc
     while leaving the revision tag.
  _- Check in the file to git and push the change to github 

4.3  We have a script that basically runs the rest of the steps.  To use it:
  _- cd <git repo root dir>/generator/src/gen_erate/bp_prod/win32/7.1B/build_scripts
  _- ./build_release_version
  R- you are put into the build/ folder and a ready-to-use gen_erate.exe exists

  NOTE: If you have problems, try following the manual steps that follow.
  
4.4  Build
  _- cd <git repo root dir>/generator/src/gen_erate
  _- rm -rf bp_build
  _- ./create_bp_build -p C:/lib/PCCTS/v1.33_mr20
  _- cd bp_prod/win32/7.1B/build_scripts
  _- dos2unix * 

4.4.1 Release build
  _- ./comp_private win32 7.1B compile
    NOTE: If the build fails, see the troubleshooting section below.
  _- ./prod_private win32 7.1B mc_dbms trans gen_erate

4.4.2 Debug build
  -- This is for development purposes only.  You normally would skip building
  -- the debug version.
  _- ./comp_private win32 7.1B debug
  _- ./prod_private win32 7.1B debug mc_dbms trans gen_erate
     
4.4.3  Verify complete
  _- ls -l ../../../../bp_build/win32/7.1B/build/*.exe
  _R gen_erate.exe should exist

4.4.4 Make gen_erate LARGEADDRESSAWARE  
  _- cd ../../../../bp_build/win32/7.1B/build/
  _- editbin.exe /LARGEADDRESSAWARE gen_erate.exe
  _- dumpbin.exe /headers gen_erate.exe | grep "Application can handle large (>2GB) addresses"
  _R The string IS present in the generate binary.
  _R Note: This is simply a second chance to check that the gen_erate binary 
     is properly modified by editbin.exe.  Repeat that dumpbin.exe line and 
     ASSURE that the string being grepped IS found.
     

5  Using the EXEs
------------------
5.1  Backup current version and copy the new one into place
5.1.1 If you built on the server, transfer the new gen_erate.exe to your machine.
      Google drive is an easy way to do this. Download it into a local temporary
      folder (e.g. c:/temp).
      
5.1.2 Update MC plugin
  _- cd C:\xtuml\BridgePoint\eclipse_extensions\Bridgepoint\eclipse\
          plugins\corg.xtuml.bp.mc.c.binary_<version>\mc3020\bin        
  _- mv gen_erate.exe gen_erate.exe.orig
  . if you built on the server
    _- cp c:/temp/gen_erate.exe .
  . if you built locally
    _- cp <git repo root dir>/generator/src/gen_erate/bp_build/win32
           /7.1B/build/gen_erate.exe .

5.1.3 Update DAP plugin (optional)
  _- cd C:\xtuml\BridgePoint\eclipse_extensions\Bridgepoint\eclipse\
          plugins\org.xtuml.bp.dap.pkg_<version>\bridgepoint\win32\client\bin
  _- mv gen_erate.exe gen_erate.exe.orig
  . if you built on the server
    _- cp c:/temp/gen_erate.exe .
  . if you built locally
    _- cp <git repo root dir>/generator/src/gen_erate/bp_build/win32
           /7.1B/build/gen_erate.exe .
  _- cp gen_erate.exe gen_file.exe
  _- cp gen_erate.exe gen_import.exe

5.1.4 Move the new gen_erate so it is picked up by the build server
   ##############
   TODO - this section needs to be updated
   ############## 
  _- Perform smoke tests to verify the generator works properly.
  _- Remote desktop to svr-azt-eng-03 (if not already there)
  _- Start BridgePoint on the workspace c:/workspaces/build_artifacts
  _- Switch to the Resource perspective
  _- Expand the extra_files_for_build project
  _- Copy the new gen_erate.exe into this folder
  _- Commit the change to SVN


6. Using MS Visual Studio as a class browser
--------------------------------------------
6.1 The following files are present to allow the generator classes to be viewed
    using the MS Visual Studio IDE (MS VC6).
    <git repo root dir>/generator/src/gen_erate/gen_erate.dsw
    <git repo root dir>/generator/src/gen_erate/gen_erate.dsp

    This project's purpose is to provide a class browser for the generator, it
    can also aide in debugging (by attaching to the running process).  A MS VC6
    project was selected, because that is what generator is built with.
    However, note that these MS project files can not currently be used to build
    gen_erate.  It shouldn't be hard to extend the project files to do this
    if needed.

    -The Microsoft IDE does not understand how to interpret ".cc" and ".hh"
     files by default.  The registry must be hacked to force DevStudio to
     interpret these files properly.  The instructions in the MS knowledgebase
     article "How to make Visual C++ recognize file extensions as C/C++ files"
     must be followed.  Here is the link to that article:
     http://support.microsoft.com/kb/181506
     
7. Troubleshooting Build Problems
---------------------------------
7.1  The build steps outlined above will work nearly all the time for the build
     run on the server.  Occasionally, however, due to 
     running the build on a different machine, or an upgrade to cygwin, etc...
     the build will not function correctly.  Here are some tips for debugging
     problems.
     
7.1.1  Make sure all variables and paths to be used are correctly specified in
       msvc6.bat and get_host_platform.inc
7.1.1.1  Use "dir /x" on windows to get paths with "~<n>" in them

7.1.2  Errors output about incorrect usage of "set"
7.1.2.1  Possible due to /bin/sh (specified in the script) not pointing to the
         necessary command shell which is bash.  Check the system configuration.
7.1.2.2  Shell scripts not in the proper format.  Run dos2unix on the scripts,
         and also perhaps the source code and makefiles.
           $ cd model_compilers/generator/gen_erate/bp_prod
           $ find . -exec dos2unix {} \;
         
         Also make sure all *.sh files in the bp_source/win32/7.1B/make tree are
         in unix format.
           
7.1.3  To debug makefile problems, add "--debug=bj" on line 172 of comp_private
       where make is invoked.
       
7.1.4  If make outputs the error "invalid option <val>", this is likely due to 
       an issue with the command line specified on line 173 of comp_private.
7.1.4.1  Past resolutions for this issue have been to reorder the command line
         or set the variable "MAKEFLAGS=--unix".  Another recent solution to
         this problem was to add and "export BUILD_INCLUDE" line to export the
         environment variable instead of passing it on the make command line.
