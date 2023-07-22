# Mac build:

```bash
git submodule update --init --recursive
cmake -S ./deps/AAGL -B ./deps/AAGL/build
make -C ./deps/AAGL/build
cmake -S ./deps/glfw/ -B ./deps/glfw/build
make -C ./deps/glfw/build/
```
