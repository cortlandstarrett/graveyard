@echo off
echo doall: Begin TIX exception examples
echo doall: Begin removing results of previous run
echo.
nmake /nologo clean 1> nul 2>&1
echo.
echo doall: Done removing results of previous run
echo doall: Begin building TIX exception examples
echo.
nmake /nologo
echo.
echo doall: Done building TIX exception examples
echo doall: Begin creating two databases
echo.
make_dbs stuff.db nonsense.db
echo.
echo doall: Done creating two databases
echo doall: Begin first run of nested TIX exception handler:
echo doall:   no argument specified
echo.
tix_nest
echo.
echo doall: Done first run of nested TIX exception handler
echo doall: Begin second run of nested TIX exception handler:
echo doall:   wrong argument specified
echo.
tix_nest stuff
echo.
echo doall: Done second run of nested TIX exception handler
echo doall: Begin third run of nested TIX exception handler:
echo doall:   correct argument specified
echo.
tix_nest stuff.db
echo.
echo doall: Done third run of nested TIX exception handler
echo doall: Begin first run of no-handler example:
echo doall:   two arguments specified, first is incorrect
echo.
no_hndlr stuff nonsense.db
echo.
echo doall: Done first run of no-handler example
echo doall: Begin second run of no-handler example:
echo doall:   two arguments specified, second is incorrect
echo.
no_hndlr stuff.db nonsense
echo.
echo doall: Done second run of no-handler example
echo doall: Begin third run of no-handler example:
echo doall:   both arguments incorrect
echo.
no_hndlr stuff nonsense
echo.
echo doall: Done third run of no-handler example
echo doall: Begin fourth run of no-handler example:
echo doall:   both arguments correct
echo.
no_hndlr stuff.db nonsense.db
echo.
echo doall: Done fourth run of no-handler example
echo doall: Done TIX exception examples
echo.
