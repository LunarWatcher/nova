# Nova

Nova is a scriptable helper bot

## Building nova

```
mkdir build && cd build
cmake ..
# Assuming makefiles:
make nova
```

Just `make` also builds tests, `make test` compiles and runs tests.

The same applies to other generators: no specified target builds everything (in theory), `nova` builds nova (may require `novasources` first; required with ninja on windows because dependency resolution is bad), `test` builds and runs tests.
