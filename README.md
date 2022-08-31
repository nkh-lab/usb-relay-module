## Intro

## How to get the project source code
Clone main git project:
```
$ git clone https://github.com/nkh-lab/nrelay.git
```
Clone submodule projects:
```
$ git submodule update --init
```
## Depedencies
### Linux
```
$ sudo apt-get install libudev-dev libusb-1.0-0-dev libfox-1.6-dev
```
## How to build
### Linux
```
$ mkdir build && cd build
```
Without tests:
```
$ cmake ..
$ make
```
With tests:
```
$ cmake -Dusbrelaymodule_BUILD_CTESTS=on ..
$ make
```
### Windows
The following describes how to build the project from the command line for the compiler from Visual Studio.

Add `msbuild` to `PATH` environment variable:
```
set PATH=%PATH%;<path to msbuild>
```
```
$ mkdir build && cd build
```
Without tests:
```
$ cmake -G "Visual Studio 17 2022" -A Win32 .. 
$ cmake --build . --config Release
```
With tests:
```
$ cmake -G "Visual Studio 17 2022" -A Win32 -Dusbrelaymodule_BUILD_CTESTS=on .. 
$ cmake --build . --config Release
```


