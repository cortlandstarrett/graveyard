@echo off
echo doall: Begin macro examples
echo doall: Begin removing results of previous runs
echo.
nmake /nologo clean 1> nul 2>&1
echo.
echo doall: Done removing results of previous runs
echo doall: Begin building macro examples
echo.
nmake /nologo
echo.
echo doall: Done building macro examples
echo doall: Begin run of DEFINE_EXCEPTION example
echo.
def_exc
def_exc arg
def_exc arg arg
def_exc bad
echo.
echo doall: Done run of DEFINE_EXCEPTION example
echo doall: Begin run of OS_BEGIN_TXN example
echo.
txn_example
echo.
echo doall: Done run of OS_BEGIN_TXN example
echo doall: Begin run of TIX_HANDLE example
echo.
tix_example
tix_example nonsense.db
tix_example nonsense.db
echo.
echo doall: Done run of TIX_HANDLE example
echo doall: Done running macro examples
echo.
