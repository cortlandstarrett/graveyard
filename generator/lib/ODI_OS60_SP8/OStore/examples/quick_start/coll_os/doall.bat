@echo off
echo doall: a script that builds and runs the collections version
echo doall: of the restaurant reservations program
echo.
echo doall: begin removing results of previous runs
echo.
nmake clean
echo.
echo  doall: Done removing results of previous runs
echo.
echo doall: begin building collections example
echo.
nmake
echo.
echo  doall: Done building collections example
echo.
echo  doall: begin initializing database with collection object
echo  doall: and populating collection with Restaurant objects
echo.
init_db 
echo.
echo  doall: Done initialization.
echo. 
echo  doall: begin listing all restaurants in database.
echo.
rlist
echo.
echo  doall: done listing.
echo.
echo  doall: begin run of main application,
echo  doall: request reservations for party of 17 at Il Falchetto
echo.
reserve "Il Falchetto" 17
echo.
echo  doall: done reservations request.
echo.
echo  doall: begin adding restaurants to database.
echo.
add_restaurant "McDonald's" Beverly 23
add_restaurant Commodore Beverly 57
echo.
echo  doall: done adding restaurants.
echo.
echo  doall: begin listing restaurants in Beverly.
echo.
rlist Beverly
echo.
echo  doall: done listing.
echo.
echo  doall: done running collections example.
echo.

