# Lime
A library of useful C++ stuff developed and implemented by Phil Kilby on belalf of CSIRO.

Subject to copyright as set out in the file [LICENCE.md](LICENCE.md) 

# Installation

The library using CMake for compilation and installation of the library and
tests where tests are created optionally.

## Builds for Linux distributions and Mac OSX

### Builds

Open a terminal and go to the root directory of Lime and follow these steps
to compile the library.
```
mkdir build
cd build
cmake ..
cmake --build .

```
Note that by default the library will be built for Release. You can specify the
build mode by using the parameter `-DCMAKE_BUILD_TYPE=[Debug|Release|MinSizeRel|RelWithDebInfo]`
for the first `cmake` command, e.g., `cmake -DCMAKE_BUILD_TYPE=Debug ..`.

### Tests

If you want to compile all tests or a subset of them then additionally use the 
target parameter for the cmake build command. For all tests use the target value
`tests`. The individual target values for all tests are `limetest`, `boxtest`, 
`accessortest`, and `pwlttest`. For instance, the command
```
cmake --build . --target tests
```
builds all the tests whereas the command
```
cmake --build . --target limetest --target boxtest
```
only builds for the lime and box test. Note that on some system multiple targets
are not allowed for one build command. In that case, just run a seperate build
command for each target.


## Builds for Windows using MS Visual Studio C++

### Builds

Open a Developer Command Prompt for Visual Studio and go to the root directory of Lime and follow these steps
to compile the library.
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
Note that MS Visual Studio can build multiple different build types with the 
same configuration setup, which one to use needs to be specified for the configuration
parameter `--config` when building the system. It can take these values `Debug`, `Release`,
`MinSizeRel`, and `RelWithDebInfo`. Further note that building without a specified 
configuration parameter will automatically build for `Debug`.

### Tests

Use the same commands as for Linux distributions and Mac OSX, but additional use
the configuration parameter `--config` to specify the build type.

## Installation

To install the library and tests onto your system after building them, simply 
run following command inside the build directory for Linux distributions and Mac OSX
```
cmake --build . --target install
```
and 
```
cmake --build . --config Release --target install
```
for Windows.

The library, the header files, and the executables will be installed in the default
location on your machine, which are system dependent. If you want to change the 
default location then specifiy the variable `CMAKE_INSTALL_PREFIX` when setting up
the build folder, e.g.,
```
cmake -DCMAKE_INSTALL_PREFIX=<LOCATION> ..
```
Replace `<LOCATION>` with your installation location. In that location, there 
will be the three sub-folders `lib`, `include`, and `bin` respectively including
the library, the header files, and the executables.

Note that you may need to add the installation folder or its sub-folders to the
corresponding environment variables on your system, so that other programs
can find them.
