## Intro
Cross-platform project for controlling USB relay modules based on HID technology.

![](doc/pictures/intro.png)

## CI Status
[![CI](https://github.com/nkh-lab/usb-relay-module/actions/workflows/ci.yml/badge.svg)](https://github.com/nkh-lab/usb-relay-module/actions/workflows/ci.yml)

Ubuntu | Windows

## How to get project source code
Clone main project:
```
git clone https://github.com/nkh-lab/usb-relay-module.git
```
Clone submodule projects:
```
git submodule update --init
```
## How to build

The following describes how to build and use CLI applications: `getrelay` and `setrelay`.

If you also want to use GUI application - `relaybox`, follow the [GUI Application](doc/GUI.md) guide.

### Linux
Install depedencies, e.g. for Ubuntu:
```
sudo apt-get install libudev-dev
```
Build:
```
mkdir build && cd build
cmake ..
make
```
### Windows
The following describes how to build the project from the command line for the compiler from Visual Studio.

Add `msbuild` to `PATH` environment variable if it's unset:
```
set PATH=%PATH%;<path to msbuild>
```
Build:
```
mkdir build && cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
```
### Portable
To be able to use the output binaries outside of the project, use the appropriate scripts from the [tools](tools) folder to build the portable package ([build/portable](build/portable) and its archive [build/usbrelaymodule-portable.tar.gz](build/usbrelaymodule-portable.tar.gz)), for example for Ubuntu:
```
./tools/build-portable-linux.sh
```

## How to use getrelay and setrelay
These are CLI applications, use `--help` command to see usage description.
### Usage examples
**Example**: Get information about detected module
```
./getrelay
path:             /dev/hidraw6
vendor_id:        0x16c0
product_id:       0x05df
serial_number:
release_number:   256
manufacturer:     www.dcttech.com
product:          USBRelay2
interface_number: 0
module_name:      R3
channel_1:        0
channel_2:        0
```
**Example**: Set first channel to `1` (ON) then to `0` (OFF) of module `R3`
```
./setrelay R3_1=1
...
./setrelay R3_1=0
```
**Example**: Rename module `R3` to `Mod4`
```
./setrelay R3=Mod4
```

## Troubleshooting and other documentation
Troubleshooting documentation is available at:
- [Troubleshooting](doc/Troubleshooting.md)

And here is the contents page of all available documentation:
- [Contents](doc/Contents.md)
