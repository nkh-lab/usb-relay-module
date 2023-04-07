## Intro

The project also supports simulation mode. For this, a JSON configuration file is used, which is created at the first start and can then be configured.

## Dependencies
For working with JSON format [jsoncpp][github-jsoncpp] library is used.

It should be cloned manualy to [external](../external) folder:
```
git clone https://github.com/open-source-parsers/jsoncpp.git ./external/jsoncpp -b 1.9.5
```
**Warning!** Because [jsoncpp][github-jsoncpp] has a problem when compiled as a subproject, use the patched from [nkh-lab][github-nkhlab-jsoncpp]:
```
git clone https://github.com/nkh-lab/jsoncpp.git ./external/jsoncpp -b Avoid-using-cmake-glob-vars
```

## How to build
Run `cmake` with `-Dusbrelaymodule_BUILD_SIMU=ON` option.

### Linux
```
cmake -Dusbrelaymodule_BUILD_SIMU=ON ..
make
```

### Windows
```
cmake -G "Visual Studio 17 2022" -Dusbrelaymodule_BUILD_SIMU=ON ..
cmake --build . --config Release
```

### Portable
Run the appropriate script according to your OS from the [tools](../tools) folder with the simu flag, for example:
```
./tools/build-portable-linux.sh simu
```

<!-- References -->
[github-nkhlab-jsoncpp]: https://github.com/nkh-lab/jsoncpp/tree/Avoid-using-cmake-glob-vars
[github-jsoncpp]: https://github.com/open-source-parsers/jsoncpp
[github-jsoncpp-issue]: https://github.com/open-source-parsers/jsoncpp/issues/1451

---
Go to [Contents](Contents.md)