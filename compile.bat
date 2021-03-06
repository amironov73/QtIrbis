@echo off

rmdir /s /q Binaries\x64 > nul 2> nul
rmdir /s /q Binaries\x86 > nul 2> nul

mkdir Binaries\x64
mkdir Binaries\x86

call :BUILD C:\Qt\5.12.2\msvc2017_64 64 x64
call :BUILD C:\Qt\5.12.2\msvc2017    32 x86

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

rmdir /s /q Source\QtIrbis\release      > nul 2> nul
rmdir /s /q Source\OfflineTests\release > nul 2> nul
rmdir /s /q Source\OnlineTests\release  > nul 2> nul

del Source\.qmake.stash                 > nul 2> nul
del Source\Makefile.*                   > nul 2> nul
del Source\QtIrbis\Makefile.*           > nul 2> nul
del Source\OfflineTests\Makefile.*      > nul 2> nul
del Source\OnlineTests\Makefile.*       > nul 2> nul

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

copy /b Source\QtIrbis\release\*.dll Source\OfflineTests\release > nul 2> nul
del Source\QtIrbis\release\*.obj                                 > nul 2> nul
del Source\QtIrbis\release\*.pch                                 > nul 2> nul
del Source\OfflineTests\release\*.pch                            > nul 2> nul
del Source\OnlineTests\release\*.pch                             > nul 2> nul

windeployqt -no-translations -no-compiler-runtime Source\QtIrbis\release\QtIrbis.dll
windeployqt -no-translations -no-compiler-runtime Source\OfflineTests\release\OfflineTests.exe
windeployqt -no-translations -no-compiler-runtime Source\OnlineTests\release\OnlineTests.exe

rmdir /s /q Source\QtIrbis\release\bearer > nul 2> nul

rem -------------------------------------------------------
rem Run tests
rem -------------------------------------------------------

Source\OfflineTests\release\OfflineTests.exe

copy Source\QtIrbis\release\*.* Binaries\%3 > nul 2> nul
copy Source\QtIrbis\QtIrbis.h   Binaries\%3 > nul 2> nul

EndLocal

:END
