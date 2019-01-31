@echo off

rmdir /s /q Binaries\xp > nul 2> nul
mkdir Binaries\xp

SetLocal

rem -------------------------------------------------------
rem Setup
rem -------------------------------------------------------

set QTDIR=C:\Qt\5.6.3\mingw49_32
set MINGW=C:\Qt\Tools\mingw492_32
set PATH=%QTDIR%\bin;%MINGW%\bin;%PATH%
set INCLUDE=C:\Qt\5.6.3\mingw49_32\include;C:\Qt\5.6.3\mingw49_32\mkspecs\win32-g++;C:\Qt\5.6.3\mingw49_32\include\QtCore;C:\Qt\5.6.3\mingw49_32\include\QtNetwork

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
mingw32-make clean
mingw32-make
cd ..

rem -------------------------------------------------------
rem Copy DLL
rem -------------------------------------------------------

copy /b Source\QtIrbis\release\*.dll Source\IrbisTests\release
del   Source\QtIrbis\release\*.o           > nul 2> nul
rmdir Source\QtIrbis\release\QtIrbis.h.gch > nul 2> nul
del   Source\IrbisTests\release\*.o        > nul 2> nul
rmdir Source\IrbisTests\release\pch.h.gch  > nul 2> nul

windeployqt -no-translations -no-compiler-runtime Source\QtIrbis\release\QtIrbis.dll
windeployqt -no-translations -no-compiler-runtime Source\IrbisTests\release\IrbisTests.exe

rmdir /s /q Source\QtIrbis\release\bearer > nul 2> nul

rem -------------------------------------------------------
rem Run tests
rem -------------------------------------------------------

Source\IrbisTests\release\IrbisTests.exe

copy %MINGW%\bin\libgcc*.dll         Binaries\xp > nul 2> nul
copy %MINGW%\bin\libstdc*.dll        Binaries\xp > nul 2> nul
copy %MINGW%\bin\libwinpthread*.dll  Binaries\xp > nul 2> nul
copy Source\QtIrbis\release\*.*      Binaries\xp > nul 2> nul
copy Source\QtIrbis\QtIrbis.h        Binaries\xp > nul 2> nul

EndLocal
