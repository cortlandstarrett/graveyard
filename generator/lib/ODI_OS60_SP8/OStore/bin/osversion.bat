@echo off
rem Copyright (c) 1989-2002 by eXcelon Corporation. All Rights Reserved.
@echo ObjectStore Release 6.0 Service Pack 8 for Windows NT and Windows 98 Systems
@echo Build packaged %m-%d-%y %H:%M
@echo Fixes ambers 17622, 17667  

rem ##########################
if not "%1%"=="-v" goto SKIPMARKER
   setlocal
   set BIN=%~dp0
   dir/b/s %BIN% %BIN:bin=binsngl% %BIN:bin=lib% %BIN:bin=libsngl% | %BIN%\marker -
   endlocal
:SKIPMARKER

