@echo off
echo doall: Begin schema key examples
echo doall: Begin removing results of previous run
echo.
nmake /nologo clean 1> nul 2>&1
echo.
echo doall: Done removing results of previous run
echo doall: Begin building schema key examples
echo.
nmake /nologo
echo.
echo doall: Begin building schema key examples
echo doall: Begin creating database with schema key
echo.
create_sk
echo.
echo doall: Done creating database with schema key
echo doall: Begin setting schema key to access database
echo.
set_sk
echo.
echo doall: Done setting schema key to access database
echo doall: Done schema key examples
echo.

