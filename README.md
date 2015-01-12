C++ generic factory 
===================

Experimental generic factory library for C++11/14/17. 

# Proposal

This code will eventualy form the basis of a formal proposal to add a generic factories to the C++ standard library (https://github.com/viboes/std-make/blob/master/doc/proposal/factories/DXXXX_factories.md).


# Development Status

This code is undocumented, untested, constantly changing, and generally not fit for any use whatsoever.

# Test results

@               | Build         | Tests coverage | More info
----------------|-------------- | -------------- |-----------
Develop branch: | [![Build Status](https://travis-ci.org/viboes/std_make.svg?branch=develop)](https://travis-ci.org/viboes/std_make)  | [![Coverage Status](https://coveralls.io/repos/viboes/std_make/badge.png?branch=develop)](https://coveralls.io/r/viboes/std_make?branch=develop) | [details...](http://www.boost.org/development/tests/develop/developer/std_make.html)
Master branch:  | [![Build Status](https://travis-ci.org/viboes/std_make.svg?branch=master)](https://travis-ci.org/viboes/std_make)  | [![Coverage Status](https://coveralls.io/repos/viboes/std_make/badge.png?branch=master)](https://coveralls.io/r/viboes/std_make?branch=master) | [details...](http://www.boost.org/development/tests/master/developer/std_make.html)


# License

Most of the source code in this project are mine, and those are under the Boost Software License. I have borrowed the `hana::type` class.

# Supported Compilers

The code is known to work on the following compilers:

* Clang 3.2 -std=c++11 
* Clang 3.5 -std=c++11 -std=c++1y
* GCC 4.7.2, 4.8.0, 4.8.1, 4.8.2 -std=c++11
* GCC 4.9.0 -std=c++11 -std=c++1y
* GCC 4.9.1 -std=c++11 -std=c++1y

# Acknowledgements 

Many thanks to Agustín K-ballo Bergé. 

# References

