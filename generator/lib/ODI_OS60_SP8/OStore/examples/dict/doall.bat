@echo off
echo.
echo *** doall: begin dictionary example
echo.
echo *** doall: begin removing results of previous runs
echo.
nmake clean
echo.
echo *** doall: done removing results of previous runs
echo.
echo *** doall: begin creation of dict executable
echo.
nmake
echo.
echo *** doall: done creation of dict executables
echo.
echo *** doall: begin run of dict executable
echo.
dict
echo.
echo *** doall: done run of dict executable
echo.
echo *** doall: done dictionary example ***
