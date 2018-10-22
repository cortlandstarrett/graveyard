@echo off
echo.
echo *** doall: begin relat example
echo.
echo *** doall: begin removing results of previous runs
echo.
nmake clean
echo.
echo *** doall: done removing results of previous runs
echo.
echo *** doall: begin creation of coll_put and invtest executables
echo.
nmake
echo.
echo *** doall: done creation of coll_put and invtest executables
echo.
echo *** doall: begin run of coll_put executable
echo.
coll_put
echo.
echo *** doall: done run of coll_put executable
echo.
echo *** doall: begin run of invtest executable
echo.
invtest
echo.
echo *** doall: done run of invtest executable
echo.
echo *** doall: done relat example ***
