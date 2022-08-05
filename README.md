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
