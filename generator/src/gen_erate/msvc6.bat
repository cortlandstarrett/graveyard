@echo off
rem==========================================================================
rem
rem File:      $RCSfile: msvc6.bat,v $
rem Version:   $Revision: 1.10 $
rem Modified:  $Date: 2013/01/10 23:42:31 $
rem
rem (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
rem
rem==========================================================================
rem This document contains information proprietary and confidential to
rem Mentor Graphics Corp., and is not for external distribution.
rem==========================================================================
rem

c:
chdir c:\cygwin\bin
set HOME=/home/Administrator

rem
rem Root of Visual Developer Studio Common files.
set VSCommonDir=C:\Program Files\Microsoft Visual Studio\Common

rem
rem Root of Visual Developer Studio installed files.
rem
set MSDevDir=C:\Program Files\Microsoft Visual Studio\Common\MSDev98

rem
rem Root of Visual C++ installed files.
rem
set MSVCDir=C:\Program Files\Microsoft Visual Studio\VC98

rem
rem VcOsDir is used to help create either a Windows 95 or Windows NT specific path.
rem
set VcOsDir=WIN95
if "%OS%" == "Windows_NT" set VcOsDir=WINNT

rem
echo Setting environment for using Microsoft Visual C++ tools.
rem

if "%OS%" == "Windows_NT" set PATH=%MSDevDir%\Bin;%MSVCDir%\Bin;%VSCommonDir%\Tools\%VcOsDir%;%VSCommonDir%\Tools;%PATH%
if "%OS%" == "" set PATH="%MSDevDir%\Bin";"%MSVCDir%\Bin";"%VSCommonDir%\Tools\%VcOsDir%";"%VSCommonDir%\Tools";"%windir%\system";"%PATH%"
set INCLUDE=%MSVCDir%\ATL\Include;%MSVCDir%\Include;%MSVCDir%\MFC\Include;%INCLUDE%
set LIB=%MSVCDir%\Lib;%MSVCDir%\MFC\Lib;%LIB%

set VcOsDir=
set VSCommonDir=

bash --login -i

