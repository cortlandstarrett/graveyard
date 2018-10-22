@echo off
echo doall: a script that builds and runs the basic ObjectStore version
echo doall: of the restaurant reservations program
echo.
echo doall: begin removing results of previous runs
echo.
nmake clean
echo.
echo  doall: Done removing results of previous runs
echo.
echo doall: begin basic ObjectStore example
echo.
nmake
echo.
echo  doall: Done building basic ObjectStore example
echo.
echo  doall: begin creating and initializing database
echo.
init_db "Il Falchetto" 10
echo.
echo  doall: Done initialization.
echo  
echo  doall: begin run of main application.
echo  doall: request reservations for 6 persons
echo
reserve 6
echo
echo  doall: done reservations request
echo
echo  doall: done running basic ObjectStore example
