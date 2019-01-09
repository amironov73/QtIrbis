@echo off

set QTDIR=C:\Qt\5.11.2\msvc2017_64
set PATH=%QTDIR%\bin;%PATH%

copy ..\Source\cmake-build-debug\QtIrbis.dll cmake-build-debug
windeployqt -no-translations -no-compiler-runtime cmake-build-debug\TestIrbis.exe