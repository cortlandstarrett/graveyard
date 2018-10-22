@echo off
echo  doall: Do all the steps of Hello World 2 example
echo  doall: Begin removing results of previous runs
echo.
nmake clean
echo.
echo  doall: Done removing results of previous runs
echo  doall: Begin creation of cntinit and hello2 executables
echo  doall:   A warning is expected from ossg.  See README.TXT.
echo.
nmake
echo.
echo  doall: Done creation of cntinit and hello2 executables
echo  doall: Begin run of cntinit executable
echo.
cntinit
echo.
echo  doall: Done run of cntinit executable
echo  doall: Begin first run of hello2 executable
echo.
hello2
echo.
echo  doall: Done first run of hello2 executable
echo  doall: Begin second run of hello2 executable
echo.
hello2
echo.
echo  doall: Done second run of hello2 executable
echo  doall: Begin third run of hello2 executable
echo.
hello2
echo.
echo  doall: Done third run of hello2 executable
echo  doall: Begin fourth run of hello2 executable
echo.
hello2
echo.
echo  doall: Done fourth run of hello2 executable
echo  doall: Done hello world 2 example
