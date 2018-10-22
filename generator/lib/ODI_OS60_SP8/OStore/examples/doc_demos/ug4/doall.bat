@echo off
echo doall: Begin database roots example
echo doall: Begin removing results of previous run
echo.
nmake /nologo clean 1> nul 2>&1
echo.
echo doall: Done removing results of previous run
echo doall: Begin building executables
echo.
nmake /nologo
echo.
echo doall: Finished building executables
echo doall: Begin setting root value
echo.
set_part
echo.
echo doall: Done setting root value
echo doall: Begin retrieving root value
echo.
get_part
echo.
echo doall: Done retrieving root value
echo doall: Done database roots example
echo.
