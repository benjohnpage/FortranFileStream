## Overview

FortranFileStream is a basic attempt at a class that uses Fortran file
units to read in data, but with a C++ stream syntax.

Some would say that this is a mad idea, but this is useful in the world of
cross compiling Fortran and C++. I specifically needed it because I was
partially rewriting a Fortran library in C++. Such I needed to do some
C++ reading on the same file that the fortran needed to read. What's more
I wanted to maintain C++ convention and so we have FortranFileStream.

A few notes:

* The current implementation is compiler dependent. It is written using the
  autoconf macro FC\_FUNC, however as the project is too small to warrant
  autoconf I have provided a version that works on MY system.

* The method of passing strings as arguments to Fortran Functions also
  differs between compilers, so extra functionality may be needed here.

* Currently we only support the reading of files, but the principles used
  (leveraging Fortran's "stream-like" read statements) should extend fairly
  well to writing files.

## Building

Simply use the given Makefile to build the Demo program. In terms of
linking your own stuff to it I suggest that you use it as drop in code.
Renaming the namespace and providing a real FC_FUNC from autoconf.