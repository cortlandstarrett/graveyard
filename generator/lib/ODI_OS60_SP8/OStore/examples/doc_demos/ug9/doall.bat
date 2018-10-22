@echo off
echo doall: Begin schema evolution examples
echo doall: Begin removing results of previous run
echo.
nmake /nologo clean 1> nul 2>&1
del workdb
echo.
echo doall: Done removing results of previous run
echo doall: Begin building schema evolution examples
echo.
nmake /nologo
echo.
echo.
echo doall: Done building schema evolution examples
echo doall: Begin creating unevolved database
echo.
cd ..\ug5
call doall
cd ..\ug9
copy ..\ug5\notes .
echo.
echo doall: Invoke ossevol to evolve database
echo.
ossevol workdb n_schema.adb notes
echo.
echo doall: Done evolving database with ossevol
echo  doall: Begin listing evolved database
echo.
list notes
echo.
echo doall: Done listing evolved database
echo doall: Begin post processing
echo.
post_process notes
echo.
echo doall: Done post processing
echo doall: Begin listing processed database
echo.
list notes
echo.
echo doall: Done listing processed database
echo doall: Begin copying unevolved database
echo.
copy ..\ug5\notes .
del workdb
echo.
echo doall: Done copying unevolved database
echo doall: Begin run of schema evolution application
echo.
evol_schema workdb notes
echo.
echo doall: Done run of schema evolution application
echo doall: Begin listing evolved database
echo.
list notes
echo.
echo doall: Done listing evolved database
echo doall: Done schema evolution examples
echo.

