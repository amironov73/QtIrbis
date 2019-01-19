@echo off

rem -------------------------------------------------------
rem Setup
rem -------------------------------------------------------

set QTDIR=C:\Qt\5.11.2\msvc2017_64
set PATH=%QTDIR%\bin;%PATH%
set CL= /MP
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"

rem -------------------------------------------------------
rem Compile
rem -------------------------------------------------------

cd Source
qmake All.pro
nmake clean
nmake
cd ..

rem -------------------------------------------------------
rem Copy DLL
rem -------------------------------------------------------

copy /b Source\QtIrbis\release\*.dll Source\QtTests\release
del Source\QtIrbis\release\*.obj > nul
rmdir /s /q Source\QtIrbis\release\bearer > nul

windeployqt -no-translations -no-compiler-runtime Source\QtIrbis\release\QtIrbis.dll
windeployqt -no-translations -no-compiler-runtime Source\QtTests\release\QtTests.exe

rem -------------------------------------------------------
rem Run tests
rem -------------------------------------------------------

Source\QtTests\release\QtTests.exe