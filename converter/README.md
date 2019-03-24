# Converter
Convert numbers between positional numeral systems.

----

## About
Converter is a C++ program that allows displaying numbers in different positional numeral systems. It can be run in either command-line mode (for text terminal) or graphical mode (with Gtk3 GUI).

----

## Dependencies

### Standard build & run
Build process:
+ [C++ 14](https://isocpp.org/)
+ [CMake 3.5](https://cmake.org/)
+ [GNU Make](https://www.gnu.org/software/make)

Additional libraries:
+ [gtkmm3](https://www.gtkmm.org)

----

## How to build?
Converter can be built using **[CMake](https://cmake.org/)** with help of **[GNU Make](https://www.gnu.org/software/make)** using following script:
```sh
mkdir build
cd build
cmake ..
make
```

Binaries are stored in `bin` directory.

## How to run graphical mode?
Converter in graphical mode can be run directly using the executable file:
```sh
$ /path/to/directory/bin/converter-gtk
```

## How to run command-line mode?
Converter in command-line mode can be run directly using the executable file with options described below:
```sh
$ /path/to/directory/bin/converter ...
```

### Synopsis
**converter** \[**-b** *in*\] \[**-B** *out*\] \[*arg*\]...

### Description
Convert each number *arg* from numeral system of base *in* to system of base *out*. If no numbers are specified as arguments, read them from standard input.

### Options
**-b** *in*
> Define *in* as input base i.e. the base of numeral system in which each number *arg* is expressed. The value of *in* has to be between 2 and 16 inclusive, default is 10.

**-B** *out*
> Define *out* as output base i.e. the base of numeral system to which each number *arg* is converted. The value of *out* has to be between 2 and 16 inclusive, default is 10.
