@echo off
echo  doall: Do all the steps of Allocator example
echo  doall: Begin removing results of previous runs
echo.
nmake clean
echo.
echo  doall: Done removing results of previous runs
echo  doall: Begin creation of dba & user example executables
echo.
nmake
echo.
echo  doall: Done creation of dba & user executables
echo  doall: Begin run of dba example executable
echo.
dba_example
echo.
echo  doall: Done run of dba example executable
echo  
echo  doall: Begin run of user example executable
echo.
usr_example
echo.
echo  doall: Done run of user example executable
echo  
echo  doall: Done allocator example
