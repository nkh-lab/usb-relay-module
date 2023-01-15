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

SET DIR=%~dp0
cd %DIR\..
SET PROJECT_ROOT=%cd%
SET PORTABLE_DIR_REL_PATH="build\portable"
SET PORTABLE_ARCHIVE_NAME="usbrelaymodule-portable"

:start_args_check
if "%1" == "" (
    goto end_args_check
)
else if "%1" == "simu" (
    SET SIMU="true"
    CMAKE_ARGS="$CMAKE_ARGS \
                -Dusbrelaymodule_BUILD_SIMU=ON
                -DJSONCPP_WITH_TESTS=OFF
                -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF
                -DJSONCPP_WITH_PKGCONFIG_SUPPORT=OFF
                -DJSONCPP_WITH_CMAKE_PACKAGE=OFF"

    if [ ! -d "$PROJECT_ROOT/external/jsoncpp" ]; then
        git clone https://github.com/nkh-lab/jsoncpp.git ./external/jsoncpp -b Avoid-using-cmake-glob-vars
    fi
)

shift
goto :start_args_check

:end_args_check

rd /s /q build\ 2>nul
mkdir build && cd build

cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release

cd %PROJECT_ROOT%

mkdir %PORTABLE_DIR_REL_PATH%

copy build\app-cli\Release\getrelay.exe %PORTABLE_DIR_REL_PATH%
copy build\app-cli\Release\setrelay.exe %PORTABLE_DIR_REL_PATH%
copy build\libusbrelaymodule\Release\libusbrelaymodule.dll %PORTABLE_DIR_REL_PATH%
copy build\external\hidapi\src\windows\Release\hidapi.dll %PORTABLE_DIR_REL_PATH%

cd %PORTABLE_DIR_REL_PATH%

tar -czf ../%PORTABLE_ARCHIVE_NAME%.tar.gz *