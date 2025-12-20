# multigrid-solver

...

## Build

This project uses the Clang compiler.
If you don’t have Clang, install it with your package manager (e.g., `sudo apt install clang`).

To build:

```sh
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
make
./main
```