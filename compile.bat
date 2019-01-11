@echo off

set QTDIR=C:\Qt\5.11.2\msvc2017_64
set PATH=%QTDIR%\bin;%PATH%
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
cd Source
qmake QtIrbis.pro
nmake clean
nmake
windeployqt -no-translations -no-compiler-runtime release\QtIrbis.dll
cd ..
cd Tests
qmake TestIrbis.pro
nmake clean
nmake
windeployqt -no-translations -no-compiler-runtime release\TestIrbis.exe
copy ..\Source\release .\release
release\TestIrbis.exe
cd ..