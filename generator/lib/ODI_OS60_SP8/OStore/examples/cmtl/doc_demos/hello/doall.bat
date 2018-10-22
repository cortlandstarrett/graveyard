@echo off
echo doall: Begin CMTL example Hello World (XML version)
echo.
echo doall: Remove results from previous run
echo.
nmake /nologo clean 1> nul 2>&1
echo.
echo doall: Done removing results
echo.
echo doall: Build executables
echo.
nmake /nologo
echo.
echo doall: Done building
echo.
echo doall: Run application
echo.
hello.exe
echo.
echo doall: Done CMTL example
echo.
