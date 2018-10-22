@echo off
echo.
echo *** doall: begin coll example
echo.
echo *** doall: begin removing results of previous runs
echo.
nmake clean
echo.
echo *** doall: done removing results of previous runs
echo.
echo *** doall: begin creation of coll_put and coll_get executables
echo.
nmake
echo.
echo *** doall: done creation of coll_put and coll_get executables
echo.
echo *** doall: begin run of coll_put executable
echo.
coll_put
echo.
echo *** doall: done run of coll_put executable
echo.
echo *** doall: begin run of coll_get executable
echo.
coll_get
echo.
echo *** doall: done run of coll_get executable
echo.
echo *** doall: done coll example ***
