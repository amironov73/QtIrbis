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

copy /b Source\QtIrbis\release\*.dll Source\IrbisTests\release
del Source\QtIrbis\release\*.obj > nul

windeployqt -no-translations -no-compiler-runtime Source\QtIrbis\release\QtIrbis.dll
windeployqt -no-translations -no-compiler-runtime Source\IrbisTests\release\IrbisTests.exe

rmdir /s /q Source\QtIrbis\release\bearer > nul

rem -------------------------------------------------------
rem Run tests
rem -------------------------------------------------------

Source\IrbisTests\release\IrbisTests.exe