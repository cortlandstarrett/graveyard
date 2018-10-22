@echo off
echo doall: Do all the steps of the Hello World example
echo doall: Begin removing results of previous runs
echo.
nmake clean
echo.
echo doall: Done removing results of previous runs
echo doall: Begin creation of hello executable
echo.
nmake
echo.
echo doall: Done creation of hello executable
echo doall: Begin run of hello executable
echo.
hello
echo.
echo doall: Done run of hello executable
echo doall: Done hello world example
