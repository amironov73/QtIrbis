@echo off

rmdir /s /q Binaries\x64 > nul 2> nul
rmdir /s /q Binaries\x86 > nul 2> nul

mkdir Binaries\x64
mkdir Binaries\x86

call :BUILD C:\Qt\5.11.2\msvc2017_64 64 x64
call :BUILD C:\Qt\5.11.2\msvc2015    32 x86

goto :END

:BUILD

echo ======================================================
echo BUILD %1 %2
echo ======================================================

SetLocal

rem -------------------------------------------------------
rem Setup
rem -------------------------------------------------------

set QTDIR=%1
set PATH=%QTDIR%\bin;%PATH%
set CL= /MP
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars%2.bat"

rmdir /s /q Source\QtIrbis\release    > nul 2> nul
rmdir /s /q Source\IrbisTests\release > nul 2> nul

del Source\.qmake.stash          > nul 2> nul
del Source\Makefile.*            > nul 2> nul
del Source\QtIrbis\Makefile.*    > nul 2> nul
del Source\IrbisTests\Makefile.* > nul 2> nul

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
del Source\QtIrbis\release\*.obj    > nul 2> nul
del Source\QtIrbis\release\*.pch    > nul 2> nul
del Source\IrbisTests\release\*.pch > nul 2> nul

windeployqt -no-translations -no-compiler-runtime Source\QtIrbis\release\QtIrbis.dll
windeployqt -no-translations -no-compiler-runtime Source\IrbisTests\release\IrbisTests.exe

rmdir /s /q Source\QtIrbis\release\bearer > nul 2> nul

rem -------------------------------------------------------
rem Run tests
rem -------------------------------------------------------

Source\IrbisTests\release\IrbisTests.exe

copy Source\QtIrbis\release\*.* Binaries\%3 > nul 2> nul

EndLocal

:END
