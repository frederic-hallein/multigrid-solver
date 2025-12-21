# multigrid-solver

...

## Build & Test

This project uses the Clang compiler.
If you don’t have Clang, install it with your package manager (e.g., `sudo apt install clang`).

### Clone with submodules

If you are cloning the repository for the first time, use:

```sh
git clone --recursive git@github.com:frederic-hallein/multigrid-solver.git
```

If you already cloned without `--recursive`, initialize submodules with:

```sh
git submodule update --init --recursive
```

### Build the project and tests

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
make
```

### Run the main executable

```sh
./main
```

### Run the tests

```sh
./test/test_<function-name>
```

Or use CTest to run all tests:

```sh
ctest
```