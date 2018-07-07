# RPN
Reverse Polish Notation. For more information, please check [wikipedia](https://en.wikipedia.org/wiki/Reverse_Polish_notation).

## Prerequisites
You have to install the GNU readline and a working C compiler (clang, gcc, etc...).

## Build
Generate the configure script:
```
./bootstrap.sh
```

Generate the Makefile:
```
./configure
```

Compile the source:
```
make
```
or:
```
./build.sh
```

Clean everything:
```
./clean.sh
```

## Running the tests
There is a python script called *regress.py* which is wrapped via the *clean.sh* script.

## License
**rpn** is licensed under the BSD 3-clause "New" or "Revised" License.
