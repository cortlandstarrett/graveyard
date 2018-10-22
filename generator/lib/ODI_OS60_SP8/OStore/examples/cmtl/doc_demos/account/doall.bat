@echo off
echo doall: Begin CMTL example application
echo doall: maintains bank balances for accounts in database
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
echo doall: Create and initialize database
echo.
init_db.exe
echo.
echo doall: Done initialization
echo.
echo doall: Run the main application
echo.

echo list>input
echo deposit 005 200>>input
echo balance 005>>input
echo withdraw 999 100>>input
echo withdraw 001 100000>>input
echo withdraw 001 100>>input
echo list>>input
echo quit>>input

account < input

del input

echo.
echo doall: Done CMTL example
echo.
