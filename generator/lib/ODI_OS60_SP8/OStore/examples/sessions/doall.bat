@echo off
echo  doall: Do all the steps of Sessions example
echo  doall: Begin removing results of previous runs
echo.
nmake clean
echo.
echo  doall: Done removing results of previous runs
echo  doall: Begin creation of app_server executables
echo.
nmake
echo.
echo  doall: done creation of app_server executables
echo  doall: begin run of app_server executable
echo.
app_server appserver.db 5 10 1 3000
echo.
echo  doall: done run of app_server executable
echo  doall: done Sessions example
