@echo off

SET DIR=%~dp0
cd %DIR\..
SET PROJECT_ROOT=%cd%
SET PORTABLE_DIR_REL_PATH="build\portable"
SET PORTABLE_ARCHIVE_NAME="usbrelaymodule-portable"

rd /s /q build\ 2>nul
mkdir build && cd build

cmake -G "Visual Studio 17 2022" -A Win32 .. 
cmake --build . --config Release

cd %PROJECT_ROOT%

mkdir %PORTABLE_DIR_REL_PATH%

copy build\app-cli\Release\getrelay.exe %PORTABLE_DIR_REL_PATH%
copy build\app-cli\Release\setrelay.exe %PORTABLE_DIR_REL_PATH%
copy build\libusbrelaymodule\Release\usbrelaymodule.dll %PORTABLE_DIR_REL_PATH%
copy external\hidapi\windows\Release\hidapi.dll %PORTABLE_DIR_REL_PATH%

cd %PORTABLE_DIR_REL_PATH%

tar -czf ../%PORTABLE_ARCHIVE_NAME%.tar.gz *