# multigrid-solver

...

## Build & Test

This project uses the Clang compiler and requires yaml-cpp for configuration parsing.

### Prerequisites

Install Clang and yaml-cpp:

```sh
sudo apt install clang libyaml-cpp-dev
```

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

To run with a custom config file:

```sh
./main --config ../data/config.yaml
```

### Run the tests

```sh
./test/test_<function-name>
```

Or use CTest to run all tests:

```sh
ctest
```