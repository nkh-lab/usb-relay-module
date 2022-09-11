## How to build tests
### Linux
Supports both Unit and Component tests:
```
cmake -Dusbrelaymodule_BUILD_UTESTS=on -Dusbrelaymodule_BUILD_CTESTS=on ..
make
```
### Windows
Supports only Component tests:
```
cmake -G "Visual Studio 17 2022" -A Win32 -Dusbrelaymodule_BUILD_CTESTS=on .. 
cmake --build . --config Release
```