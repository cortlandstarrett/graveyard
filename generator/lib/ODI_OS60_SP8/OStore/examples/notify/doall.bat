@echo off
echo  doall: Do all the steps of Notification example
echo  doall: Begin removing results of previous runs
echo.
nmake clean
echo.
echo  doall: Done removing results of previous runs
echo  doall: Begin creation of notify executable
echo.
nmake
echo.
echo  doall: Done creation of notify executable
echo  doall: Begin run of notify executable
echo.
notify
echo.
echo  doall: Done running notify executables
echo.
