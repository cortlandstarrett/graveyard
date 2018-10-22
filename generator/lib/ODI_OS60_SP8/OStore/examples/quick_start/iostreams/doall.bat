@echo off
echo doall: a script that builds and runs the iostreams version.
echo doall: of the restaurant reservations program.
echo.
echo doall: begin iostreams example.
echo.
echo doall: begin removing results of previous runs.
echo.
nmake clean
echo.
echo  doall: done removing results of previous runs.
echo.
echo  doall: begin building iostreams example.
echo.
nmake
echo.
echo doall: done building iostreams example.
echo.
echo doall: begin initializing streams file with.
echo doall: name of restaurant and number of tables.
echo.
init_db "Il Falchetto" 10
echo.
echo doall: done initializing.
echo.
echo doall: begin run of main application,
echo doall: request reservations for 6 persons.
echo.
reserve 6
echo.
echo doall: done reservations request.
echo.
echo doall: done running iostreams example.
echo.

