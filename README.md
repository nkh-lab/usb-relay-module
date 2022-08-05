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
```
With tests:
```
$ cmake -Dnrelay_BUILD_CTESTS=on ..
```
