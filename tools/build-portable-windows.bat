@rem
@rem Copyright (C) 2022 https://github.com/nkh-lab
@rem
@rem This is free software. You can redistribute it and/or
@rem modify it under the terms of the GNU General Public License
@rem version 3 as published by the Free Software Foundation.
@rem
@rem This software is distributed in the hope that it will be useful,
@rem but WITHOUT ANY WARRANTY.
@rem

@echo off

@rem To be able to set variables inside an if statement
setlocal enableDelayedExpansion

set DIR=%~dp0
cd %DIR\..
set PROJECT_ROOT=%cd%
set PORTABLE_DIR_REL_PATH="build\portable"
set PORTABLE_ARCHIVE_NAME="usbrelaymodule-portable"

:start_args_check
if "%1" == "" (
    goto end_args_check
)
if "%1" == "simu" (
    set SIMU=true
    set CMAKE_ARGS=!CMAKE_ARGS! -Dusbrelaymodule_BUILD_SIMU=ON
    set CMAKE_ARGS=!CMAKE_ARGS! -DJSONCPP_WITH_TESTS=OFF
    set CMAKE_ARGS=!CMAKE_ARGS! -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF
    set CMAKE_ARGS=!CMAKE_ARGS! -DJSONCPP_WITH_PKGCONFIG_SUPPORT=OFF
    set CMAKE_ARGS=!CMAKE_ARGS! -DJSONCPP_WITH_CMAKE_PACKAGE=OFF
)
if "%1" == "gui" (
    set GUI=true
    set CMAKE_ARGS=!CMAKE_ARGS! -Dusbrelaymodule_BUILD_GUI=ON

    if not exist %PROJECT_ROOT%\prebuilt\wxwidgets (
        mkdir .temp
        cd .temp
        curl -LO https://www.7-zip.org/a/7zr.exe
        curl -LO https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.1/wxMSW-3.2.1_vc14x_x64_Dev.7z
        curl -LO https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.1/wxMSW-3.2.1_vc14x_x64_ReleaseDLL.7z
        curl -LO https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.1/wxWidgets-3.2.1-headers.7z

        7zr.exe x *.7z -o*

        mkdir %PROJECT_ROOT%\prebuilt\wxwidgets\lib\Debug
        mkdir %PROJECT_ROOT%\prebuilt\wxwidgets\lib\Release
        mkdir %PROJECT_ROOT%\prebuilt\wxwidgets\include

        xcopy /s /e wxMSW-3.2.1_vc14x_x64_Dev\lib\vc14x_x64_dll %PROJECT_ROOT%\prebuilt\wxwidgets\lib\Debug
        xcopy /s /e wxMSW-3.2.1_vc14x_x64_ReleaseDLL\lib\vc14x_x64_dll %PROJECT_ROOT%\prebuilt\wxwidgets\lib\Release
        xcopy /s /e wxWidgets-3.2.1-headers\include %PROJECT_ROOT%\prebuilt\wxwidgets\include

        cd %PROJECT_ROOT%
        rd /s /q .temp\ 2>nul
    )
)

shift
goto :start_args_check

:end_args_check

rd /s /q build\ 2>nul

mkdir build && cd build

cmake -G "Visual Studio 17 2022" %CMAKE_ARGS% ..
cmake --build . --config Release

@rem Check if build return error
if not %errorlevel% == 0 (
    exit /b %errorlevel%
)

cd %PROJECT_ROOT%

mkdir %PORTABLE_DIR_REL_PATH%

copy build\app-cli\Release\getrelay.exe %PORTABLE_DIR_REL_PATH%
copy build\app-cli\Release\setrelay.exe %PORTABLE_DIR_REL_PATH%
copy build\libusbrelaymodule\Release\libusbrelaymodule.dll %PORTABLE_DIR_REL_PATH%
copy build\external\hidapi\src\windows\Release\hidapi.dll %PORTABLE_DIR_REL_PATH%
if "%SIMU%" == "true" (
    copy build\external\jsoncpp\src\lib_json\Release\jsoncpp.dll %PORTABLE_DIR_REL_PATH%
)
if "%GUI%" == "true" (
    copy build\app-gui\Release\relaybox.exe %PORTABLE_DIR_REL_PATH%
    copy prebuilt\wxwidgets\lib\Release\wxbase32u_vc*_x64.dll %PORTABLE_DIR_REL_PATH%
    copy prebuilt\wxwidgets\lib\Release\wxmsw32u_core_vc*_x64.dll %PORTABLE_DIR_REL_PATH%
)

cd %PORTABLE_DIR_REL_PATH%

tar -czf ../%PORTABLE_ARCHIVE_NAME%.tar.gz *
