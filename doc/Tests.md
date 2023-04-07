## How to build tests
### Linux
Supports both Unit and Component tests.

Install dependencies for compiling Unit tests:
```
sudo apt-get install libgtest-dev libgmock-dev
```
Build:
```
cmake -Dusbrelaymodule_BUILD_UTESTS=on -Dusbrelaymodule_BUILD_CTESTS=on ..
make
```
### Windows
Supports only Component tests:
```
cmake -G "Visual Studio 17 2022" -Dusbrelaymodule_BUILD_CTESTS=on ..
cmake --build . --config Release
```

---
Go to [Contents](Contents.md)