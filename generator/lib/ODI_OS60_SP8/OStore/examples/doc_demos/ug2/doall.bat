@echo off
echo doall: Begin basic ObjectStore example
echo doall: Remove results from previous run
echo.
nmake /nologo clean 1> nul 2>&1
echo.
echo doall: Done removing results from previous run
echo doall: Build executables
echo.
nmake /nologo
echo.
echo doall: Done building executables
echo doall: Initialize readers.db and books.db databases
echo.
init_bc readers.db books.db < bc1.dat
echo.
echo doall: Finished initializing databases
echo doall: List contents of databases
echo.
list_bc readers.db books.db
echo.
echo doall: Finished listing databases
echo doall: Make two bookclub selections
echo.
bookclub readers.db books.db < bc2.dat > nul
bookclub readers.db books.db < bc3.dat > nul
echo.
echo doall: Finished bookclub selections
echo doall: List contents of databases
echo.
list_bc readers.db books.db
echo.
echo doall: Finished listing databases
echo doall: Done basic ObjectStore example
echo.
