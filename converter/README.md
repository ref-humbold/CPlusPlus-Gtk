# Converter
Converts numbers between positional numeral systems.

----

## How to run graphical mode?

```sh
$ ./converter-gtk
```

----

## How to run command-line mode?

### Synopsis
**converter** \[**-b** *in*\] \[**-B** *out*\] \[*arg*\]...

### Description

Convert each number *arg* from numberal system with base *in* to system with base *out*. If no numbers are specified, read them from standard input.

### Options
**-b** *in*

> Define *in* as input base i.e. the base of numeral system in which each number *arg* is expressed. The value of *in* has to be between 2 and 16 inclusive, default is 10.

**-B** *out*

> Define *out* as output base i.e. the base of numeral system to which each number *arg* is converted. The value of *out* has to be between 2 and 16 inclusive, default is 10.
