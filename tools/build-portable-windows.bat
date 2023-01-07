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