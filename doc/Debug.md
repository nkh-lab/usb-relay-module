## How to build Debug variant

Run `cmake` with `-DCMAKE_BUILD_TYPE=Debug` option, e.g.:

```
cmake -Dusbrelaymodule_BUILD_SIMU=ON -Dusbrelaymodule_BUILD_UTESTS=on -DCMAKE_BUILD_TYPE=Debug ..
make
```

## Using VSCode for debugging

The project contains the appropriate configuration file [launch.json](../.vscode/launch.json) to launch the debugger from VSCode.

---
Go to [Contents](Contents.md)