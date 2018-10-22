@echo off
echo  doall: Do all the steps of Employee Retrieve example
echo  doall: Begin removing results of previous runs
echo.
nmake clean
echo.
echo  doall: Done removing results of previous runs
echo  doall: Begin creation of partinit and empretr executables
echo.
nmake
echo.
echo  doall: done creation of partinit and empretr executables
echo  doall: begin run of partinit executable
echo.
partinit
echo.
echo  doall: done run of partinit executable
echo  doall: begin run of empretr executable
echo.
empretr
echo.
echo  doall: done run of partinit executable
echo  doall: done empretr example
