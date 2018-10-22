@echo off
echo doall: Begin notifications example
echo doall: Begin removing results of previous run
echo.
nmake /nologo clean 1> nul 2>&1
echo.
echo doall: Done removing results of previous run
echo doall: Begin building notifications example
echo.
nmake /nologo
echo.
echo doall: Done building notifications example
echo doall: Begin run of receiver invocation of notify
echo.
start notify 1
echo.
echo doall: Give receiver time to execute
echo.
doze 5
echo.
echo doall: Begin run of sender invocation of notify
echo.
notify
echo.
echo doall: Receiver and sender both returned
echo doall: Done notifications example
echo.
