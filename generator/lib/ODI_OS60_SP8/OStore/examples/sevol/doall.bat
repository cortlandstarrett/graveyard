@echo off
echo.
echo *** doall: begin sevol example
echo.
echo *** doall: begin removing results of previous runs
echo.
nmake clean
echo.
echo *** doall: done removing results of previous runs
echo.
echo *** doall: begin creation of db_pop1 and db_read1 executables
echo.
nmake db_pop1.exe
nmake db_read1.exe
echo.
echo *** doall: done creation of db_pop1 and db_read1 executables
echo.
echo *** doall: begin run of db_pop1 executable
echo.
db_pop1 db1.db 1000
echo.
echo *** doall: done run of db_pop1 executable
echo.
echo *** doall: begin run of db_read1 executable. NB: error is expected, see README.TXT
echo.
db_read1 db1.db
echo.
echo *** doall: done run of db_read1 executable
echo.
echo *** doall: begin creation of db_pop2, db_read2 and evolve2 executables
echo.
nmake db_pop2.exe
nmake db_read2.exe
nmake evolve2.exe
echo.
echo *** doall: done creation of db_pop2, db_read2 and evolve2 executables
echo.
echo *** doall: begin run of db_pop2 executable
echo.
db_pop2 db2.db 1000
echo.
echo *** doall: done run of db_pop2 executable
echo.
echo *** doall: begin run of db_read2 executable. NB: error is expected, see README.TXT
echo.
db_read2 db2.db
echo.
echo *** doall: done run of db_read2 executable
echo.
echo.
echo *** doall: begin run of evolve2 executable
echo.
evolve2 db2.db wdb2.db
echo.
echo *** doall: done run of evolve2 executable
echo.
echo *** doall: begin run of db_read2 executable
echo.
db_read2 db2.db
echo.
echo *** doall: done run of db_read2 executable
echo.
echo *** doall: begin creation of db_pop3, db_read3 and evolve3 executables
echo.
nmake db_pop3.exe
nmake db_read3.exe
nmake evolve3.exe
echo.
echo *** doall: done creation of db_pop3, db_read3 and evolve3 executables
echo.
echo *** doall: begin run of db_pop3 executable
echo.
db_pop3 db3.db 1000
echo.
echo *** doall: done run of db_pop3 executable
echo.
echo *** doall: begin run of db_read3 executable. NB: error is expected, see README.TXT
echo.
db_read3 db3.db
echo.
echo *** doall: done run of db_read3 executable
echo.
echo.
echo *** doall: begin run of evolve3 executable
echo.
evolve3 db3.db wdb3.db
echo.
echo *** doall: done run of evolve3 executable
echo.
echo *** doall: begin run of db_read3 executable
echo.
db_read3 db3.db
echo.
echo *** doall: done run of db_read3 executable
echo.
echo *** doall: begin creation of db_pop4, db_read4 and evolve4 executables
echo.
nmake db_pop4.exe
nmake db_read4.exe
nmake evolve4.exe
echo.
echo *** doall: done creation of db_pop4, db_read4 and evolve4 executables
echo.
echo *** doall: begin run of db_pop4 executable
echo.
db_pop4 db4.db 1000
echo.
echo *** doall: done run of db_pop4 executable
echo.
echo *** doall: begin run of db_read4 executable. NB: error is expected, see README.TXT
echo.
db_read4 db4.db
echo.
echo *** doall: done run of db_read4 executable
echo.
echo.
echo *** doall: begin run of evolve4 executable
echo.
evolve4 db4.db wdb4.db
echo.
echo *** doall: done run of evolve4 executable
echo.
echo *** doall: begin run of db_read4 executable
echo.
db_read4 db4.db
echo.
echo *** doall: done run of db_read4 executable
echo.
echo *** doall: begin creation of db_pop5, db_read5 and evolve5 executables
echo.
nmake db_pop5.exe
nmake db_read5.exe
nmake evolve5.exe
echo.
echo *** doall: done creation of db_pop5, db_read5 and evolve5 executables
echo.
echo *** doall: begin run of db_pop5 executable
echo.
db_pop5 db5.db 1000
echo.
echo *** doall: done run of db_pop5 executable
echo.
echo *** doall: begin run of db_read5 executable. NB: error is expected, see README.TXT
echo.
db_read5 db5.db
echo.
echo *** doall: done run of db_read5 executable
echo.
echo.
echo *** doall: begin run of evolve5 executable
echo.
evolve5 db5.db wdb5.db
echo.
echo *** doall: done run of evolve5 executable
echo.
echo *** doall: begin run of db_read5 executable
echo.
db_read5 db5.db
echo.
echo *** doall: done run of db_read5 executable
echo.
echo *** doall: done sevol example ***
