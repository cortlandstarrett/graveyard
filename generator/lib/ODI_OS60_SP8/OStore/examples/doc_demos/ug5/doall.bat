@echo off
echo doall: Begin transaction examples
echo doall: Begin removing results of previous run
echo.
nmake /nologo clean 1> nul 2>&1
echo.
echo doall: Done removing results of previous run
echo doall: Begin building transaction examples
echo.
nmake /nologo
echo.
echo doall: Done building transaction examples
echo doall: Begin run of dynamic transaction example
echo.
dyn_txn notes < note1.dat >nul
echo.
echo doall: Done run of dynamic transaction example
echo doall: Begin listing contents of database
echo.
list notes
echo.
echo doall: Done listing contents of database
echo doall: Begin second run of dynamic transaction example (rollback)
echo.
dyn_txn notes < note2.dat >nul
echo.
echo doall: Done second run of dynamic transaction example (rollback)
echo doall: Begin listing contents of database
echo.
list notes
echo.
echo doall: Done listing contents of database
echo doall: Begin run of lexical transaction example
echo.
lex_txn notes < note2.dat >nul
echo.
echo doall: Done run of lexical transaction example
echo doall: Begin listing contents of database
echo.
list notes
echo.
echo doall: Done listing contents of database
echo doall: Begin run of abort-only transaction
echo.
txn_nest notes < note3.dat >nul
echo.
echo doall: Done run of abort-only transaction
echo doall: Begin listing contents of database
echo.
list notes
echo.
echo doall: Done listing contents of database
echo doall: Done transaction examples
echo.

